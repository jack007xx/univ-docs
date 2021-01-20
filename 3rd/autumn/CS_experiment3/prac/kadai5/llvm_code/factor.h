#pragma once

#include "../symtab/symtab.h"

/* 変数もしくは定数の型 */
// Row型に合わせて順番変更
typedef struct {
  char *vname; /* 変数の場合の変数名 ラベルはコメントにつけたい名前 */
  int val; /* 整数の場合はその値，変数の場合は割り当てたレジスタ番号 */
  Scope type; /* 変数（のレジスタ）か整数の区別 */
} Factor;

/* 変数もしくは定数のためのスタック */
typedef struct {
  Factor *element[100]; /* スタック（最大要素数は100まで） */
  unsigned int top;     /* スタックのトップの位置         */
} Factorstack;

void fstack_init();
Factor *factor_pop();
Factor *factor_push(char *, int, Scope);
