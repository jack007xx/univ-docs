#include "llvm.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define DEBUG
#define TOFILE

void print_code(LLVMcode *aCode);

// 命令列の前後のアドレスを保持するポインタ
LLVMcode *gCodehd, *gCodetl;

// 関数定義の線形リストの前後アドレスを保持するポインタ
Fundecl *gDeclhd, *gDecltl;

FILE *gFile;  // 出力先

void fundecl_init() { gDeclhd = gDecltl = NULL; }

void fundecl_add(char *aName, unsigned aArity) {
  Fundecl *tFun = malloc(sizeof(Fundecl));
  strcpy(tFun->fname, aName);
  tFun->arity = aArity;

  tFun->codes = gCodehd;
  code_init();

  if (gDeclhd == NULL)
    gDecltl = gDeclhd = tFun;
  else
    gDecltl = gDecltl->next = tFun;
}

void code_init() { gCodehd = gCodetl = NULL; }

LLVMcode *code_create(LLVMcommand aCommand, Factor *aArg1, Factor *aArg2,
                      Factor *aRetval) {
  LLVMcode *tCode = malloc(sizeof(LLVMcode));
  tCode->command = aCommand;
  switch (aCommand) {
    case Alloca:
      tCode->args.alloca.retval = aRetval;
      break;
    case Global:
      tCode->args.global.retval = aRetval;
      break;
    case Load:
      tCode->args.load.arg1 = aArg1;
      tCode->args.load.retval = aRetval;
      break;
    case Store:
      tCode->args.store.arg1 = aArg1;
      tCode->args.store.arg2 = aArg2;
      break;
    case Add:
      tCode->args.add.arg1 = aArg1;
      tCode->args.add.arg2 = aArg2;
      tCode->args.add.retval = aRetval;
      break;
    case Sub:
      tCode->args.sub.arg1 = aArg1;
      tCode->args.sub.arg2 = aArg2;
      tCode->args.sub.retval = aRetval;
      break;
    case Mul:
      tCode->args.mul.arg1 = aArg1;
      tCode->args.mul.arg2 = aArg2;
      tCode->args.mul.retval = aRetval;
      break;
    case Sdiv:
      tCode->args.sdiv.arg1 = aArg1;
      tCode->args.sdiv.arg2 = aArg2;
      tCode->args.sdiv.retval = aRetval;
      break;
    default:
      break;
  }
  return tCode;
}

void code_add(LLVMcode *aCode) {
  // aCodeの内容は変更される可能性がある

  if (gCodetl == NULL && gDecltl == NULL)
    fprintf(stderr, "[ERROR] unexpected error\n");

  aCode->next = NULL;
  if (gCodetl == NULL)  // 解析中の関数の最初の命令の場合
    gCodetl = gCodehd = gDecltl->codes = aCode;
  else  // 解析中の関数の命令列に1つ以上命令が存在する場合
    gCodetl = gCodetl->next = aCode;
}

// プライベート関数
// localとか、globalとか、条件によってそのFactorを示す表記が違う
void factor_encode(Factor *aFactor, char *aArg) {
  switch (aFactor->type) {
    case GLOBAL_VAR:
      sprintf(aArg, "@%s", aFactor->vname);
      break;
    case LOCAL_VAR:
      sprintf(aArg, "%%%d", aFactor->val);
      break;
    case CONSTANT:
      sprintf(aArg, "%d", aFactor->val);
      break;
    case LABEL:
      sprintf(aArg, "%d", aFactor->val);
      break;
    default:
      break;
  }
}

// プライベート関数
// 1命令単位で実際のLLVMコードを出力する
void print_code(LLVMcode *aCode) {
  // Factorをいい感じのstr表現にしたいので、エンコしてから利用する
  char tArg1[256], tArg2[256], tRetval[256];

  switch (aCode->command) {
    case Alloca:
      factor_encode(aCode->args.alloca.retval, tRetval);
      fprintf(gFile, "\t%s = alloca i32, align 4 ; Allocate for %s\n", tRetval,
              aCode->args.alloca.retval->vname);
      break;
    case Global:
      factor_encode(aCode->args.global.retval, tRetval);
      fprintf(gFile, "%s = common global i32 0, align 4\n", tRetval);
      break;
    case Load:
      factor_encode(aCode->args.load.arg1, tArg1);
      factor_encode(aCode->args.load.retval, tRetval);
      fprintf(gFile, "\t%s = load i32, i32* %s, align 4\n", tRetval, tArg1);
      break;
    case Store:
      factor_encode(aCode->args.store.arg1, tArg1);
      factor_encode(aCode->args.store.arg2, tArg2);
      fprintf(gFile, "\tstore i32 %s, i32* %s, align 4\n", tArg1, tArg2);
      break;
    case Add:
      factor_encode(aCode->args.add.arg1, tArg1);
      factor_encode(aCode->args.add.arg2, tArg2);
      factor_encode(aCode->args.add.retval, tRetval);
      fprintf(gFile, "\t%s = add nsw i32 %s, %s\n", tRetval, tArg1, tArg2);
      break;
    case Sub:
      factor_encode(aCode->args.sub.arg1, tArg1);
      factor_encode(aCode->args.sub.arg2, tArg2);
      factor_encode(aCode->args.sub.retval, tRetval);
      fprintf(gFile, "\t%s = sub nsw i32 %s, %s\n", tRetval, tArg1, tArg2);
      break;
    case Mul:
      factor_encode(aCode->args.mul.arg1, tArg1);
      factor_encode(aCode->args.mul.arg2, tArg2);
      factor_encode(aCode->args.mul.retval, tRetval);
      fprintf(gFile, "\t%s = mul nsw i32 %s, %s\n", tRetval, tArg1, tArg2);
      break;
    case Sdiv:
      factor_encode(aCode->args.sdiv.arg1, tArg1);
      factor_encode(aCode->args.sdiv.arg2, tArg2);
      factor_encode(aCode->args.sdiv.retval, tRetval);
      fprintf(gFile, "\t%s = sdiv i32 %s, %s\n", tRetval, tArg1, tArg2);
      break;
    default:
      break;
  }
}

void print_LLVM_code() {
  gFile = stdout;
#ifdef TOFILE
  gFile = fopen("result.ll", "w");
#endif

  for (Fundecl *tFunPointer = gDeclhd; tFunPointer != NULL;
       tFunPointer = tFunPointer->next) {
    // 初回のfundeclは大域変数の定義に当てられる
    if (tFunPointer != gDeclhd)
      fprintf(gFile, "define i32 @%s(){\n", tFunPointer->fname);

    // 関数の中のコード読み切るまでブン回す
    for (LLVMcode *tCodePointer = tFunPointer->codes; tCodePointer != NULL;
         tCodePointer = tCodePointer->next)
      print_code(tCodePointer);

    // 初回のfundeclは大域変数の定義に当てられる
    if (tFunPointer != gDeclhd) fprintf(gFile, "\tret i32 0\n}\n");
    fprintf(gFile, "\n");
  }

#ifdef TOFILE
  fclose(gFile);
#endif
};
