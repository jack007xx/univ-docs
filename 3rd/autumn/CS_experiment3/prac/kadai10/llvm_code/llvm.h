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
  Icmp,
  BrUncond,
  BrCond,
  Call,
  Label,
  Ret,
  Phi,
  Write,
  Read,
  Comment,
  Gep,
  Free
} LLVMcommand;

// brcondで指定する比較演算の種類
typedef enum { EQUAL, NE, SGT, SGE, SLT, SLE } Cmptype;

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
    struct {
      Factor *arg1;
      Factor *arg2;
      Factor *retval;
      Cmptype type;
    } icmp;
    struct {
      Factor *arg1;
    } bruncond;
    struct {
      Factor *cond;
      Factor *arg1;
      Factor *arg2;
    } brcond;
    struct {
      Factor *arg1;
      Factor *retval;
      Factor **proc_args;
    } call;
    struct {
      Factor *arg1;
    } label;
    struct {
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
    struct {
      Factor *arg1;
    } comment;
    struct {
      Factor *arg1;
      Factor *ind;
      Factor *retval;
    } gep;  // getelementptr
    struct {
      Factor *arg1;
    } free;
  } args;
  // 次の命令へのポインタ
  struct llvmcode *next;
} LLVMcode;

// 初期化処理
void code_init();

// 命令とオペランド、格納先とかを指定して、llvm命令を作る
LLVMcode *code_create(LLVMcommand, Factor *, Factor *, Factor *, Cmptype);

// ↑↓を分けたのは、制御文とかでとりあえず作るけど追加したくないときを想定

// スタックに1つのllvm命令を追加する
void code_add(LLVMcode *);

// 全てのコードをファイルに出力する
// 最後に呼び出す
void print_LLVM_code();

// ~~~~~~~~~ここから関数の表現定義~~~~~~~~~

/* LLVMの関数定義 */
typedef struct fundecl {
  int is_proc;
  char fname[256];       // 関数名
  unsigned arity;        // 引数個数
  Factor *args[10];      // 引数名
  LLVMcode *codes;       // 命令列の線形リストへのポインタ
  struct fundecl *prev;  // 最適化用に後ろにも参照できる
  struct fundecl *next;  // 次の関数定義へのポインタ
} Fundecl;

// 初期化処理
void fundecl_init();

// 関数を追加して、その関数に対するコード追加を開始する
void fundecl_add(char *);

// 手続きを追加して、その手続きに対するコード追加を開始する
void procdecl_add(char *);

// 新しい引数名を登録する
void fundecl_add_arg(Factor *);

// 引数用の領域確保して、ストアするとこまでやる
// 関数ラベルも考慮してgRegnumを返す。
int fundecl_add_arg_code();

// 関数名で調べてシグネチャ(今回は数字のみでシグネチャは分かる)を返す
int fundecl_lookup(char *);
