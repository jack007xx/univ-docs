#include "llvmcommands.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define DEBUG

void print_code(LLVMcode *aCode);

LLVMcode *codehd; /* 命令列の先頭のアドレスを保持するポインタ */
LLVMcode *codetl; /* 命令列の末尾のアドレスを保持するポインタ */
Fundecl
    *declhd; /* 関数定義の線形リストの先頭の要素のアドレスを保持するポインタ */
Fundecl
    *decltl; /* 関数定義の線形リストの末尾の要素のアドレスを保持するポインタ */

Factorstack FSTACK; /* 整数もしくはレジスタ番号を保持するスタック */
void fundecl_init() {
  // 課題4では関数呼び出しを行わないので、このように定義する。
  Fundecl *tMain = (Fundecl *)malloc(sizeof(Fundecl));
  strcpy(tMain->fname, "Main");
  declhd = tMain;
  decltl = tMain;
}

void code_init() {
  // LLVMcode *tInitialCode = (LLVMcode *)malloc(sizeof(LLVMcode));
  codehd = NULL;
  codetl = NULL;
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
  printf("factor stock\n");
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
  printf("[DEBUG] Factor stack poped\n");
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
  printf("[DEBUG] Factor stack pushed\n");
  print_factor_stack();
  print_LLVM_code();
#endif
  return tFactor;
}

LLVMcode *code_create(LLVMcommand aCommand, Factor *aArg1, Factor *aArg2,
                      Factor *aRetval) {
  LLVMcode *tCode = malloc(sizeof(LLVMcode));
  tCode->command = aCommand;

  switch (aCommand) {
    case Alloca:
      tCode->args.alloca.retval = *aRetval;
      break;
    case Global:
      tCode->args.global.retval = *aRetval;
      break;
    case Load:
      tCode->args.load.arg1 = *aArg1;
      tCode->args.load.retval = *aRetval;
      break;
    case Store:
      tCode->args.store.arg1 = *aArg1;
      tCode->args.store.arg2 = *aArg2;
      break;
    case Add:
      tCode->args.add.arg1 = *aArg1;
      tCode->args.add.arg2 = *aArg2;
      tCode->args.add.retval = *aRetval;
      break;
    case Sub:
      break;
    case Mul:
      break;
    case Sdiv:
      break;
    case Icmp:
      break;
    case BrUncond:
      break;
    case BrCond:
      break;
    case Call:
      break;
    case Label:
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
      fprintf(stderr, "unexpected error\n");
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

void factor_encode(Factor aFactor, char *aArg) {
  switch (aFactor.type) {
    case GLOBAL_VAR:
      sprintf(aArg, "@%s", aFactor.vname);
      break;
    case LOCAL_VAR:
      sprintf(aArg, "%%%d", aFactor.val);
      break;
    case CONSTANT:
      sprintf(aArg, "%d", aFactor.val);
      break;
    case LABEL:
      sprintf(aArg, "%d", aFactor.val);
    default:
      break;
  }
}

void print_code(LLVMcode *aCode) {
  char tInstruction[256], tArg1[256], tArg2[256], tRetval[256];
  switch (aCode->command) {
    case Alloca:
      factor_encode(aCode->args.alloca.retval, tRetval);
      printf("%s = alloca i32 0, align 4\n", tRetval);
      break;
    case Global:
      factor_encode(aCode->args.global.retval, tRetval);
      printf("%s = common global i32 0, align 4\n", tRetval);
      break;
    case Load:
      factor_encode(aCode->args.load.arg1, tArg1);
      factor_encode(aCode->args.load.retval, tRetval);
      printf("%s = load i32, i32* %s, align 4\n", tRetval, tArg1);
      break;
    case Store:
      factor_encode(aCode->args.store.arg1, tArg1);
      factor_encode(aCode->args.store.arg2, tArg2);
      printf("store i32 %s, i32* %s, align 4\n", tArg1, tArg2);
      break;
    case Add:
      factor_encode(aCode->args.add.arg1, tArg1);
      factor_encode(aCode->args.add.arg2, tArg2);
      factor_encode(aCode->args.add.retval, tRetval);
      printf("%s = add nsw i32 %s, %s\n", tRetval, tArg1, tArg2);
      break;
    case Sub:
      factor_encode(aCode->args.sub.arg1, tArg1);
      factor_encode(aCode->args.sub.arg2, tArg2);
      factor_encode(aCode->args.sub.retval, tRetval);
      printf("%s = sub nsw i32 %s, %s\n", tRetval, tArg1, tArg2);
      break;
    case Mul:
      factor_encode(aCode->args.mul.arg1, tArg1);
      factor_encode(aCode->args.mul.arg2, tArg2);
      factor_encode(aCode->args.mul.retval, tRetval);
      printf("%s = mul nsw i32 %s, %s\n", tRetval, tArg1, tArg2);
      break;
    case Sdiv:
      factor_encode(aCode->args.sdiv.arg1, tArg1);
      factor_encode(aCode->args.sdiv.arg2, tArg2);
      factor_encode(aCode->args.sdiv.retval, tRetval);
      printf("%s = sdiv i32 %s, %s\n", tRetval, tArg1, tArg2);
      break;
    case Icmp:
      factor_encode(aCode->args.icmp.arg1, tArg1);
      factor_encode(aCode->args.icmp.arg2, tArg2);
      factor_encode(aCode->args.icmp.retval, tRetval);
      printf("%s = icmp %d i32 %s, %s\n", tRetval,
             ito_cmp_type[aCode->args.icmp.type], tArg1, tArg2);
      break;
    case BrUncond:
      printf("br label %d\n", aCode->args.bruncond.arg1);
      break;
    case BrCond:
      // condの代わりにretvalに入れてる
      factor_encode(aCode->args.brcond.cond, tRetval);
      factor_encode(aCode->args.brcond.arg1, tArg1);
      factor_encode(aCode->args.brcond.arg2, tArg2);
      printf("br i1 %s, label %d, label %d\n", tRetval, tArg1, tArg2);
      break;
    case Call:
      break;
    case Label:
      printf("; <label>:%d:\n", aCode->args.label.arg1);
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
  int tIsInMain = 0;
  for (Fundecl *tFunPointer = declhd; tFunPointer != NULL;
       tFunPointer = tFunPointer->next) {
    for (LLVMcode *tCodePointer = tFunPointer->codes; tCodePointer != NULL;
         tCodePointer = tCodePointer->next) {
      if (!tIsInMain && tCodePointer->command != Global) {
        printf("define i32 @main(){\n");
        printf("\t%%1 = alloca i32, align 4\n");
        tIsInMain = 1;
      }

      if (tIsInMain) printf("\t");
      print_code(tCodePointer);
    }
    printf("\tret i32 0\n}\n\n");
  }
};
