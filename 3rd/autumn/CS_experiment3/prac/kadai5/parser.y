%{
/*
 * parser; Parser for PL-0
 */

#define MAXLENGTH 16

#include <stdio.h>
#include <string.h>

#include "symtab.h"
#include "llvmcommands.h"

int yyparse();
int yyerror(char *);

extern int yylineno;
extern char *yytext;

int gRegnum;
Scope gScope;
int gLabelNum;

%}

%union {
    int num;
    char ident[MAXLENGTH+1];
}

%token SBEGIN DO ELSE SEND
%token FOR FORWARD FUNCTION IF PROCEDURE
%token PROGRAM READ THEN TO VAR
%token WHILE WRITE

%left PLUS MINUS
%left MULT DIV

%token EQ NEQ LE LT GE GT
%token LPAREN RPAREN LBRACKET RBRACKET
%token COMMA SEMICOLON COLON INTERVAL
%token PERIOD ASSIGN
%token <num> NUMBER
%token <ident> IDENT

%%

program
        :PROGRAM IDENT SEMICOLON
        {
                fundecl_init();
                code_init();
                fstack_init();
                symtab_init();

                gScope = GLOBAL_VAR;
                gRegnum = 2;
                gLabelNum = 0;

                symtab_push($2, gRegnum, gScope);

                fundecl_add("__GlobalDecl", 0);
        }
          outblock PERIOD
        {
                print_LLVM_code();
        }
        ;

outblock
        : var_decl_part subprog_decl_part
        {
                fundecl_add("main", 0);
        }
         statement
        ;

var_decl_part
        : /* empty */
        | var_decl_list SEMICOLON
        ;

var_decl_list
        : var_decl_list SEMICOLON var_decl
        | var_decl
        ;

var_decl
        : VAR id_list
        ;

subprog_decl_part
        : /* empty */
        | subprog_decl_list SEMICOLON
        ;

subprog_decl_list
        : subprog_decl
        | subprog_decl_list SEMICOLON subprog_decl
        ;

subprog_decl
        : proc_decl
        ;

proc_decl
        : PROCEDURE proc_name SEMICOLON inblock
        {
                gScope = GLOBAL_VAR;
                symtab_delete();
        }
        ;

proc_name
        : IDENT
        {
                symtab_push($1, gRegnum, PROC_NAME);
                Row *tRow = symtab_lookup($1);

                fundecl_add(tRow->name, 0);

                gScope = LOCAL_VAR;
        }
        ;

inblock
        : var_decl_part statement
        ;

statement_list
        : statement
        | statement_list SEMICOLON statement
        ;

statement
        : assignment_statement
        | if_statement
        | while_statement
        | for_statement
        | proc_call_statement
        | null_statement
        | block_statement
        | read_statement
        | write_statement
        ;

assignment_statement
        : IDENT ASSIGN expression
        {
                Row *tRow = symtab_lookup($1);
                factor_push(tRow->name, tRow->regnum, tRow->type);
                Factor *tArg2 = factor_pop();
                Factor *tArg1 = factor_pop();

                code_add(code_create(Store, tArg1, tArg2, NULL, 0));
        }
        ;

if_statement
        : IF condition THEN
        {
                Factor *tCondition = factor_pop();

                factor_push("", 0, LABEL);
                Factor *tLabel1 = factor_pop(); // バックパッチであとで正しい値をつける

                factor_push("", gLabelNum, LABEL);
                Factor *tLabel2 = factor_pop(); // 捨てラベル(icmpのfalseのときに飛ぶラベルを直後に置く)
                gLabelNum++;

                LLVMcode *tCode = code_create(BrCond, tLabel1, tLabel2, tCondition, 0);
                br_push(tCode); // あとでバックパッチするためのbr命令スタックに積む
                code_add(tCode);
                code_add(code_create(Label, tLabel2, NULL, NULL, 0)); // 捨てラベルコード生成
        }
         statement
        {
                factor_push("", 0, LABEL);
                Factor *tLabel1 = factor_pop();
                LLVMcode *tBrCode = code_create(BrUncond, tLabel1, NULL, NULL, 0);

                br_back_patch(gLabelNum); // 今回のBr命令を積むより先にthenから飛んでくるやつをバックパッチ
                factor_push("", gLabelNum, LABEL);
                Factor *tLabel2 = factor_pop();
                gLabelNum++;

                br_push(tBrCode);

                code_add(tBrCode);
                code_add(code_create(Label, tLabel2, NULL, NULL, 0));
        }
         else_statement
        {
                br_back_patch(gLabelNum);
                factor_push("", gLabelNum, LABEL);
                Factor *tLabel = factor_pop();
                gLabelNum++;

                code_add(code_create(Label, tLabel, NULL, NULL, 0));
        }
        ;

else_statement
        : /* empty */
        | ELSE statement
        ;

while_statement
        : WHILE condition DO statement
        ;

for_statement
        : FOR IDENT
        {
                symtab_lookup($2);
        }
          ASSIGN expression TO expression DO statement
        ;

proc_call_statement
        : proc_call_name
        ;

proc_call_name
        : IDENT
        {
                symtab_lookup($1);
        }
        ;

block_statement
        : SBEGIN statement_list SEND
        ;

read_statement
        : READ LPAREN IDENT RPAREN
        {
                symtab_lookup($3);
        }
        ;

write_statement
        : WRITE LPAREN expression RPAREN
        ;

null_statement
        : /* empty */
        ;

condition
        : expression EQ expression
        {
                // 四則演算と大体一緒
                Factor *tArg2 = factor_pop();
                Factor *tArg1 = factor_pop();
                Factor *tRetval = factor_push("", gRegnum, LOCAL_VAR);
                gRegnum++;
                code_add(code_create(Icmp, tArg1, tArg2, tRetval, EQUAL));
        }
        | expression NEQ expression
        {
                Factor *tArg2 = factor_pop();
                Factor *tArg1 = factor_pop();
                Factor *tRetval = factor_push("", gRegnum, LOCAL_VAR);
                gRegnum++;
                code_add(code_create(Icmp, tArg1, tArg2, tRetval, NE));
        }
        | expression GT expression
        {
                Factor *tArg2 = factor_pop();
                Factor *tArg1 = factor_pop();
                Factor *tRetval = factor_push("", gRegnum, LOCAL_VAR);
                gRegnum++;
                code_add(code_create(Icmp, tArg1, tArg2, tRetval, SGT));
        }
        | expression GE expression
        {
                Factor *tArg2 = factor_pop();
                Factor *tArg1 = factor_pop();
                Factor *tRetval = factor_push("", gRegnum, LOCAL_VAR);
                gRegnum++;
                code_add(code_create(Icmp, tArg1, tArg2, tRetval, SGE));
        }
        | expression LT expression
        {
                Factor *tArg2 = factor_pop();
                Factor *tArg1 = factor_pop();
                Factor *tRetval = factor_push("", gRegnum, LOCAL_VAR);
                gRegnum++;
                code_add(code_create(Icmp, tArg1, tArg2, tRetval, SLT));
        }
        | expression LE expression
        {
                Factor *tArg2 = factor_pop();
                Factor *tArg1 = factor_pop();
                Factor *tRetval = factor_push("", gRegnum, LOCAL_VAR);
                gRegnum++;
                code_add(code_create(Icmp, tArg1, tArg2, tRetval, SLE));
        }
        ;

expression
        : term
        | PLUS term
        {
                Factor *tArg2 = factor_pop();
                // 単項演算はゼロからの足し引きで表現。
                factor_push("", 0, CONSTANT);
                Factor *tArg1 = factor_pop();
                Factor *tRetval = factor_push("", gRegnum, LOCAL_VAR);
                gRegnum++;
                code_add(code_create(Add, tArg1, tArg2, tRetval, 0));
        }
        | MINUS term
        {
                Factor *tArg2 = factor_pop();
                factor_push("", 0, CONSTANT);
                Factor *tArg1 = factor_pop();
                Factor *tRetval = factor_push("", gRegnum, LOCAL_VAR);
                gRegnum++;
                code_add(code_create(Sub, tArg1, tArg2, tRetval, 0));
        }
        | expression PLUS expression
        {
                // 四則演算は、全部これと一緒

                // オペランドをポップする(順番に注意)
                Factor *tArg2 = factor_pop();
                Factor *tArg1 = factor_pop();

                // 代入先として局所変数を用意、popしないことで、次のオペランドとしてもそのまま使える
                Factor *tRetval = factor_push("", gRegnum, LOCAL_VAR);
                gRegnum++;

                // Factorからのコード生成と追加を同時に行う
                code_add(code_create(Add, tArg1, tArg2, tRetval, 0));
        }
        | expression MINUS expression
        {
                Factor *tArg2 = factor_pop();
                Factor *tArg1 = factor_pop();
                Factor *tRetval = factor_push("", gRegnum, LOCAL_VAR);
                gRegnum++;
                code_add(code_create(Sub, tArg1, tArg2, tRetval, 0));
        }
        ;

term
        : factor
        | term MULT factor
        {
                Factor *tArg2 = factor_pop();
                Factor *tArg1 = factor_pop();
                Factor *tRetval = factor_push("", gRegnum, LOCAL_VAR);
                gRegnum++;
                code_add(code_create(Mul, tArg1, tArg2, tRetval, 0));
        }
        | term DIV factor
        {
                Factor *tArg2 = factor_pop();
                Factor *tArg1 = factor_pop();
                Factor *tRetval = factor_push("", gRegnum, LOCAL_VAR);
                gRegnum++;
                code_add(code_create(Sdiv, tArg1, tArg2, tRetval, 0));
        }
        ;

factor
        : var_name
        | NUMBER
        {
                factor_push("const", $1, CONSTANT);
        }
        | LPAREN expression RPAREN
        ;

var_name
        : IDENT
        {
                Row* tRaw = symtab_lookup($1);

                factor_push(tRaw->name, tRaw->regnum, tRaw->type);
                Factor *tArg1 = factor_pop();
                Factor *tRetval = factor_push("", gRegnum, LOCAL_VAR);
                gRegnum++;

                code_add(code_create(Load, tArg1, NULL, tRetval, 0));
        }
        ;

arg_list
        : expression
        | arg_list COMMA expression
        ;

id_list
        : IDENT
        {
                // 大域変数と局所変数の場合で処理分けた
                // 局所だと、レジスタ番号をSSAで管理する必要がある
                LLVMcommand tCommand;
                if(gScope == GLOBAL_VAR){
                        tCommand = Global;
                        symtab_push($1, 0, gScope);
                } else{
                        tCommand = Alloca;
                        symtab_push($1, gRegnum, gScope);
                        gRegnum++;
                }

                Row *tRow = symtab_lookup($1);

                factor_push(tRow->name, tRow->regnum, gScope);
                Factor *tRetval = factor_pop();

                code_add(code_create(tCommand,NULL,NULL,tRetval, 0));
        }
        | id_list COMMA IDENT
        {
                LLVMcommand tCommand;
                if(gScope == GLOBAL_VAR){
                        tCommand = Global;
                        symtab_push($3, 0, gScope);
                } else{
                        tCommand = Alloca;
                        symtab_push($3, gRegnum, gScope);
                        gRegnum++;
                }

                Row *tRow = symtab_lookup($3);

                factor_push(tRow->name, tRow->regnum, gScope);
                Factor *tRetval = factor_pop();

                code_add(code_create(tCommand,NULL,NULL,tRetval, 0));
        }
        ;


%% 
int yyerror(char *s)
{
  fprintf(stderr, "%s\n", s);
  fprintf(stderr, "%s\n", yytext);
  fprintf(stderr, "%d\n", yylineno);
  return yylineno;
}
