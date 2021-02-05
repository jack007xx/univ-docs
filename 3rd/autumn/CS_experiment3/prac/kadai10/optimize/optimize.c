#include <stdio.h>
#include <stdlib.h>

#include "../llvm_code/factor.h"
#include "../llvm_code/llvm.h"

int block(LLVMcode *, LLVMcode *);

Fundecl *gFun;
// 以下startは基本ブロックの一個前、endは一個後ろの命令を表す。

int optimize_all(Fundecl *aFuncs) {
  for (Fundecl *tFunPointer = aFuncs; tFunPointer != NULL;
       tFunPointer = tFunPointer->next) {
    gFun = tFunPointer;
    LLVMcode *tStart = NULL;
    for (LLVMcode *tCodePointer = tFunPointer->codes; tCodePointer != NULL;
         tCodePointer = tCodePointer->next) {
      if (tCodePointer->command == Label || tCodePointer->next == NULL) {
        block(tStart, tCodePointer->next);
        tStart = tCodePointer;
      }
    }
  }

  return 0;
}

// aStartはスタート位置の一個前
// aEndは終わりの一個次
int const_calc(LLVMcode *aStart, LLVMcode *aEnd) {
  int isDel = 0;
  int tOpt = 0;
  LLVMcode *tPrev = aStart;
  LLVMcode *tCodePointer;
  if (aStart == NULL)
    tCodePointer = gFun->codes;
  else
    tCodePointer = aStart->next;

  for (; tCodePointer != aEnd; tCodePointer = tCodePointer->next) {
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

// 階乗をシフトにする。
// 2^0~2^32までカバーしている(はず。)
int divn2_to_shift(LLVMcode *aStart, LLVMcode *aEnd) {
  int n2[32];
  for (int i = n2[0] = 1; i < 32; i++) n2[i] = n2[i - 1] * 2;
  LLVMcode *tPrev = aStart;  // つなぎ直し用

  LLVMcode *tCodePointer = (aStart == NULL) ? gFun->codes : aStart->next;
  for (; tCodePointer != aEnd; tCodePointer = tCodePointer->next) {
    if (tCodePointer->command == Sdiv &&
        tCodePointer->args.sdiv.arg2->type == CONSTANT)
      for (int i = 0; i < 32; i++)
        if (tCodePointer->args.sdiv.arg2->val == n2[i]) {
          // free命令使ってシフトコード追加
          char *tFreeInst = malloc(sizeof(char) * 512);
          int tSource = tCodePointer->args.sdiv.arg1->val;
          int tTarget = tCodePointer->args.sdiv.retval->val;
          sprintf(tFreeInst,
                  "\n\t;[OPTIMIZED]\n"
                  "\t;div 2^n -> sift-R n\n"
                  "\t%%o%d.1 = ashr i32 %%o%d, 31\n"
                  "\t%%o%d.2 = add i32 %%o%d, %%o%d.1\n"
                  "\t%%o%d = ashr i32 %%o%d.2, %d\n\n",
                  tSource, tSource, tSource, tSource, tSource, tTarget, tSource,
                  i);
          factor_push(tFreeInst, 0, CONSTANT);
          LLVMcode *tNewCode = code_create(Free, factor_pop(), NULL, NULL, 0);
          if (tPrev == NULL)
            gFun->codes = tNewCode;
          else
            tPrev->next = tNewCode;

          tNewCode->next = tCodePointer->next;
        }
    tPrev = (tPrev == NULL) ? gFun->codes : tPrev->next;
  }
}

// 3での除算を、マジックナンバー使った乗算にする。
int div3_to_mul(LLVMcode *aStart, LLVMcode *aEnd) {
  LLVMcode *tPrev = aStart;  // つなぎ直し用

  LLVMcode *tCodePointer = (aStart == NULL) ? gFun->codes : aStart->next;
  for (; tCodePointer != aEnd; tCodePointer = tCodePointer->next) {
    if (tCodePointer->command == Sdiv &&
        tCodePointer->args.sdiv.arg2->type == CONSTANT &&
        tCodePointer->args.sdiv.arg2->val == 3) {
      // free命令使ってシフトコード追加
      char *tFreeInst = malloc(sizeof(char) * 512);
      int tSource = tCodePointer->args.sdiv.arg1->val;
      int tTarget = tCodePointer->args.sdiv.retval->val;
      sprintf(tFreeInst,
              "\n\t;[OPTIMIZED]\n"
              "\t;div 3 -> sift hogehoge\n"
              "\t%%o%d.1 = sext i32 %%o%d to i64\n"
              "\t%%o%d.2 = ashr i64 %%o%d.1, 31\n"
              "\t%%o%d.3 = mul i64 %%o%d.1, 1431655766\n"
              "\t%%o%d.4 = ashr i64 %%o%d.3, 32\n"
              "\t%%o%d.5 = sub i64 %%o%d.4, %%o%d.2\n"
              "\t%%o%d = trunc i64 %%o%d.5 to i32\n\n",
              tSource, tSource, tSource, tSource, tSource, tSource, tSource,
              tSource, tSource, tSource, tSource, tTarget, tSource);
      factor_push(tFreeInst, 0, CONSTANT);
      LLVMcode *tNewCode = code_create(Free, factor_pop(), NULL, NULL, 0);
      if (tPrev == NULL)
        gFun->codes = tNewCode;
      else
        tPrev->next = tNewCode;

      tNewCode->next = tCodePointer->next;
    }

    tPrev = (tPrev == NULL) ? gFun->codes : tPrev->next;
  }
  return 0;
}

// aStartはスタート位置の一個前
// aEndは終わりの一個次
int block(LLVMcode *aStart, LLVMcode *aEnd) {
  while (const_calc(aStart, aEnd) != 0) {
  }
  divn2_to_shift(aStart, aEnd);
  div3_to_mul(aStart, aEnd);

  return 0;
}
