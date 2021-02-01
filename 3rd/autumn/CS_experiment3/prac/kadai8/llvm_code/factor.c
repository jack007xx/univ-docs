#include "factor.h"

#include <stdio.h>
#include <stdlib.h>

#include "llvm.h"

// #define DEBUG

Factorstack gFstack;

void fstack_init() {
  gFstack.top = 0;
  return;
}

// デバッグ用
void print_factor(Factor *aFactor) {
  printf("[vname: %s, val: %d, type: %d]\n", aFactor->vname, aFactor->val,
         aFactor->type);
}

// デバッグ用
void print_factor_stack() {
  for (int i = 0; i <= gFstack.top - 1; i++) print_factor(gFstack.element[i]);
  printf("\n");
}

Factor *factor_push(char *aName, int aVal, Scope aType) {
  return push(aName, aVal, -1, aType);
}

Factor *factor_push_array(char *aName, int aVal, int aSize) {
  return push(aName, aVal, aSize, ARRAY);
}

// プライベート
// バックエンドでのプッシュ
Factor *push(char *aName, int aVal, int aSize, Scope aType) {
  // プッシュするたびにメモリ確保、変数名はRow構造体に入っているポインタを流用する想定
  Factor *tFactor = malloc(sizeof(Factor));
  *tFactor = (Factor){aName, aVal, aSize, aType};

  gFstack.element[gFstack.top] = tFactor;
  gFstack.top++;

#ifdef DEBUG
  printf("<<");
  print_factor(tFactor);
  // print_LLVM_code();
#endif

  return tFactor;
}

Factor *factor_pop() {
#ifdef DEBUG
  printf(">>");
  print_factor(gFstack.element[gFstack.top - 1]);
#endif
  // ポップしてもメモリを開放しない(コード生成に使い回すため)
  // .topは、挿入する位置を示すので、先にデクリメントしておk
  return gFstack.element[--gFstack.top];
}
