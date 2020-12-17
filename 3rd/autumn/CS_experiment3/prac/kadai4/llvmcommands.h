#ifndef __LLVMCOMMANDS_H__
#define __LLVMCOMMANDS_H__
#include "symtab.h"
/* LLVM命令名の定義 */
typedef enum {
  Alloca, /* alloca */
  Global,
  Load,  /* load   */
  Store, /* store  */
  Add,   /* add    */
  Sub,   /* sub    */
  Mul,
  Sdiv,
  Icmp,     /* icmp   */
  BrUncond, /* br     */
  BrCond,   /* brc    */
  Call,
  Label, /* label  */
  Ret,   /* ret    */
  Phi
} LLVMcommand;

/* 比較演算子の種類 */
typedef enum {
  EQUAL, /* eq （==）*/
  NE,    /* ne （!=）*/
  SGT,   /* sgt （>，符号付き） */
  SGE,   /* sge （>=，符号付き）*/
  SLT,   /* slt （<，符号付き） */
  SLE    /* sle （<=，符号付き）*/
} Cmptype;

/* 変数もしくは定数の型 */
// Row型に合わせて順番変更
typedef struct {
  char vname[256]; /* 変数の場合の変数名 */
  int val; /* 整数の場合はその値，変数の場合は割り当てたレジスタ番号 */
  Scope type; /* 変数（のレジスタ）か整数の区別 */
} Factor;

/* 変数もしくは定数のためのスタック */
typedef struct {
  Factor element[100]; /* スタック（最大要素数は100まで） */
  unsigned int top;    /* スタックのトップの位置         */
} Factorstack;

void fstack_init();
Factor factor_pop();
void factor_push(char *, int, Scope);

typedef struct llvmcode {
  LLVMcommand command; /* 命令名 */
  union {              /* 命令の引数 */
    struct {           /* alloca */
      Factor retval;
    } alloca;
    struct {
    } global;
    struct { /* load   */
      Factor arg1;
      Factor retval;
    } load;
    struct { /* store  */
      Factor arg1;
      Factor arg2;
    } store;
    struct { /* add    */
      Factor arg1;
      Factor arg2;
      Factor retval;
    } add;
    struct { /* sub    */
      Factor arg1;
      Factor arg2;
      Factor retval;
    } sub;
    struct {
      Factor arg1;
      Factor arg2;
      Factor retval;
    } mul;
    struct {
      Factor arg1;
      Factor arg2;
      Factor retval;
    } sdiv;
    struct { /* icmp   */
      Cmptype type;
      Factor arg1;
      Factor arg2;
      Factor retval;
    } icmp;
    struct { /* br     */
      int arg1;
    } bruncond;
    struct { /* brc    */
      Factor arg1;
      int arg2;
      int arg3;
    } brcond;
    struct {
    } call;
    struct { /* label  */
      int l;
    } label;
    struct { /* ret    */
      Factor arg1;
    } ret;
    struct {
    } phi;
  } args;
  /* 次の命令へのポインタ */
  struct llvmcode *next;
} LLVMcode;

void code_init();
void code_add(LLVMcode tmp);

/* LLVMの関数定義 */
typedef struct fundecl {
  char fname[256];      /* 関数名                      */
  unsigned arity;       /* 引数個数                    */
  Factor args[10];      /* 引数名                      */
  LLVMcode *codes;      /* 命令列の線形リストへのポインタ */
  struct fundecl *next; /* 次の関数定義へのポインタ      */
} Fundecl;

void fundecl_init();

#endif
