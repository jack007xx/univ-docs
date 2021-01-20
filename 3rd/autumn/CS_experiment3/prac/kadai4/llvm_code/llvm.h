#pragma once

#include "factor.h"

// +----------------------------------------+
// | 命令列や、関数列を追加したり、出力する |
// +----------------------------------------+

/* LLVM命令名の定義 */
typedef enum {
  Alloca,
  Global,
  Load,
  Store,
  Add,
  Sub,
  Mul,
  Sdiv,
} LLVMcommand;

// 1つのLLVM命令と次の命令へのリンク
// 基本的にFactorでオペランドを定義している
typedef struct llvmcode {
  LLVMcommand command;
  union {
    struct {
      Factor *retval;
    } alloca;
    struct {
      Factor *retval;
    } global;
    struct {
      Factor *arg1;
      Factor *retval;
    } load;
    struct {
      Factor *arg1;
      Factor *arg2;
    } store;
    struct {
      Factor *arg1;
      Factor *arg2;
      Factor *retval;
    } add;
    struct {
      Factor *arg1;
      Factor *arg2;
      Factor *retval;
    } sub;
    struct {
      Factor *arg1;
      Factor *arg2;
      Factor *retval;
    } mul;
    struct {
      Factor *arg1;
      Factor *arg2;
      Factor *retval;
    } sdiv;
  } args;
  // 次の命令へのポインタ
  struct llvmcode *next;
} LLVMcode;

// 初期化処理
void code_init();

// 命令とオペランド、格納先とかを指定して、llvm命令を作る
LLVMcode *code_create(LLVMcommand, Factor *, Factor *, Factor *);

// ↑↓を分けたのは、制御文とかでとりあえず作るけど追加したくないときを想定

// スタックに1つのllvm命令を追加する
void code_add(LLVMcode *);

// 全てのコードをファイルに出力する
// 最後に呼び出す
void print_LLVM_code();

// ~~~~~~~~~ここから関数の表現定義~~~~~~~~~

/* LLVMの関数定義 */
typedef struct fundecl {
  char fname[256];       // 関数名
  unsigned arity;        // 引数個数
  Factor args[10];       // 引数名
  LLVMcode *codes;       // 命令列の線形リストへのポインタ
  struct fundecl *next;  // 次の関数定義へのポインタ
} Fundecl;

// 初期化処理
void fundecl_init();

// 関数を追加して、その関数に対するコード追加を開始する
void fundecl_add(char *, unsigned);
