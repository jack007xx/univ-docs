#include "symtab.h"

#include <stdio.h>
#include <string.h>

#define DEBUG
/* 記号表の実体をここで作成 */
/* parser.yからは，以下のinsert/lookup/deleteなどを通してアクセスする */

/* insert, lookup, deleteの実装 */

SYMTAB* TABLE;

void init() {
  row tRows[10000];
  SYMTAB table = {tRows, 0};

#ifdef DEBUG
  printf("[DEBUG] new symbol table created\n");
#endif

  TABLE = &table;
}

void insert(SYMTAB* aTable, char* aName, int aRegnum, Scope aScope) {
  row tRow = {aName, aRegnum, aScope};
  aTable->table[aTable->size] = tRow;

  strcpy(aTable->table[aTable->size].name, aName);

  aTable->size++;

#ifdef DEBUG
  printf("[DEBUG] inserted\n");
  for (int i = 0; i < aTable->size; i++) {
    printf("<var name:%s, reg num:%d, scope:%d>\n", aTable->table[i].name,
           aTable->table[i].regnum, aTable->table[i].scope);
  }
  printf("\n");
#endif
}

row* lookup(SYMTAB* aTable, char* aName) {
  for (int i = 0; i < aTable->size; i++) {
    if (strcmp(aTable->table[i].name, aName) == 0) {
#ifdef DEBUG
      printf("[DEBUG] found\n");
      printf("<var name:%s, reg num:%d, scope:%d>\n\n", aTable->table[i].name,
             aTable->table[i].regnum, aTable->table[i].scope);
#endif

      return &(aTable->table[i]);
    }
  }

#ifdef DEBUG
  printf("[DEBUG] not found\n\n");
#endif

  return NULL;
}

void delete (SYMTAB* aTable) {
  for (int i = aTable->size - 1; i >= 0; i--) {
    if (aTable->table[i].scope == GLOBAL_VAR ||
        aTable->table[i].scope == PROC_NAME) {
      aTable->size = i;
      break;
    }
  }

#ifdef DEBUG
  printf("[DEBUG] deleted\n");
  for (int i = 0; i < aTable->size; i++) {
    printf("<var name:%s, reg num:%d, scope:%d>\n", aTable->table[i].name,
           aTable->table[i].regnum, aTable->table[i].scope);
  }
  printf("\n");
#endif
}
