%{
/*
 * parser; Parser for PL-0
 */

#define MAXLENGTH 16

#include <stdio.h>
#include <string.h>

#include "./symtab/symtab.h"
#include "./llvm_code/llvm.h"
#include "./llvm_code/factor.h"

int yyparse();
int yyerror(char *);

extern int yylineno;
extern char *yytext;

int gRegnum;
Scope gScope;
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
                gRegnum = 1;

                symtab_push($2, 0, gScope);

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
                gRegnum = 1; // 手続きごとにレジスタ番号はリセットされる
                factor_push("Func Retval", gRegnum++, LOCAL_VAR);
                Factor *tFunRet = factor_pop();
                code_add(code_create(Alloca, NULL, NULL, tFunRet, 0)); // 戻り値を先に定義
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
        : PROCEDURE proc_name SEMICOLON 
        {
                factor_push("Func Retval", gRegnum++, LOCAL_VAR);
                Factor *tFunRet = factor_pop();
                code_add(code_create(Alloca, NULL, NULL, tFunRet, 0)); // 戻り値を先に定義
        }
          inblock
        {
                gScope = GLOBAL_VAR;
                symtab_delete();
        }
        ;

proc_name
        : IDENT
        {
                symtab_push($1, 0, PROC_NAME);
                Row *tRow = symtab_lookup($1);

                fundecl_add(tRow->name, 0);
                gRegnum = 1; // 手続きごとにレジスタ番号はリセットされる

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
                Factor *tCond = factor_pop();

                // TODO if.endをいい感じの名前にしたい。if.break?while.breakをかえてもいいけど。
                Factor *tEnd = factor_push("if.else.end", 0, LABEL);
                // バックパッチであとで正しい値をつける(elseの前に来る)

                factor_push("if.then", gRegnum++, LABEL);
                Factor *tThen = factor_pop();
                // 捨てラベル(icmpのtrueのときに飛ぶラベルを直後に置く)

                code_add(code_create(BrCond, tThen, tEnd, tCond, 0));
                code_add(code_create(Label, tThen, NULL, NULL, 0));
        }
         statement else_statement
        ;

else_statement
        : /* empty */
        {
                Factor *tEnd = factor_pop();
                tEnd->val=gRegnum++;

                code_add(code_create(BrUncond, tEnd, NULL, NULL, 0));
                code_add(code_create(Label, tEnd, NULL, NULL, 0));
        }
        | ELSE
        {
                Factor *tElse = factor_pop();
                tElse->val = gRegnum++;

                Factor *tEnd = factor_push("if.end", 0, LABEL);
                
                code_add(code_create(BrUncond, tEnd, NULL, NULL, 0));
                code_add(code_create(Label, tElse, NULL, NULL, 0));
        }
         statement
        {
                Factor *tEnd = factor_pop();
                tEnd->val = gRegnum++;

                code_add(code_create(BrUncond, tEnd, NULL, NULL, 0));
                // Labelの前にはそれに対応するジャンプがないとダメっぽい?
                code_add(code_create(Label, tEnd, NULL, NULL, 0));
        }
        ;

while_statement
        : WHILE
        {
                Factor *tLoop = factor_push("while.loop", gRegnum++, LABEL);

                code_add(code_create(BrUncond, tLoop, NULL, NULL, 0));
                code_add(code_create(Label, tLoop, NULL, NULL, 0));
        }
         condition DO
        {
                Factor *tCond = factor_pop();

                factor_push("while.do", gRegnum++, LABEL);
                Factor *tDo = factor_pop(); // 捨てラベル

                Factor *tBreak = factor_push("while.break", 0, LABEL);
                // バックパッチであとで正しい値をつける(whileを抜ける)

                code_add(code_create(BrCond, tDo, tBreak, tCond, 0));
                code_add(code_create(Label, tDo, NULL, NULL, 0));
        }
         statement
        {
                Factor *tBreak = factor_pop();
                tBreak->val = gRegnum++;
                Factor *tLoop= factor_pop();
                // ステートメント内ではFactorのスタックは必ず使い切られる

                code_add(code_create(BrUncond, tLoop, NULL, NULL, 0));
                code_add(code_create(Label, tBreak, NULL, NULL, 0));
        }
        ;

for_statement
        : FOR IDENT ASSIGN expression TO expression DO
        {
                Row *tRow = symtab_lookup($2);
                Factor *tTo = factor_pop(); // tFromからtToまで
                Factor *tFrom = factor_pop();

                Factor *tCnt = factor_push(tRow->name, tRow->regnum, tRow->type);
                // カウンタ(インクリメントしていく変数)
                //popせずにとっておく

                code_add(code_create(Store, tFrom, tCnt, NULL, 0));

                Factor *tLoop = factor_push("for.loop", gRegnum++, LABEL);
                // ループで戻ってくる場所、あとからpopしてbr命令を書く

                code_add(code_create(BrUncond, tLoop, NULL, NULL, 0));
                code_add(code_create(Label, tLoop, NULL, NULL, 0));

                factor_push("", gRegnum++, LOCAL_VAR);
                Factor *tCntLocal = factor_pop();
                code_add(code_create(Load, tCnt, NULL, tCntLocal, 0)); // カウンタをレジスタに持ってくる

                factor_push("", gRegnum++, LOCAL_VAR);
                Factor *tCond = factor_pop(); // 条件を用意する

                code_add(code_create(Icmp, tCntLocal, tTo, tCond, SLE));

                factor_push("for.do", gRegnum++, LABEL);
                Factor *tDo = factor_pop(); // 条件でブレークしないときにここに飛ぶ

                Factor *tBreak = factor_push("for.break", 0, LABEL);
                // バックパッチであとから値入れたいのでpushしたままにする。

                code_add(code_create(BrCond, tDo, tBreak, tCond, 0));
                code_add(code_create(Label, tDo, NULL, NULL, 0));
        }
         statement
        {
                // この順番で出てくる
                Factor *tBreak = factor_pop();
                Factor *tLoop = factor_pop();
                Factor *tCnt = factor_pop();

                // cntインクリメント部ここから
                factor_push("for.increment", gRegnum++, LABEL);
                Factor *tInc = factor_pop();
                code_add(code_create(BrUncond, tInc, NULL, NULL, 0));
                code_add(code_create(Label, tInc, NULL, NULL, 0));

                factor_push("", gRegnum++, LOCAL_VAR);
                Factor *tCntLocal = factor_pop();

                code_add(code_create(Load, tCnt, NULL, tCntLocal, 0)); // カウンタをレジスタに持ってくる

                factor_push("", 1, CONSTANT);
                Factor *tOne = factor_pop();

                factor_push("", gRegnum++, LOCAL_VAR);
                Factor *tRetval = factor_pop();

                code_add(code_create(Add, tCntLocal, tOne, tRetval, 0));

                code_add(code_create(Store, tRetval, tCnt, NULL, 0));
                // インクリメント部ここまで

                code_add(code_create(BrUncond, tLoop, NULL, NULL, 0));

                tBreak->val = gRegnum++; // バックパッチ
                code_add(code_create(Label, tBreak, NULL, NULL, 0));
        }
        ;

proc_call_statement
        : proc_call_name
        ;

proc_call_name
        : IDENT
        {
                Row *tRow = symtab_lookup($1);
                factor_push(tRow->name, tRow->regnum, tRow->type);
                Factor *tProc = factor_pop();

                factor_push("", gRegnum++, LOCAL_VAR);//関数の戻り血
                Factor *tRetval = factor_pop();
                code_add(code_create(Call, tProc, NULL, tRetval, 0));
        }
        ;

block_statement
        : SBEGIN statement_list SEND
        ;

read_statement
        : READ LPAREN IDENT RPAREN
        {
                Row *tRow = symtab_lookup($3);
                factor_push(tRow->name, tRow->regnum, tRow->type);
                Factor *tArg = factor_pop();
                gRegnum++; // 本当は返り値を持っとく分
                code_add(code_create(Read, tArg, NULL, NULL, 0));
        }
        ;

write_statement
        : WRITE LPAREN expression RPAREN
        {
                Factor *tArg = factor_pop();
                code_add(code_create(Write, tArg, NULL, NULL, 0));
                gRegnum++; // print文は返り値を使わないけど、レジスタ番号は一応確保しないとエラー
        }
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
                Factor *tRetval = factor_push("", gRegnum++, LOCAL_VAR);

                code_add(code_create(Icmp, tArg1, tArg2, tRetval, EQUAL));
        }
        | expression NEQ expression
        {
                Factor *tArg2 = factor_pop();
                Factor *tArg1 = factor_pop();
                Factor *tRetval = factor_push("", gRegnum++, LOCAL_VAR);

                code_add(code_create(Icmp, tArg1, tArg2, tRetval, NE));
        }
        | expression GT expression
        {
                Factor *tArg2 = factor_pop();
                Factor *tArg1 = factor_pop();
                Factor *tRetval = factor_push("", gRegnum++, LOCAL_VAR);

                code_add(code_create(Icmp, tArg1, tArg2, tRetval, SGT));
        }
        | expression GE expression
        {
                Factor *tArg2 = factor_pop();
                Factor *tArg1 = factor_pop();
                Factor *tRetval = factor_push("", gRegnum++, LOCAL_VAR);

                code_add(code_create(Icmp, tArg1, tArg2, tRetval, SGE));
        }
        | expression LT expression
        {
                Factor *tArg2 = factor_pop();
                Factor *tArg1 = factor_pop();
                Factor *tRetval = factor_push("", gRegnum++, LOCAL_VAR);

                code_add(code_create(Icmp, tArg1, tArg2, tRetval, SLT));
        }
        | expression LE expression
        {
                Factor *tArg2 = factor_pop();
                Factor *tArg1 = factor_pop();
                Factor *tRetval = factor_push("", gRegnum++, LOCAL_VAR);

                code_add(code_create(Icmp, tArg1, tArg2, tRetval, SLE));
        }
        ;

expression
        : term
        | PLUS term
        | MINUS term
        {
                // 単項演算はゼロからの足し引きで表現。
                Factor *tArg2 = factor_pop();
                factor_push("", 0, CONSTANT);
                Factor *tArg1 = factor_pop();
                Factor *tRetval = factor_push("", gRegnum++, LOCAL_VAR);
                code_add(code_create(Sub, tArg1, tArg2, tRetval, 0));
        }
        | expression PLUS expression
        {
                // 四則演算は、全部これと一緒

                // オペランドをポップする(順番に注意)
                Factor *tArg2 = factor_pop();
                Factor *tArg1 = factor_pop();

                // 代入先として局所変数を用意、popしないことで、次のオペランドとしてもそのまま使える
                Factor *tRetval = factor_push("", gRegnum++, LOCAL_VAR);

                // Factorからのコード生成と追加を同時に行う
                code_add(code_create(Add, tArg1, tArg2, tRetval, 0));
        }
        | expression MINUS expression
        {
                Factor *tArg2 = factor_pop();
                Factor *tArg1 = factor_pop();
                Factor *tRetval = factor_push("", gRegnum++, LOCAL_VAR);
                code_add(code_create(Sub, tArg1, tArg2, tRetval, 0));
        }
        ;

term
        : factor
        | term MULT factor
        {
                Factor *tArg2 = factor_pop();
                Factor *tArg1 = factor_pop();
                Factor *tRetval = factor_push("", gRegnum++, LOCAL_VAR);
                code_add(code_create(Mul, tArg1, tArg2, tRetval, 0));
        }
        | term DIV factor
        {
                Factor *tArg2 = factor_pop();
                Factor *tArg1 = factor_pop();
                Factor *tRetval = factor_push("", gRegnum++, LOCAL_VAR);
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
                Row* tRow = symtab_lookup($1);
                factor_push(tRow->name, tRow->regnum, tRow->type);

                Factor *tArg1 = factor_pop();
                Factor *tRetval = factor_push("", gRegnum++, LOCAL_VAR);

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
                        symtab_push($1, gRegnum++, gScope);
                }

                Row *tRow = symtab_lookup($1);

                factor_push(tRow->name, tRow->regnum, gScope);
                Factor *tRetval = factor_pop();

                code_add(code_create(tCommand,NULL,NULL,tRetval, 0));
        }
        | id_list COMMA IDENT
        {
                // ↑と同じ
                LLVMcommand tCommand;
                if(gScope == GLOBAL_VAR){
                        tCommand = Global;
                        symtab_push($3, 0, gScope);
                } else{
                        tCommand = Alloca;
                        symtab_push($3, gRegnum++, gScope);
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
