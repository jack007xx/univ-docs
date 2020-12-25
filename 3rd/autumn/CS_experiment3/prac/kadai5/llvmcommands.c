#include "llvmcommands.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define DEBUG
// #define TOFILE

void print_code(LLVMcode *aCode);

LLVMcode *codehd; /* 命令列の先頭のアドレスを保持するポインタ */
LLVMcode *codetl; /* 命令列の末尾のアドレスを保持するポインタ */
Fundecl
    *declhd; /* 関数定義の線形リストの先頭の要素のアドレスを保持するポインタ */
Fundecl
    *decltl; /* 関数定義の線形リストの末尾の要素のアドレスを保持するポインタ */

Factorstack FSTACK; /* 整数もしくはレジスタ番号を保持するスタック */

BrStack *gBrStack;

FILE *gFile;

void fundecl_init() {
  declhd = NULL;
  decltl = NULL;
}

void fundecl_add(char *aName, unsigned aArity) {
  Fundecl *tFun = malloc(sizeof(Fundecl));
  strcpy(tFun->fname, aName);
  tFun->arity = aArity;

  tFun->codes = codehd;
  code_init();

  if (declhd == NULL) {
    declhd = tFun;
    decltl = tFun;
  } else {
    decltl->next = tFun;
    decltl = tFun;
  }
}

void fstack_init() { /* FSTACKの初期化 */
  FSTACK.top = 0;
  return;
}

void print_factor(Factor *aFactor) {
  printf("[vname: %s, val: %d, type: %d]\n", aFactor->vname, aFactor->val,
         aFactor->type);
}

void print_factor_stack() {
  for (int i = 0; i <= FSTACK.top - 1; i++) {
    print_factor(FSTACK.element[i]);
  }
  printf("\n");
}

// ポップしてもメモリを開放しない(コード生成に使い回すため)
Factor *factor_pop() {
  // .topは、挿入する位置を示すので、先にデクリメントしてもおk
  FSTACK.top--;
#ifdef DEBUG
  printf("[DEBUG] Factor stack POPED\n");
  print_factor(FSTACK.element[FSTACK.top]);
  printf("\n");
#endif
  return FSTACK.element[FSTACK.top];
}

// プッシュするたびにメモリ確保、変数名はRow構造体に入っているポインタを流用する想定
Factor *factor_push(char *aName, int aVal, Scope aType) {
  // printf("<Factor pushed: %s>\n\n", aName);
  Factor *tFactor = malloc(sizeof(Factor));
  *tFactor = (Factor){aName, aVal, aType};
  // tFactor->vname = aName;
  // tFactor->val = aVal;
  // tFactor->type = aType;
  FSTACK.element[FSTACK.top] = tFactor;
  FSTACK.top++;
#ifdef DEBUG
  printf("[DEBUG] Factor stack PUSHED\n");
  print_factor_stack();
  print_LLVM_code();
#endif
  return tFactor;
}

void code_init() {
  // LLVMcode *tInitialCode = (LLVMcode *)malloc(sizeof(LLVMcode));
  codehd = NULL;
  codetl = NULL;
}

// Factorのポインタを投げて、コマンドを指定するとコードを生成してくれる
//
LLVMcode *code_create(LLVMcommand aCommand, Factor *aArg1, Factor *aArg2,
                      Factor *aRetval, Cmptype aIcmpType) {
  LLVMcode *tCode = malloc(sizeof(LLVMcode));
  tCode->command = aCommand;
  switch (aCommand) {
    case Alloca:
      tCode->args.alloca.retval = aRetval;
      break;
    case Global:
      tCode->args.global.retval = aRetval;
      break;
    case Load:
      tCode->args.load.arg1 = aArg1;
      tCode->args.load.retval = aRetval;
      break;
    case Store:
      tCode->args.store.arg1 = aArg1;
      tCode->args.store.arg2 = aArg2;
      break;
    case Add:
      tCode->args.add.arg1 = aArg1;
      tCode->args.add.arg2 = aArg2;
      tCode->args.add.retval = aRetval;
      break;
    case Sub:
      tCode->args.sub.arg1 = aArg1;
      tCode->args.sub.arg2 = aArg2;
      tCode->args.sub.retval = aRetval;
      break;
    case Mul:
      tCode->args.mul.arg1 = aArg1;
      tCode->args.mul.arg2 = aArg2;
      tCode->args.mul.retval = aRetval;
      break;
    case Sdiv:
      tCode->args.sdiv.arg1 = aArg1;
      tCode->args.sdiv.arg2 = aArg2;
      tCode->args.sdiv.retval = aRetval;
      break;
    case Icmp:
      tCode->args.icmp.arg1 = aArg1;
      tCode->args.icmp.arg2 = aArg2;
      tCode->args.icmp.retval = aRetval;
      tCode->args.icmp.type = aIcmpType;
      break;
    case BrUncond:
      tCode->args.bruncond.arg1 = aArg1;
      break;
    case BrCond:
      tCode->args.brcond.arg1 = aArg1;
      tCode->args.brcond.arg2 = aArg2;
      tCode->args.brcond.cond = aRetval;
      break;
    case Call:
      break;
    case Label:
      tCode->args.label.arg1 = aArg1;
      break;
    case Ret:
      break;
    case Phi:
      break;
    default:
      break;
  }
  return tCode;
}

void code_add(LLVMcode *aCode) {
  // printf("<Factpr poped: command is %d>\n\n", aCode.command);
  // aCodeの内容は変更される可能性がある

  aCode->next = NULL;
  if (codetl == NULL) {   /* 解析中の関数の最初の命令の場合 */
    if (decltl == NULL) { /* 解析中の関数がない場合 */
      /* 関数宣言を処理する段階でリストが作られているので，ありえない */
      fprintf(stderr, "[ERROR] unexpected error\n");
    }
    decltl->codes = aCode; /* 関数定義の命令列の先頭の命令に設定 */
    codehd = codetl = aCode; /* 生成中の命令列の末尾の命令として記憶 */
  } else { /* 解析中の関数の命令列に1つ以上命令が存在する場合 */
    codetl->next = aCode; /* 命令列の末尾に追加 */
    codetl = aCode;       /* 命令列の末尾の命令として記憶 */
  }
}

char *ito_instruction[] = {"alloca", "global", "load",  "add",  "store",
                           "add",    "mul",    "sdiv",  "icmp", "br",
                           "brc",    "call",   "label", "ret",  "phi"};

char *ito_cmp_type[] = {"eq", "ne", "sgt", "sge", "slt", "sle"};

void factor_encode(Factor *aFactor, char *aArg) {
  switch (aFactor->type) {
    case GLOBAL_VAR:
      sprintf(aArg, "@%s", aFactor->vname);
      break;
    case LOCAL_VAR:
      sprintf(aArg, "%%%d", aFactor->val);
      break;
    case CONSTANT:
      sprintf(aArg, "%d", aFactor->val);
      break;
    case LABEL:
      sprintf(aArg, "%d", aFactor->val);
    default:
      break;
  }
}

void print_code(LLVMcode *aCode) {
  char tArg1[256], tArg2[256], tRetval[256];
  switch (aCode->command) {
    case Alloca:
      factor_encode(aCode->args.alloca.retval, tRetval);
      fprintf(gFile, "%s = alloca i32 0, align 4\n", tRetval);
      break;
    case Global:
      factor_encode(aCode->args.global.retval, tRetval);
      fprintf(gFile, "%s = common global i32 0, align 4\n", tRetval);
      break;
    case Load:
      factor_encode(aCode->args.load.arg1, tArg1);
      factor_encode(aCode->args.load.retval, tRetval);
      fprintf(gFile, "%s = load i32, i32* %s, align 4\n", tRetval, tArg1);
      break;
    case Store:
      factor_encode(aCode->args.store.arg1, tArg1);
      factor_encode(aCode->args.store.arg2, tArg2);
      fprintf(gFile, "store i32 %s, i32* %s, align 4\n", tArg1, tArg2);
      break;
    case Add:
      factor_encode(aCode->args.add.arg1, tArg1);
      factor_encode(aCode->args.add.arg2, tArg2);
      factor_encode(aCode->args.add.retval, tRetval);
      fprintf(gFile, "%s = add nsw i32 %s, %s\n", tRetval, tArg1, tArg2);
      break;
    case Sub:
      factor_encode(aCode->args.sub.arg1, tArg1);
      factor_encode(aCode->args.sub.arg2, tArg2);
      factor_encode(aCode->args.sub.retval, tRetval);
      fprintf(gFile, "%s = sub nsw i32 %s, %s\n", tRetval, tArg1, tArg2);
      break;
    case Mul:
      factor_encode(aCode->args.mul.arg1, tArg1);
      factor_encode(aCode->args.mul.arg2, tArg2);
      factor_encode(aCode->args.mul.retval, tRetval);
      fprintf(gFile, "%s = mul nsw i32 %s, %s\n", tRetval, tArg1, tArg2);
      break;
    case Sdiv:
      factor_encode(aCode->args.sdiv.arg1, tArg1);
      factor_encode(aCode->args.sdiv.arg2, tArg2);
      factor_encode(aCode->args.sdiv.retval, tRetval);
      fprintf(gFile, "%s = sdiv i32 %s, %s\n", tRetval, tArg1, tArg2);
      break;
    case Icmp:
      factor_encode(aCode->args.icmp.arg1, tArg1);
      factor_encode(aCode->args.icmp.arg2, tArg2);
      factor_encode(aCode->args.icmp.retval, tRetval);
      fprintf(gFile, "%s = icmp %s i32 %s, %s\n", tRetval,
              ito_cmp_type[aCode->args.icmp.type], tArg1, tArg2);
      break;
    case BrUncond:
      factor_encode(aCode->args.bruncond.arg1, tArg1);
      fprintf(gFile, "br label %%%s\n", tArg1);
      break;
    case BrCond:
      // condの代わりにretvalに入れてる
      factor_encode(aCode->args.brcond.cond, tRetval);
      factor_encode(aCode->args.brcond.arg1, tArg1);
      factor_encode(aCode->args.brcond.arg2, tArg2);
      fprintf(gFile, "br i1 %s, label %%%s, label %%%s\n", tRetval, tArg1,
              tArg2);
      break;
    case Call:
      break;
    case Label:
      factor_encode(aCode->args.label.arg1, tArg1);
      printf("; <label>:%s:\n", tArg1);
      break;
    case Ret:
      break;
    case Phi:
      break;
    default:
      break;
  }
}

void print_LLVM_code() {
  gFile = stdout;
#ifdef TOFILE
  gFile = fopen("result.ll", "w");
#endif

  for (Fundecl *tFunPointer = declhd; tFunPointer != NULL;
       tFunPointer = tFunPointer->next) {
    if (tFunPointer != declhd) {
      // 初回のfundeclは大域変数の定義に当てられる
      fprintf(gFile, "define i32 @%s(){\n", tFunPointer->fname);
      fprintf(gFile, "\t%%1 = alloca i32, align 4\n");
    }

    for (LLVMcode *tCodePointer = tFunPointer->codes; tCodePointer != NULL;
         tCodePointer = tCodePointer->next) {
      if (tFunPointer != declhd) printf("\t");
      print_code(tCodePointer);
    }

    if (tFunPointer != declhd) fprintf(gFile, "\tret i32 0\n}\n\n");
  }

#ifdef TOFILE
  fclose(gFile);
#endif
};

void br_push(LLVMcode *aCode) {
  BrStack *tTop = malloc(sizeof(BrStack));
  tTop->code = aCode;
  tTop->next = gBrStack;
  gBrStack = tTop;
}
void br_back_patch(int aLabel) {
  if (gBrStack->code->command == BrCond) {
    if (gBrStack->code->args.brcond.arg1->val == 0) {
      gBrStack->code->args.brcond.arg1->val = aLabel;
    } else if (gBrStack->code->args.brcond.arg2->val == 0) {
      gBrStack->code->args.brcond.arg2->val = aLabel;
    }
    gBrStack = gBrStack->next;
  } else if (gBrStack->code->command == BrUncond) {
    gBrStack->code->args.bruncond.arg1->val = aLabel;
    gBrStack = gBrStack->next;
  }
}
