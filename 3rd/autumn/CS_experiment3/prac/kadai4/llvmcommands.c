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

Factor factor_pop() {
  Factor tmp;
  tmp = FSTACK.element[FSTACK.top];
  FSTACK.top--;
  return tmp;
}

void factor_push(char *aName, int aVal, Scope aType) {
  printf("<Factor pushed: %s>\n", aName);
  strcpy(FSTACK.element[FSTACK.top].vname, aName);
  FSTACK.element[FSTACK.top].val = aVal;
  FSTACK.element[FSTACK.top].type = aType;
  FSTACK.top++;
  return;
}

void code_add(LLVMcode tmp) {
  printf("<Factpr poped: command is %d>\n", tmp.command);
  LLVMcode *tCode = (LLVMcode *)malloc(sizeof(LLVMcode));
  *tCode = tmp;
  tCode->next = NULL;
  if (codetl == NULL) {   /* 解析中の関数の最初の命令の場合 */
    if (decltl == NULL) { /* 解析中の関数がない場合 */
      /* 関数宣言を処理する段階でリストが作られているので，ありえない */
      fprintf(stderr, "unexpected error\n");
    }
    decltl->codes = tCode; /* 関数定義の命令列の先頭の命令に設定 */
    codehd = codetl = tCode; /* 生成中の命令列の末尾の命令として記憶 */
  } else { /* 解析中の関数の命令列に1つ以上命令が存在する場合 */
    codetl->next = tCode; /* 命令列の末尾に追加 */
    codetl = tCode;       /* 命令列の末尾の命令として記憶 */
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
};

char *ito_instruction[] = {"alloca", "global", "load",  "add",  "store",
                           "add",    "mul",    "sdiv",  "icmp", "br",
                           "brc",    "call",   "label", "ret",  "phi"};

void factor_format(Factor aFactor, char *aArg) {
  switch (aFactor.type) {
    case GLOBAL_VAR:
      sprintf(aArg, "@%s", aFactor.vname);
      break;
    case LOCAL_VAR:
      sprintf(aArg, "%%%d", aFactor.val);
      break;
    default:
      break;
  }
}

void print_code(LLVMcode *aCode) {
  char *tInstruction[256];
  char *tArg1[256];
  char *tArg2[256];
  char *tRetval[256];
  char *tType[256];
  switch (aCode->command) {
    case Alloca:
      factor_format(aCode->args.alloca.retval, tRetval);
      printf("%s = alloca i32 0, align 4\n", tRetval);
      break;
    case Global:
      factor_format(aCode->args.global.retval, tRetval);
      printf("%s = common global i32 0, align 4\n", tRetval);
      break;
    case Load:
      printf("", aCode->args.load.arg1.val, aCode->args.load.retval.val);
      break;
    case Store:
      break;
    case Add:
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
}
