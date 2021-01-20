#include "llvm.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define DEBUG
// #define TOFILE

void print_code(LLVMcode *aCode);

/* 命令列の先頭のアドレスを保持するポインタ */
LLVMcode *gCodehd;
/* 命令列の末尾のアドレスを保持するポインタ */
LLVMcode *gCodetl;

/* 関数定義の線形リストの先頭の要素のアドレスを保持するポインタ */
Fundecl *gDeclhd;
/* 関数定義の線形リストの末尾の要素のアドレスを保持するポインタ */
Fundecl *gDecltl;

FILE *gFile;

void fundecl_init() {
  gDeclhd = NULL;
  gDecltl = NULL;
}

// 関数を追加する
void fundecl_add(char *aName, unsigned aArity) {
  Fundecl *tFun = malloc(sizeof(Fundecl));
  strcpy(tFun->fname, aName);
  tFun->arity = aArity;

  tFun->codes = gCodehd;
  code_init();

  if (gDeclhd == NULL) {
    gDeclhd = tFun;
    gDecltl = tFun;
  } else {
    gDecltl->next = tFun;
    gDecltl = tFun;
  }
}

void code_init() {
  // LLVMcode *tInitialCode = (LLVMcode *)malloc(sizeof(LLVMcode));
  gCodehd = NULL;
  gCodetl = NULL;
}

LLVMcode *code_create(LLVMcommand aCommand, Factor *aArg1, Factor *aArg2,
                      Factor *aRetval, Cmptype aIcmpType) {
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
    case Icmp:
      tCode->args.icmp.arg1 = aArg1;
      tCode->args.icmp.arg2 = aArg2;
      tCode->args.icmp.retval = aRetval;
      tCode->args.icmp.type = aIcmpType;
      break;
    case BrUncond:
      tCode->args.bruncond.arg1 = aArg1;
      break;
    case BrCond:
      tCode->args.brcond.arg1 = aArg1;
      tCode->args.brcond.arg2 = aArg2;
      tCode->args.brcond.cond = aRetval;
      break;
    case Call:
      tCode->args.call.arg1 = aArg1;
      tCode->args.call.retval = aRetval;
      break;
    case Label:
      tCode->args.label.arg1 = aArg1;
      break;
    case Ret:
      break;
    case Phi:
      break;
    case Write:
      tCode->args.write.arg1 = aArg1;
      break;
    case Read:
      tCode->args.read.arg1 = aArg1;
      break;
    case Comment:
      tCode->args.comment.arg1 = aArg1;
      break;
    default:
      break;
  }
  return tCode;
}

void code_add(LLVMcode *aCode) {
  // printf("<Factpr poped: command is %d>\n\n", aCode.command);
  // aCodeの内容は変更される可能性がある

  aCode->next = NULL;
  if (gCodetl == NULL) {  // 解析中の関数の最初の命令の場合
    if (gDecltl == NULL) fprintf(stderr, "[ERROR] unexpected error\n");
    gDecltl->codes = aCode;
    gCodehd = gCodetl = aCode;
  } else {  // 解析中の関数の命令列に1つ以上命令が存在する場合
    gCodetl->next = aCode;
    gCodetl = aCode;
  }
}

char *ito_instruction[] = {"alloca", "global", "load", "store", "add", "sub",
                           "mul",    "sdiv",   "icmp", "br",    "brc", "call",
                           "label",  "ret",    "phi",  "write", "read"};
char *ito_cmp_type[] = {"eq", "ne", "sgt", "sge", "slt", "sle"};

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
    case PROC_NAME:
      sprintf(aArg, "@%s()", aFactor->vname);
      break;
    default:
      break;
  }
}

// プライベート関数
// 1命令単位で出力する
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
    case Icmp:
      factor_encode(aCode->args.icmp.arg1, tArg1);
      factor_encode(aCode->args.icmp.arg2, tArg2);
      factor_encode(aCode->args.icmp.retval, tRetval);
      fprintf(gFile, "\t%s = icmp %s i32 %s, %s\n", tRetval,
              ito_cmp_type[aCode->args.icmp.type], tArg1, tArg2);
      break;
    case BrUncond:
      factor_encode(aCode->args.bruncond.arg1, tArg1);
      fprintf(gFile, "\tbr label %%%s\n", tArg1);
      break;
    case BrCond:
      // condの代わりにretvalに入れてる
      factor_encode(aCode->args.brcond.cond, tRetval);
      factor_encode(aCode->args.brcond.arg1, tArg1);
      factor_encode(aCode->args.brcond.arg2, tArg2);
      fprintf(gFile, "\tbr i1 %s, label %%%s, label %%%s\n", tRetval, tArg1,
              tArg2);
      break;
    case Call:
      factor_encode(aCode->args.call.arg1, tArg1);
      factor_encode(aCode->args.call.retval, tRetval);
      fprintf(gFile, "\t%s = call i32 %s\n", tRetval, tArg1);
      break;
    case Label:
      factor_encode(aCode->args.label.arg1, tArg1);
      fprintf(gFile, "\n; <%s>:%s:\n", aCode->args.label.arg1->vname, tArg1);
      break;
    case Ret:
      break;
    case Phi:
      break;
    case Write:
      factor_encode(aCode->args.write.arg1, tArg1);
      fprintf(gFile,
              "\tcall i32 (i8*, ...) @printf(i8* getelementptr inbounds"
              " ([4 x i8], [4 x i8]* @.str.w, i64 0, i64 0), i32 %s)\n",
              tArg1);
      break;
    case Read:
      factor_encode(aCode->args.read.arg1, tArg1);
      fprintf(
          gFile,
          "\tcall i32 (i8*, ...) @__isoc99_scanf(i8* getelementptr inbounds "
          "([3 x i8], [3 x i8]* @.str.r, i64 0, i64 0), i32* %s)\n",
          tArg1);
      break;
    case Comment:
      fprintf(gFile, "\t; %s\n", aCode->args.comment.arg1->vname);
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
  // printf scanfに必要な定義部
  fprintf(gFile,
          "@.str.w = private unnamed_addr constant [4 x i8] c\"%%d\\0A\\00\", "
          "align 1\n"
          "@.str.r = private unnamed_addr constant [3 x i8] c\"%%d\\00\", "
          "align 1\n"
          "declare i32 @printf(i8*, ...)\n"
          "declare i32 @__isoc99_scanf(i8 *, ...)\n\n");

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
