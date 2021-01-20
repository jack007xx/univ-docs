#pragma once

#ifndef __SYMBOLS_H__
#define __SYMBOLS_H__

/* 記号表の管理 + 変数・定数の区別用 */
typedef enum {
  GLOBAL_VAR, /* 大域変数 */
  LOCAL_VAR,  /* 局所変数 */
  PROC_NAME,  /* 手続き   */
  CONSTANT,   /* 定数     */
  LABEL
} Scope;

/* 記号表の構造体の宣言 */

// 表の列
typedef struct row Row;
struct row {
  char* name;
  int regnum;
  Scope type;
};

// スタックっぽい感じで表現、FILOなので出力は下から積み上がる感じに出力される
typedef struct symtab Symtab;
struct symtab {
  Row row;
  struct symtab* prev;
};

// もろもろ初期化
void symtab_init();

// 先頭に挿入
void symtab_push(char*, int, Scope);

// 失敗したときにNULLを返したいのでポインタにしている。あんまりよくないかも。
Row* symtab_lookup(char*);

// 消したシンボルの数出力
int symtab_delete();

// いい感じで出力
void print_row(Row);

#endif
