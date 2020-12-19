#include "llvmcommands.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void print_factor_stack() {
  printf("factor stock\n");
  for (int i = 0; i <= FSTACK.top - 1; i++) {
    printf("[vname: %s(%d), val: %d, type: %d]\n", FSTACK.element[i]->vname,
           FSTACK.element[i]->vname, FSTACK.element[i]->val,
           FSTACK.element[i]->type);
  }
  printf("\n");
}

Factor *factor_pop() {
  FSTACK.top--;
  return FSTACK.element[FSTACK.top];
}

Factor *factor_push(char *aName, int aVal, Scope aType) {
  // printf("<Factor pushed: %s>\n\n", aName);
  Factor *tFactor = malloc(sizeof(Factor));
  tFactor->vname = aName;
  tFactor->val = aVal;
  tFactor->type = aType;
  FSTACK.element[FSTACK.top] = tFactor;
  FSTACK.top++;
  print_factor_stack();
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
      break;
    case Store:
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

void print_LLVM_code() {
  for (Fundecl *tFunPointer = declhd; tFunPointer != NULL;
       tFunPointer = tFunPointer->next) {
    LLVMcode *tCodePointer;
    for (tCodePointer = tFunPointer->codes; tCodePointer != NULL;
         tCodePointer = tCodePointer->next) {
      print_code(tCodePointer);
    }
  }
  printf("\n");
};

char *ito_instruction[] = {"alloca", "global", "load",  "add",  "store",
                           "add",    "mul",    "sdiv",  "icmp", "br",
                           "brc",    "call",   "label", "ret",  "phi"};

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

void cmp_type_encode(Cmptype aType, char *aArg) {
  switch (aType) {
    case EQUAL:
      strcpy(aArg, "eq");
      break;
    case NE:
      strcpy(aArg, "ne");
      break;
    case SGT:
      strcpy(aArg, "sgt");
      break;
    case SGE:
      strcpy(aArg, "sge");
      break;
    case SLT:
      strcpy(aArg, "slt");
      break;
    case SLE:
      strcpy(aArg, "sle");
      break;
    default:
      break;
  }
}

void print_code(LLVMcode *aCode) {
  char tInstruction[256], tArg1[256], tArg2[256], tRetval[256], tCmpType[256];
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
      printf("%s = load i32, i32* %s, align 4", tArg1, tRetval);
      break;
    case Store:
      factor_encode(aCode->args.store.arg1, tArg1);
      factor_encode(aCode->args.store.arg2, tArg2);
      printf("store i32 %s, i32* %s, align 4", tArg1, tArg2);
      break;
    case Add:
      factor_encode(aCode->args.add.arg1, tArg1);
      factor_encode(aCode->args.add.arg2, tArg2);
      factor_encode(aCode->args.add.retval, tRetval);
      printf("%s = add nsw i32 %s, %s", tRetval, tArg1, tArg2);
      break;
    case Sub:
      factor_encode(aCode->args.sub.arg1, tArg1);
      factor_encode(aCode->args.sub.arg2, tArg2);
      factor_encode(aCode->args.sub.retval, tRetval);
      printf("%s = sub nsw i32 %s, %s", tRetval, tArg1, tArg2);
      break;
    case Mul:
      factor_encode(aCode->args.mul.arg1, tArg1);
      factor_encode(aCode->args.mul.arg2, tArg2);
      factor_encode(aCode->args.mul.retval, tRetval);
      printf("%s = mul nsw i32 %s, %s", tRetval, tArg1, tArg2);
      break;
    case Sdiv:
      factor_encode(aCode->args.sdiv.arg1, tArg1);
      factor_encode(aCode->args.sdiv.arg2, tArg2);
      factor_encode(aCode->args.sdiv.retval, tRetval);
      printf("%s = sdiv i32 %s, %s", tRetval, tArg1, tArg2);
      break;
    case Icmp:
      printf("%s = icmp %d i32 %s, %s", tRetval, aCode->args.icmp.type, tArg1,
             tArg2);
      break;
    case BrUncond:
      printf("br label %d", aCode->args.bruncond.arg1);
      break;
    case BrCond:
      // condの代わりにretvalに入れてる
      factor_encode(aCode->args.brcond.cond, tRetval);
      factor_encode(aCode->args.brcond.arg1, tArg1);
      factor_encode(aCode->args.brcond.arg2, tArg2);
      printf("br i1 %s, label %d, label %d", tRetval, tArg1, tArg2);
      break;
    case Call:
      break;
    case Label:
      printf("; <label>:%d:", aCode->args.label.arg1);
      break;
    case Ret:
      break;
    case Phi:
      break;
    default:
      break;
  }
}
