%{
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "caltype.h"
#include "symtab.h"
#include "exprtree.h"
#include "PHint.hpp"

extern void yyerror(const char *);
extern int yylex (void);

%}

%union{
    Expressions* expressions;
    Expression* expression;
    char      name[32];
    double      num;
    char      str[32];
    PHint       phint;
}

%token T_Int T_Real T_Void T_Return 
%token T_Print T_ReadInt 
%token T_If T_Else T_While T_Break T_Continue 
%token T_And T_Or T_Le T_Ge T_Eq T_Ne
%token <num> T_IntConstant T_RealConstant 
%token <str> T_StringConstant 
%token <name> T_Identifier

%right '='
%left T_Or
%left T_And
%left T_Eq T_Ne
%left '<' '>' T_Le T_Ge
%left '+' '-'
%left '*' '/' '%'
%right '!'

%type<expression> Expr AssignStmt PrintStmt ReadIntStmt 
%type<expression> CallStmt ReturnStmt IfStmt WhileStmt
%type<expression> Stmt TestExpr StmtsBlock
%type<expressions> Stmts 
%type<num>PrintTimes
%type<phint> PrintHint
%type <str> PrintContent


%%

Program:
    /* empty */             { /* empty */ }
|   Program FuncDecl        { /* empty */ }
;

FuncDecl:
    RetType FuncName '(' Args ')' '{' VarDecls Stmts '}'
                            { printf("ENDFUNC\n\n"); 
                              Execute($8);
                            }
;

RetType:
    T_Int                   { /* empty */ }
|   T_Void                  { /* empty */ }
;

FuncName:
    T_Identifier            { printf("FUNC @%s:\n", $1); }
;

Args:
    /* empty */             { /* empty */ }
|   _Args                   { printf("\n\n"); }
;

_Args:
    T_Int T_Identifier      { printf("\targ %s", $2); }
|   _Args ',' T_Int T_Identifier
                            { printf(", %s", $4); }
;

VarDecls:
    /* empty */             { /* empty */ }
|   VarDecls VarDecl ';'    { printf("\n\n"); }
;

VarDecl:
    T_Int T_Identifier      { printf("\tvar %s", $2); }
|   VarDecl ',' T_Identifier
                            { printf(", %s", $3); }
;

Stmts:
    Stmt                    { $$ = t_single_exprs($1); }
|   Stmts Stmt              { $$ = t_append_exprs($1, $2); }
;

Stmt:
    ';'                     { /* empty */ }
|   AssignStmt              { /* empty */ }
|   PrintStmt               { /* empty */ }
|   ReadIntStmt             { /* empty */ }
|   CallStmt                { /* empty */ }
|   ReturnStmt              { /* empty */ }
|   IfStmt                  { /* empty */ }
|   WhileStmt               { /* empty */ }
|   BreakStmt               { /* empty */ }
|   ContinueStmt            { /* empty */ }
;

AssignStmt:
    T_Identifier '=' Expr ';'
                            { $$ = t_assign($1, $3); }
;

PrintStmt:
    T_Print PrintHint PrintContent ';'
                            { t_out($2.count, $2.str, $3); }
|   T_Print PrintContent ';'   { t_out(1, "", $2); }
;

PrintHint:
    PrintTimes T_StringConstant { $$.count = $1; strcpy($$.str, $2); }
|   PrintTimes           { $$.count = $1; strcpy($$.str, "")}
;

PrintTimes:
    T_IntConstant { $$ = $1; }
|   T_Identifier  { /* Acquire var value */ }
;

PrintContent:
    T_Identifier         { /* Acquire var value and trans it to string */}
|   T_StringConstant     { strcpy($$, $1); }
;

ReadIntStmt:
    T_ReadInt T_StringConstant T_Identifier ';' {}
|   T_ReadInt T_Identifier ';'                  {}
;

PActuals:
    /* empty */             { /* empty */ }
|   PActuals ',' Expr       { /* empty */ }
;

CallStmt:
    CallExpr ';'            { printf("\tpop\n\n"); }
;

CallExpr:
    T_Identifier '(' Actuals ')'
                            { printf("\t$%s\n", $1); }
;

Actuals:
    /* empty */             { /* empty */ }
|   Expr PActuals           { /* empty */ }
;

ReturnStmt:
    T_Return Expr ';'       { printf("\tret ~\n\n"); }
|   T_Return ';'            { printf("\tret\n\n"); }
;

IfStmt:
    T_If TestExpr StmtsBlock
                            { $$ = t_if($2, $3); }
|   T_If TestExpr StmtsBlock T_Else StmtsBlock
                            { $$ = t_if($2, $3, $5); }
;

TestExpr:
    '(' Expr ')'            { $$ = $2; }
;

StmtsBlock:
    '{' Stmts '}'           { $$ = t_block($2); }
;


BreakStmt:
    T_Break ';'     { printf("\tjmp _endWhile_\n"); }
;

ContinueStmt:
    T_Continue ';'  { printf("\tjmp _begWhile_\n"); }
;

WhileStmt:
    T_While TestExpr StmtsBlock
                    { $$ = t_while($2, $3); }
;

Expr:
    Expr '+' Expr           { $$ = t_plus($1, $3); }
|   Expr '-' Expr           { $$ = t_sub($1, $3); }
|   Expr '*' Expr           { $$ = t_mul($1, $3); }
|   Expr '/' Expr           { $$ = t_div($1, $3); }
|   Expr '%' Expr           { printf("\tmod\n"); }
|   Expr '>' Expr           { printf("\tcmpgt\n"); }
|   Expr '<' Expr           { printf("\tcmplt\n"); }
|   Expr T_Ge Expr          { printf("\tcmpge\n"); }
|   Expr T_Le Expr          { printf("\tcmple\n"); }
|   Expr T_Eq Expr          { $$ = t_eq($1, $3); }
|   Expr T_Ne Expr          { printf("\tcmpne\n"); }
|   Expr T_Or Expr          { printf("\tor\n"); }
|   Expr T_And Expr         { printf("\tand\n"); }
|   '-' Expr %prec '!'      { printf("\tneg\n"); }
|   '!' Expr                { printf("\tnot\n"); }
|   T_IntConstant           { $$ = t_num($1); }
|   T_RealConstant          { $$ = t_num($1); }
|   T_StringConstant        { }
|   T_Identifier            { $$ = t_id($1); }
|   CallExpr                { /* empty */ }
|   '(' Expr ')'            { $$ = $2; }
;


%%

int main() {
    return yyparse();
}