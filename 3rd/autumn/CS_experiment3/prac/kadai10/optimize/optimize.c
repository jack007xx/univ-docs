#include <stdio.h>
#include <stdlib.h>

#include "../llvm_code/factor.h"
#include "../llvm_code/llvm.h"

int const_calc();
int block();

LLVMcode *gStartBlock, *gEndBlock;
Fundecl *gFun;

int optimize_all(Fundecl *aFuncs) {
  for (Fundecl *tFunPointer = aFuncs; tFunPointer != NULL;
       tFunPointer = tFunPointer->next) {
    gFun = tFunPointer;
    gStartBlock = NULL;
    for (LLVMcode *tCodePointer = tFunPointer->codes; tCodePointer != NULL;
         tCodePointer = tCodePointer->next) {
      if (tCodePointer->command == Label || tCodePointer->next == NULL) {
        gEndBlock = tCodePointer->next;
        block();

        gStartBlock = tCodePointer;
      }
    }
  }

  return 0;
}

// aStartはスタート位置の一個前
// aEndは終わりの一個次
int block() {
  while (const_calc() != 0) {
  }

  return 0;
}

// aStartはスタート位置の一個前
// aEndは終わりの一個次
int const_calc() {
  int isDel = 0;
  int tOpt = 0;
  LLVMcode *tPrev = gStartBlock;
  LLVMcode *tCodePointer;
  if (gStartBlock == NULL)
    tCodePointer = gFun->codes;
  else
    tCodePointer = gStartBlock->next;

  for (; tCodePointer != gEndBlock; tCodePointer = tCodePointer->next) {
    isDel = 0;
    // オペランドが整数のみからなるか判定
    if (tCodePointer->command == Add &&
        tCodePointer->args.add.arg1->type == CONSTANT &&
        tCodePointer->args.add.arg2->type == CONSTANT) {
      Factor *tRetval = tCodePointer->args.add.retval;
      tRetval->val =
          tCodePointer->args.add.arg1->val + tCodePointer->args.add.arg2->val;
      tRetval->type = CONSTANT;
      isDel = 1;
      tOpt++;
    } else if (tCodePointer->command == Sub &&
               tCodePointer->args.sub.arg1->type == CONSTANT &&
               tCodePointer->args.sub.arg2->type == CONSTANT) {
      Factor *tRetval = tCodePointer->args.sub.retval;
      tRetval->val =
          tCodePointer->args.sub.arg1->val - tCodePointer->args.sub.arg2->val;
      tRetval->type = CONSTANT;
      isDel = 1;
      tOpt++;
    } else if (tCodePointer->command == Mul &&
               tCodePointer->args.mul.arg1->type == CONSTANT &&
               tCodePointer->args.mul.arg2->type == CONSTANT) {
      Factor *tRetval = tCodePointer->args.mul.retval;
      tRetval->val =
          tCodePointer->args.mul.arg1->val * tCodePointer->args.mul.arg2->val;
      tRetval->type = CONSTANT;
      isDel = 1;
      tOpt++;
    } else if (tCodePointer->command == Sdiv &&
               tCodePointer->args.sdiv.arg1->type == CONSTANT &&
               tCodePointer->args.sdiv.arg2->type == CONSTANT) {
      Factor *tRetval = tCodePointer->args.sdiv.retval;
      tRetval->val =
          tCodePointer->args.sdiv.arg1->val + tCodePointer->args.sdiv.arg2->val;
      tRetval->type = CONSTANT;
      isDel = 1;
      tOpt++;
    }

    // コード削除
    if (isDel == 1) {
      if (tPrev == NULL)
        gFun->codes = tCodePointer->next;
      else
        tPrev->next = tCodePointer->next;
    }
    tPrev = tCodePointer;
  }

  return tOpt;
}
