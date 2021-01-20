#include "util.h"

#include <stdlib.h>

BrStack *gBrStack;

void br_push(LLVMcode *aCode) {
  BrStack *tTop = malloc(sizeof(BrStack));
  tTop->code = aCode;
  tTop->next = gBrStack;
  gBrStack = tTop;
}

void br_back_patch(int aLabel) {
  if (gBrStack->code->command == BrCond) {
    if (gBrStack->code->args.brcond.arg1->val == 0) {
      gBrStack->code->args.brcond.arg1->val = aLabel;
    } else if (gBrStack->code->args.brcond.arg2->val == 0) {
      gBrStack->code->args.brcond.arg2->val = aLabel;
    }
    gBrStack = gBrStack->next;
  } else if (gBrStack->code->command == BrUncond) {
    gBrStack->code->args.bruncond.arg1->val = aLabel;
    gBrStack = gBrStack->next;
  }
}
