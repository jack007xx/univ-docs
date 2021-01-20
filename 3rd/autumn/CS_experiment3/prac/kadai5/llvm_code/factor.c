#include "factor.h"

#include <stdio.h>
#include <stdlib.h>

Factorstack FSTACK;

void fstack_init() {
  FSTACK.top = 0;
  return;
}

// デバッグ用
void print_factor(Factor *aFactor) {
  printf("[vname: %s, val: %d, type: %d]\n", aFactor->vname, aFactor->val,
         aFactor->type);
}

// デバッグ用
void print_factor_stack() {
  for (int i = 0; i <= FSTACK.top - 1; i++) print_factor(FSTACK.element[i]);
  printf("\n");
}

Factor *factor_push(char *aName, int aVal, Scope aType) {
  // プッシュするたびにメモリ確保、変数名はRow構造体に入っているポインタを流用する想定
  Factor *tFactor = malloc(sizeof(Factor));
  *tFactor = (Factor){aName, aVal, aType};

  FSTACK.element[FSTACK.top] = tFactor;
  FSTACK.top++;

#ifdef DEBUG
  printf("[DEBUG] Factor stack PUSHED\n");
  print_factor_stack();
  print_LLVM_code();
#endif

  return tFactor;
}

Factor *factor_pop() {
  // ポップしてもメモリを開放しない(コード生成に使い回すため)
  // .topは、挿入する位置を示すので、先にデクリメントしておk
  FSTACK.top--;

#ifdef DEBUG
  printf("[DEBUG] Factor stack POPED\n");
  print_factor(FSTACK.element[FSTACK.top]);
  printf("\n");
#endif

  return FSTACK.element[FSTACK.top];
}
