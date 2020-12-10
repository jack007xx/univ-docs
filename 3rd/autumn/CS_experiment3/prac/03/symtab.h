#ifndef __SYMBOLS_H__
#define __SYMBOLS_H__

/* 記号表の管理 + 変数・定数の区別用 */
typedef enum {
  GLOBAL_VAR, /* 大域変数 */
  LOCAL_VAR,  /* 局所変数 */
  PROC_NAME,  /* 手続き   */
  CONSTANT    /* 定数     */
} Scope;

/* 記号表の構造体の宣言 */

typedef struct {
  char name[256];
  int regnum;
  Scope scope;
} row;

typedef struct {
  row* table;
  int size;
} SYMTAB;

extern SYMTAB* TABLE;

/* insert, lookup, deleteのプロトタイプ宣言 */
void init();
void insert(SYMTAB*, char*, int, Scope);
row* lookup(SYMTAB*, char*);
void delete (SYMTAB*);

#endif
