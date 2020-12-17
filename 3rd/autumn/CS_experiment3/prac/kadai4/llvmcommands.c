#include "llvmcommands.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  FSTACK.top++;
  strcpy(FSTACK.element[FSTACK.top].vname, aName);
  FSTACK.element[FSTACK.top].val = aVal;
  FSTACK.element[FSTACK.top].type = aType;
  return;
}

void code_add(LLVMcode tmp) {
  printf("<Factpr poped: command is %d>\n", tmp.command);
  LLVMcode *tCode = (LLVMcode *)malloc(sizeof(LLVMcode));
  *tCode = tmp;
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
