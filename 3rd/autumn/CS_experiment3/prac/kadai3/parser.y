%{
/*
 * parser; Parser for PL-0
 */

#define MAXLENGTH 16

#include <stdio.h>
#include <string.h>
#include "symtab.h"

int yyparse();
int yyerror(char *);

extern int yylineno;
extern char *yytext;

int regnum;
Scope scope;
char names[256];

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
                regnum = 0;
                init();
                scope = GLOBAL_VAR;
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
                scope = GLOBAL_VAR;
                delete();
        }
        ;

proc_name
        : IDENT
        {
                insert($1, regnum, PROC_NAME);
                scope = LOCAL_VAR;
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
                lookup($1);
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
                lookup($2);
        }
          ASSIGN expression TO expression DO statement
        ;

proc_call_statement
        : proc_call_name
        ;

proc_call_name
        : IDENT
        {
                lookup($1);
        }
        ;

block_statement
        : SBEGIN statement_list SEND
        ;

read_statement
        : READ LPAREN IDENT RPAREN
        {
                lookup($3);
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
        | expression MINUS expression
        ;

term
        : factor
        | term MULT factor
        | term DIV factor
        ;

factor
        : var_name
        | NUMBER
        | LPAREN expression RPAREN
        ;

var_name
        : IDENT
        {
                lookup($1);
        }
        ;

arg_list
        : expression
        | arg_list COMMA expression
        ;

id_list
        : IDENT
        {
                insert($1, regnum, scope);
        }
        | id_list COMMA IDENT
        {
                insert($3, regnum, scope);
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
