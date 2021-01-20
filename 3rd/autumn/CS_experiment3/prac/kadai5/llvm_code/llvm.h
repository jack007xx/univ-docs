#pragma once
#ifndef __LLVMCOMMANDS_H__
#define __LLVMCOMMANDS_H__
#include "factor.h"

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
  Icmp,
  BrUncond,
  BrCond,
  Call,
  Label,
  Ret,
  Phi,
  Write,
  Read
} LLVMcommand;

// brcondで指定する比較演算の種類
typedef enum { EQUAL, NE, SGT, SGE, SLT, SLE } Cmptype;

// 1つのLLVM命令と次の命令へのリンク
// 基本的にFactorでオペランドを定義している
typedef struct llvmcode {
  LLVMcommand command; /* 命令名 */
  union {              /* 命令の引数 */
    struct {           /* alloca */
      Factor *retval;
    } alloca;
    struct {
      Factor *retval;
    } global;
    struct { /* load   */
      Factor *arg1;
      Factor *retval;
    } load;
    struct { /* store  */
      Factor *arg1;
      Factor *arg2;
    } store;
    struct { /* add    */
      Factor *arg1;
      Factor *arg2;
      Factor *retval;
    } add;
    struct { /* sub    */
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
    struct { /* icmp   */
      Factor *arg1;
      Factor *arg2;
      Factor *retval;
      Cmptype type;
    } icmp;
    struct { /* br     */
      Factor *arg1;
    } bruncond;
    struct { /* brc    */
      Factor *cond;
      Factor *arg1;
      Factor *arg2;
    } brcond;
    struct {
    } call;
    struct { /* label  */
      Factor *arg1;
    } label;
    struct { /* ret    */
      Factor *arg1;
    } ret;
    struct {
    } phi;
    struct {
      Factor *arg1;
    } write;
    struct {
      Factor *arg1;
    } read;
  } args;
  // 次の命令へのポインタ
  struct llvmcode *next;
} LLVMcode;

// 初期化処理
void code_init();

// 命令とオペランド、格納先とかを指定して、llvm命令を作る
LLVMcode *code_create(LLVMcommand, Factor *, Factor *, Factor *, Cmptype);

// スタックに1つのllvm命令を追加する
void code_add(LLVMcode *);

// 全てのコードをファイルに出力する
// 最後に呼び出す
void print_LLVM_code();

// ~~~~~~~~~ここから関数の表現定義~~~~~~~~~

/* LLVMの関数定義 */
typedef struct fundecl {
  char fname[256];      /* 関数名                      */
  unsigned arity;       /* 引数個数                    */
  Factor args[10];      /* 引数名                      */
  LLVMcode *codes;      /* 命令列の線形リストへのポインタ */
  struct fundecl *next; /* 次の関数定義へのポインタ      */
} Fundecl;

// 初期化処理
void fundecl_init();

// 関数を追加して、その関数に対するコード追加を開始する
void fundecl_add(char *, unsigned);

#endif
