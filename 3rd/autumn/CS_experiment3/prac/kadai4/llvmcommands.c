#include "llvmcommands.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

LLVMcode *codehd = NULL; /* 命令列の先頭のアドレスを保持するポインタ */
LLVMcode *codetl = NULL; /* 命令列の末尾のアドレスを保持するポインタ */
Fundecl *declhd =
    NULL; /* 関数定義の線形リストの先頭の要素のアドレスを保持するポインタ */
Fundecl *decltl =
    NULL; /* 関数定義の線形リストの末尾の要素のアドレスを保持するポインタ */

Factorstack FSTACK; /* 整数もしくはレジスタ番号を保持するスタック */

void init_fstack() { /* FSTACKの初期化 */
  FSTACK.top = 0;
  return;
}

Factor fuctorpop() {
  Factor tmp;
  tmp = FSTACK.element[FSTACK.top];
  FSTACK.top--;
  return tmp;
}

void fuctorpush(char *aName, int aVal, Scope aType) {
  FSTACK.top++;
  strcpy(FSTACK.element[FSTACK.top].vname, aName);
  FSTACK.element[FSTACK.top].val = aVal;
  FSTACK.element[FSTACK.top].type = aType;
  return;
}

void add_code(LLVMcode *tmp) {
  if (codetl == NULL) {   /* 解析中の関数の最初の命令の場合 */
    if (decltl == NULL) { /* 解析中の関数がない場合 */
      /* 関数宣言を処理する段階でリストが作られているので，ありえない */
      fprintf(stderr, "unexpected error\n");
    }
    decltl->codes = tmp; /* 関数定義の命令列の先頭の命令に設定 */
    codehd = codetl = tmp; /* 生成中の命令列の末尾の命令として記憶 */
  } else { /* 解析中の関数の命令列に1つ以上命令が存在する場合 */
    codetl->next = tmp; /* 命令列の末尾に追加 */
    codetl = tmp;       /* 命令列の末尾の命令として記憶 */
  }
}
