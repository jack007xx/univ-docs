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

FILE *gFile;

void fundecl_init() { gDeclhd = gDecltl = NULL; }

void fundecl_add(char *aName) {
  Fundecl *tFun = malloc(sizeof(Fundecl));
  strcpy(tFun->fname, aName);
  tFun->arity = 0;

  tFun->codes = gCodehd;
  code_init();

  if (gDeclhd == NULL)
    gDecltl = gDeclhd = tFun;
  else
    gDecltl = gDecltl->next = tFun;
}

void procdecl_add(char *aName) {
  fundecl_add(aName);
  gDecltl->is_proc = 1;
}

void fundecl_add_arg(Factor *aArg) {
  gDecltl->args[gDecltl->arity] = aArg;
  gDecltl->arity++;
}

int fundecl_add_arg_code() {
  int tRegnum = gDecltl->arity + 1;
  for (int i = 0; i < gDecltl->arity; i++) {
    Factor *tArg = gDecltl->args[i];
    symtab_push(tArg->vname, tRegnum++, LOCAL_VAR);
    Row *tRow = symtab_lookup(tArg->vname);

    factor_push(tRow->name, tRow->regnum, tRow->type);
    Factor *tVArg = factor_pop();

    // 引数を仮引数として持ってくる
    code_add(code_create(Alloca, NULL, NULL, tVArg, 0));
    code_add(code_create(Store, gDecltl->args[i], tVArg, NULL, 0));
  }
  return tRegnum;
}

int fundecl_lookup(char *aFunNeme) {
  for (Fundecl *tFundeclPointer = gDeclhd; tFundeclPointer != NULL;
       tFundeclPointer = tFundeclPointer->next)
    if (strcmp(tFundeclPointer->fname, aFunNeme) == 0)
      return tFundeclPointer->arity;

  return 0;
}

char *ito_instruction[] = {"alloca", "global", "load",   "store", "add",
                           "sub",    "mul",    "sdiv",   "icmp",  "br",
                           "brc",    "call",   "label",  "ret",   "phi",
                           "write",  "read",   "comment"};
char *ito_cmp_type[] = {"eq", "ne", "sgt", "sge", "slt", "sle"};

void code_init() { gCodehd = gCodetl = NULL; }

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
      tCode->args.call.proc_args = malloc(sizeof(Factor *) * 10);
      break;
    case Label:
      tCode->args.label.arg1 = aArg1;
      break;
    case Ret:
      tCode->args.ret.arg1 = aArg1;
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
    case Gep:
      tCode->args.gep.arg1 = aArg1;
      tCode->args.gep.ind = aArg2;
      tCode->args.gep.retval = aRetval;
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

#ifdef DEBUG
  printf("%s\n", ito_instruction[aCode->command]);
#endif
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
    case PROC_NAME:
      sprintf(aArg, "@%s", aFactor->vname);
      break;
    case FUNC_NAME:
      sprintf(aArg, "@%s", aFactor->vname);
      break;
    case CONSTANT:
      sprintf(aArg, "%d", aFactor->val);
      break;
    case LABEL:
      sprintf(aArg, "%d", aFactor->val);
      break;
    case LOCAL_ARRAY:
      sprintf(aArg, "%%%d", aFactor->val);
      break;
    case GLOBAL_ARRAY:
      sprintf(aArg, "@%s", aFactor->vname);
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
      if (aCode->args.alloca.retval->type == LOCAL_ARRAY) {
        fprintf(gFile, "\t%s = alloca [%d x i32], align %d ; Allocate for %s\n",
                tRetval, aCode->args.alloca.retval->size,
                aCode->args.alloca.retval->size * 4,
                aCode->args.alloca.retval->vname);
      } else {
        fprintf(gFile, "\t%s = alloca i32, align 4 ; Allocate for %s\n",
                tRetval, aCode->args.alloca.retval->vname);
      }
      break;
    case Global:
      factor_encode(aCode->args.global.retval, tRetval);
      if (aCode->args.global.retval->type == GLOBAL_ARRAY) {
        fprintf(gFile,
                "%s = common dso_local global [%d x i32] zeroinitializer, "
                "align 4\n",
                tRetval, aCode->args.global.retval->size);
      } else {
        fprintf(gFile, "%s = common global i32 0, align 4\n", tRetval);
      }
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

      if (aCode->args.call.retval == NULL) {
        fprintf(gFile, "\tcall void %s(", tArg1);
      } else {
        factor_encode(aCode->args.call.retval, tRetval);
        fprintf(gFile, "\t%s = call i32 %s(", tRetval, tArg1);
      }

      // 引数配置
      // todo ->size
      int tArity = fundecl_lookup(aCode->args.call.arg1->vname);
      for (int i = 0; i < tArity; i++) {
        factor_encode(aCode->args.call.proc_args[i], tArg2);
        fprintf(gFile, "i32 %s", tArg2);
        if (i != tArity - 1) fprintf(gFile, ", ");
      }
      fprintf(gFile, ")\n");
      break;
    case Label:
      factor_encode(aCode->args.label.arg1, tArg1);
      fprintf(gFile, "\n; <%s>:%s:\n", aCode->args.label.arg1->vname, tArg1);
      break;
    case Ret:
      if (aCode->args.ret.arg1 == NULL) {
        fprintf(gFile, "\tret void\n");
      } else {
        factor_encode(aCode->args.ret.arg1, tArg1);
        fprintf(gFile, "\tret i32 %s\n", tArg1);
      }
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
    case Gep:
      factor_encode(aCode->args.gep.arg1, tArg1);
      factor_encode(aCode->args.gep.ind, tArg2);
      factor_encode(aCode->args.gep.retval, tRetval);
      fprintf(
          gFile,
          "\t%s = getelementptr inbounds [%d x i32], [%d x i32]* %s, i32 0, "
          "i32 %s\n",
          tRetval, aCode->args.gep.arg1->size, aCode->args.gep.arg1->size,
          tArg1, tArg2);
      break;
    default:
      break;
  }
}

// プライベート
// 引数付きの関数定義を生成する
void pprint_funchd(Fundecl *aFun, char *aFunhd) {
  if (aFun->is_proc)
    sprintf(aFunhd, "define void @%s(", aFun->fname);
  else
    sprintf(aFunhd, "define i32 @%s(", aFun->fname);

  for (int i = 0; i < aFun->arity; i++) {
    char t[256];
    sprintf(t, "i32 %%%d", aFun->args[i]->val);
    strcat(aFunhd, t);
    if (i != aFun->arity - 1) strcat(aFunhd, ", ");
  }
  strcat(aFunhd, "){\n");
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
    if (tFunPointer != gDeclhd) {
      char tFunhdStr[256];
      pprint_funchd(tFunPointer, tFunhdStr);
      fprintf(gFile, "%s", tFunhdStr);
    }
    // 関数の中のコード読み切るまでブン回す
    for (LLVMcode *tCodePointer = tFunPointer->codes; tCodePointer != NULL;
         tCodePointer = tCodePointer->next)
      print_code(tCodePointer);

    // 初回のfundeclは大域変数の定義に当てられる
    if (tFunPointer != gDeclhd) fprintf(gFile, "}\n");
    fprintf(gFile, "\n");
  }

#ifdef TOFILE
  fclose(gFile);
#endif
};
