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
                gRegnum = 0;
                fundecl_init();
                code_init();
                fstack_init();
                symtab_init();
                gScope = GLOBAL_VAR;
                symtab_push($2, gRegnum, gScope);
        }
          outblock PERIOD
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
        : IDENT
        {
                symtab_lookup($1);
        } 
          ASSIGN expression
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
                Factor tArg1 = factor_pop();
                Factor tArg2 = factor_pop();
                Factor tRetval;
                tRetval.type = LOCAL_VAR;
                tRetval.val = gRegnum;

                LLVMcode tCode;
                tCode.command = Add;
                tCode.args.mul.arg1 = tArg1;
                tCode.args.mul.arg2 = tArg2;
                tCode.args.mul.retval = tRetval;
                code_add(tCode);
                factor_push(tRetval.vname, tRetval.val, tRetval.type);
        }
        | expression MINUS expression
        {
                Factor tArg1 = factor_pop();
                Factor tArg2 = factor_pop();
                Factor tRetval;
                tRetval.type = LOCAL_VAR;
                tRetval.val = gRegnum;

                LLVMcode tCode;
                tCode.command = Sub;
                tCode.args.mul.arg1 = tArg1;
                tCode.args.mul.arg2 = tArg2;
                tCode.args.mul.retval = tRetval;
                code_add(tCode);
                factor_push(tRetval.vname, tRetval.val, tRetval.type);
        }
        ;

term
        : factor
        | term MULT factor
        {
                Factor tArg1 = factor_pop();
                Factor tArg2 = factor_pop();
                Factor tRetval;
                tRetval.type = LOCAL_VAR;
                tRetval.val = gRegnum;

                LLVMcode tCode;
                tCode.command = Mul;
                tCode.args.mul.arg1 = tArg1;
                tCode.args.mul.arg2 = tArg2;
                tCode.args.mul.retval = tRetval;
                code_add(tCode);
                factor_push(tRetval.vname, tRetval.val, tRetval.type);
        }
        | term DIV factor
        {
                Factor tArg1 = factor_pop();
                Factor tArg2 = factor_pop();
                Factor tRetval;
                tRetval.type = LOCAL_VAR;
                tRetval.val = gRegnum;

                LLVMcode tCode;
                tCode.command = Sdiv;
                tCode.args.mul.arg1 = tArg1;
                tCode.args.mul.arg2 = tArg2;
                tCode.args.mul.retval = tRetval;
                code_add(tCode);
                factor_push(tRetval.vname, tRetval.val, tRetval.type);
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
                if (tRaw == NULL){
                }
                factor_push(tRaw->name, tRaw->regnum, tRaw->type);
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
        }
        | id_list COMMA IDENT
        {
                symtab_push($3, gRegnum, gScope);
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
