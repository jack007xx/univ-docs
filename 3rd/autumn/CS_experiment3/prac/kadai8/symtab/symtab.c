#include "symtab.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define DEBUG
/* 記号表の実体をここで作成 */
/* parser.yからは，以下のinsert/symtab_lookup/deleteなどを通してアクセスする */
Symtab* TABLE;

/* symtab_push, symtab_lookup, deleteの実装 */

void symtab_init() {
  TABLE = NULL;

#ifdef DEBUG
  printf("[DEBUG] new symbol table created\n");
#endif
}

// プライベート
// バックエンドでのプッシュ
Row* __symtab_push(char* aName, int aRegnum, int aOffset, int aSize,
                   Scope aScope) {
  // TODO mallocの例外処理
  char* tName = (char*)malloc(sizeof(char) * strlen(aName));
  strcpy(tName, aName);
  // TODO mallocの例外処理
  Symtab* tTable = (Symtab*)malloc(sizeof(Symtab));

  // 多重にmallocしなくても良いように、Rowは値で渡す。問題ないはず?
  Row tRow = {tName, aRegnum, aOffset, aSize, aScope};
  tTable->row = tRow;
  tTable->prev = TABLE;
  TABLE = tTable;

#ifdef DEBUG
  // デバッグ出力、全部出す
  printf("[DEBUG] inserted\n");
  for (Symtab* tPointer = TABLE; tPointer != NULL; tPointer = tPointer->prev) {
    print_row(tPointer->row);
  }
  printf("\n");
#endif

  return &tTable->row;
}

Row* symtab_push(char* aName, int aRegnum, Scope aScope) {
  return __symtab_push(aName, aRegnum, 0, 0, aScope);
}

Row* symtab_push_array(char* aName, int aRegnum, int aOffset, int aSize,
                       Scope aScope) {
  return __symtab_push(aName, aRegnum, aOffset, aSize, aScope);
}

Row* symtab_lookup(char* aName) {
#ifdef DEBUG
  printf("[DEBUG] searching: %s\n", aName);
#endif

  for (Symtab* tPointer = TABLE; tPointer != NULL; tPointer = tPointer->prev) {
    if (strcmp(tPointer->row.name, aName) == 0) {
#ifdef DEBUG
      // デバッグ出力、見つけたもの
      printf("[DEBUG] found\n");
      print_row(tPointer->row);
      printf("\n");
#endif
      return &tPointer->row;
    }
  }

#ifdef DEBUG
  printf("[DEBUG] not found\n\n");
#endif
  return NULL;
}

int symtab_delete() {
  int tCnt = 0;
  for (Symtab* tPointer = TABLE; tPointer != NULL;) {
    tPointer = tPointer->prev;

    if (TABLE->row.type == GLOBAL_VAR || TABLE->row.type == PROC_NAME ||
        TABLE->row.type == FUNC_NAME) {
      break;
    } else {
      // free(TABLE->row.name);
      free(TABLE);
      TABLE = tPointer;
      tCnt++;
    }
  }

#ifdef DEBUG
  // デバッグ出力、全部出す
  printf("[DEBUG] deleted: %d symbols\n", tCnt);
  for (Symtab* tPointer = TABLE; tPointer != NULL; tPointer = tPointer->prev)
    print_row(tPointer->row);
  printf("\n");
#endif

  return tCnt;
}

void print_row(Row aRow) {
  char* tScopeTable[] = {"global", "local", "proc",         "func",
                         "const",  "label", "global array", "local array"};
  printf("<NAME: %s, REGNUM: %d, SCOPE: %s>\n", aRow.name, aRow.regnum,
         tScopeTable[aRow.type]);
}
