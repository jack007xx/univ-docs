#pragma once

#include "../symtab/symtab.h"

// +--------------------------+
// | 計算とか遷移のための機能 |
// +--------------------------+

// 変数もしくは定数の型
// ラベルとかコメントにも使う
typedef struct {
  char *vname;  // 変数の場合の変数名 ラベルはコメントにつけたい名前
  int val;  // 整数の場合はその値，変数の場合は割り当てたレジスタ番号
  int size;
  Scope type;  // 実態が何なのか
} Factor;

// 変数もしくは定数のためのスタック
typedef struct {
  Factor *element[256];  // スタック（最大要素数は100まで）
  unsigned int top;      // スタックのトップの位置
} Factorstack;

// 諸々初期化
void fstack_init();

// スタックに積む
// 積むときも返してくれるので、積みつつ保持しておきたいときに便利
Factor *factor_push(char *, int, Scope);

// 配列バージョン
Factor *factor_push_array(char *aName, int aVal, int aSize, Scope aScope);

// スタックから出す
Factor *factor_pop();
