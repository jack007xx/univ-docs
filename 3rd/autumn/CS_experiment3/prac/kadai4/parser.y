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
                symtab_push($2, gRegnum, gScope);
        }
          outblock PERIOD
        {
                print_LLVM_code();
        }
        ;

outblock
        : var_decl_part subprog_decl_part statement
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

                code_add(code_create(Store, tArg1, tArg2, NULL));
        }
        ;

if_statement
        : IF condition THEN statement else_statement
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
        | expression NEQ expression
        | expression GT expression
        | expression GE expression
        | expression LT expression
        | expression LE expression
        ;

expression
        : term
        | PLUS term
        | MINUS term
        | expression PLUS expression
        {
                // 四則演算は、全部これと一緒

                // オペランドをポップする(順番に注意)
                Factor *tArg2 = factor_pop();
                Factor *tArg1 = factor_pop();

                // 代入先として局所変数を用意、popしないことで、次のオペランドとしてもそのまま使える
                Factor *tRetval = factor_push("", gRegnum, LOCAL_VAR);
                gRegnum++;

                Factorからのコード生成と追加を同時に行う
                code_add(code_create(Add, tArg1, tArg2, tRetval));
        }
        | expression MINUS expression
        {
                Factor *tArg2 = factor_pop();
                Factor *tArg1 = factor_pop();

                Factor *tRetval = factor_push("", gRegnum, LOCAL_VAR);
                gRegnum++;

                code_add(code_create(Sub, tArg1, tArg2, tRetval));
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

                code_add(code_create(Mul, tArg1, tArg2, tRetval));
        }
        | term DIV factor
        {
                Factor *tArg2 = factor_pop();
                Factor *tArg1 = factor_pop();

                Factor *tRetval = factor_push("", gRegnum, LOCAL_VAR);
                gRegnum++;

                code_add(code_create(Sdiv, tArg1, tArg2, tRetval));
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

                code_add(code_create(Load, tArg1, NULL, tRetval));
        }
        ;

arg_list
        : expression
        | arg_list COMMA expression
        ;

id_list
        : IDENT
        {
                symtab_push($1, gRegnum, gScope);
                Row *tRow = symtab_lookup($1);

                factor_push(tRow->name, gRegnum, gScope);
                Factor *tRetval = factor_pop();

                code_add(code_create(Global,NULL,NULL,tRetval));
        }
        | id_list COMMA IDENT
        {
                symtab_push($3, gRegnum, gScope);
                Row *tRow = symtab_lookup($3);

                factor_push(tRow->name, gRegnum, gScope);
                Factor *tRetval = factor_pop();

                code_add(code_create(Global,NULL,NULL,tRetval));
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
