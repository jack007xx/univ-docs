#include "symtab.h"

#include <stdio.h>
#include <string.h>

#define DEBUG
/* 記号表の実体をここで作成 */
/* parser.yからは，以下のinsert/lookup/deleteなどを通してアクセスする */
SYMTAB* TABLE;

/* insert, lookup, deleteの実装 */

void init() {
  row tRows[10000];
  SYMTAB table = {tRows, 0};

#ifdef DEBUG
  printf("[DEBUG] new symbol table created\n");
#endif

  TABLE = &table;
}

void insert(char* aName, int aRegnum, Scope aScope) {
  row tRow = {"", aRegnum, aScope};
  TABLE->table[TABLE->size] = tRow;

  strcpy(TABLE->table[TABLE->size].name, aName);

  TABLE->size++;

#ifdef DEBUG
  printf("[DEBUG] inserted\n");
  for (int i = 0; i < TABLE->size; i++) {
    printf("<var name:%s, reg num:%d, scope:%d>\n", TABLE->table[i].name,
           TABLE->table[i].regnum, TABLE->table[i].scope);
  }
  printf("\n");
#endif
}

row* lookup(char* aName) {
  for (int i = 0; i < TABLE->size; i++) {
    if (strcmp(TABLE->table[i].name, aName) == 0) {
#ifdef DEBUG
      printf("[DEBUG] found\n");
      printf("<var name:%s, reg num:%d, scope:%d>\n\n", TABLE->table[i].name,
             TABLE->table[i].regnum, TABLE->table[i].scope);
#endif

      return &(TABLE->table[i]);
    }
  }

#ifdef DEBUG
  printf("[DEBUG] not found\n\n");
#endif

  return NULL;
}

void delete () {
  for (int i = TABLE->size - 1; i >= 0; i--) {
    if (TABLE->table[i].scope == GLOBAL_VAR ||
        TABLE->table[i].scope == PROC_NAME) {
      TABLE->size = i;
      break;
    }
  }

#ifdef DEBUG
  printf("[DEBUG] deleted\n");
  for (int i = 0; i < TABLE->size; i++) {
    printf("<var name:%s, reg num:%d, scope:%d>\n", TABLE->table[i].name,
           TABLE->table[i].regnum, TABLE->table[i].scope);
  }
  printf("\n");
#endif
}
