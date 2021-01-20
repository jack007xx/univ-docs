#pragma once

#include "llvm.h"

// バックパッチするために、ラベルを積んでおくスタック
typedef struct brStack {
  LLVMcode *code;
  struct brStack *next;
} BrStack;

// ジャンプ先が未確定な命令をスタックに積む
// ただし、あとから埋めたいラベルは0で指定しておく必要がある
void br_push(LLVMcode *);

// スタックに積んであった未確定命令を解決する
// 0になっているところを引数の値で置き換える
void br_back_patch(int);
