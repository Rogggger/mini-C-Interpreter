%{
#include <stdio.h>
#include <string>
#include "caltype.h"
#include "symtab.h"
#include "exprtree.h"
#include "functions.hpp"
#include "phint.hpp"
using namespace std;
extern void yyerror(const char *);
extern int yylex (void);

%}

%union{
    Expressions* expressions;
    Expression*  expression;
    Function*    function
    Parameters*  parameters;
    VarDecls*    vardecls;
    VarDecl*     vardecl;
    PHint        phint;
    Actuals*     actuals;
    string* 	 str;
    double       num;
}

%token T_Int T_Real T_String T_Return 
%token T_Print T_Read 
%token T_If T_Else T_While T_Break T_Continue 
%token T_And T_Or T_Le T_Ge T_Eq T_Ne
%token <num> T_IntConstant T_RealConstant 
%token <str> T_StringConstant 
%token <str> T_Identifier

%right '='
%left T_Or
%left T_And
%left T_Eq T_Ne
%left '<' '>' T_Le T_Ge 
%left '+' '-'
%left '*' '/' '%'
%right '!'

%type <function> FuncDecl
%type <parameters> Args _Args
%type <vardecls> VarDecls _VarDecls
%type <vardecl> VarDecl
%type <expression> Expr AssignStmt PrintStmt ReadIntStmt NormalStmt
%type <expression> CallStmt CallExpr ReturnStmt IfStmt WhileStmt
%type <expression> Stmt TestExpr StmtsBlock
%type <expressions> Stmts 
%type <num> PrintTimes
%type <phint> PrintHint
%type <str> PrintContent FuncName


%%

Program:
    /* empty */             { /* empty */ }
|   Program FuncDecl        { /* empty */ }
;

/*<function>*/
FuncDecl:
	/*token <str>      <parameters>      <vardecls> <Expressions>
    RetType FuncName '(' Args ')' FuncStart VarDecls Stmts FuncEnd
                            { 
                            	$$ = t_func($1, $2, $4, $7, $8);
                            }
;

FuncStart:
	'{'						{ /*create function scope*/ };
;

FuncEnd:
	'}'						{ /*ends function scope*/ };
;


/*token*/
RetType:
    T_Int                   { $$ = $1; }
|	T_Real 					{ $$ = $1; }
|   T_String                { $$ = $1; }
;

/*token*/
VarType:
    T_Int                   { $$ = $1; }
|	T_Real 					{ $$ = $1; }
|   T_String                { $$ = $1; }
;

/*<str>*/
FuncName:
    T_Identifier            { $$ = $1; }
;

/*<parameters>*/
Args:
    /* empty */             { $$ = t_single_para(0, NULL); }
|   _Args                   { $$ = $1; }
;

/*<parameters>*/
_Args:
    RetType T_Identifier    { t_single_para($1, $2); }
|   _Args ',' RetType T_Identifier
                            { t_append_para($1, $3, $4); }
;

/*<vardecls>*/
VarDecls:
    /* empty */             { /* empty */ }
|   _VarDecls 		    	{ $$ = $1;}
;

/*<vardecls>*/
_VarDecls:
	VarDecl ';'				{ $$ = t_single_decls($1);  }
|	_VarDecls VarDecl ';'	{ $$ = t_append_decls($1, $2); }
;

/*<vardecl>*/
VarDecl:
/*  int      <str>  */
	VarType T_Identifier	{ $$ = t_single_decl($1, $2); }
|	VarDecl ',' T_Identifier 
							{ $$ = t_append_decl($1, $3); }
;
 
/*<expressions>*/
Stmts:
    Stmt                    { $$ = t_single_exprs($1); }
|   Stmts Stmt              { $$ = t_append_exprs($1, $2); }
;

/*<expression>*/
Stmt:
    ';'                     { /* empty */ }
|   NormalStmt				{ /* empty */ }
|   AssignStmt              { /* empty */ }
|   PrintStmt               { /* empty */ }
|   ReadStmt                { /* empty */ }
|   BlockStmt				{ /* empty */ }
|   CallStmt                { /* empty */ }
|   ReturnStmt              { /* empty */ }
|   IfStmt                  { /* empty */ }
|   WhileStmt               { /* empty */ }
|   BreakStmt               { /* empty */ }
|   ContinueStmt            { /* empty */ }
;

/*<expression>*/
NormalStmt:
	Expr ';' 				{ $$ = $1; }
;

/*<expression>*/
AssignStmt:
    T_Identifier '=' Expr ';'
                            { $$ = t_assign($1, $3); }
;

/*<expression>*/
PrintStmt:
    T_Print PrintHint ',' PrintContent ';'
                            { $$ = t_out($2.count, $2.str, $4); }
|   T_Print PrintContent ';'   
							{ $$ = t_out(1, NULL, $2); }
;

/*<phint>*/
PrintHint:
    PrintTimes T_StringConstant 
    						{ $$.count = $1; $$.str = $2; }
|   PrintTimes           	{ $$.count = $1; $$.str = NULL; }
;

/*int*/
PrintTimes:
    T_IntConstant 			{ $$ = $1; }
|   T_Identifier  			{ $$ = t_id($1); }
;

/* str */
PrintContent:
    T_Identifier        	{ $$ = new string(t_id($1)); }
|   T_StringConstant        { $$ = $1; }
;

/*<expression>*/
ReadStmt:
/*  token      <str>            token
    T_Read T_StringConstant T_Identifier ';' 
    						{ 
    							$$ = t_in($2, $3)); 
    						}
/*  token       token */
|   T_Read T_Identifier ';'                  
							{ 
								$$ = t_in(NULL, $2);
							}
;

/*<expression>*/
CallStmt:
    CallExpr ';'            { $$ = $1; }
;

/*<expression>*/
CallExpr:
    T_Identifier '(' Actuals ')'
                            { $$ = t_call($1, $3); }
;

/*<actuals>*/
Actuals:
    /* empty */             { /* empty */ }
|   _Actuals                { /* empty */ }
;

/*<actuals>*/
_Actuals:
    Expr 					{ $$ = t_single_actuals($1); }
|   _Actuals ',' Expr       { $$ = t_append_actuals($1, $3); }
;


/*<expression>*/
ReturnStmt:
    T_Return Expr ';'       { $$ = t_return($2); }
|   T_Return ';'            { $$ = t_return(NULL); }
;

/*<expression>*/
IfStmt:
    T_If Expr BlockStmt
                            { $$ = t_if($2, $3, NULL); }
|   T_If Expr BlockStmt T_Else BlockStmt
                            { $$ = t_if($2, $3, $5); }
;

/*<expression>*/
BlockStmt:
    '{' Stmts '}'           { $$ = t_block($2); }
;

/*<expression>*/
BreakStmt:
    T_Break ';'     		{ $$ = t_break(); }
;

/*<expression>*/
ContinueStmt:
    T_Continue ';'          { $$ = t_continue(); }
;

/*<expression>*/
WhileStmt:
    T_While Expr BlockStmt
                   			 { $$ = t_while($2, $3); }
;

Expr:
    Expr '+' Expr           { $$ = t_plus($1, $3); }
|   Expr '-' Expr           { $$ = t_sub($1, $3); }
|   Expr '*' Expr           { $$ = t_mul($1, $3); }
|   Expr '/' Expr           { 
								try 
								{
									$$ = t_div($1, $3); 
								}
								catch (string msg)
								{
									yyerror(msg.c_str());
									printf("At %d.%d-%d.%d\n", @3.first_line, @3.first_column, @3.last_line, @3.last_column);
								}
							}
|   Expr '%' Expr           { 
								try
								{
									$$ = t_mod($1, $3); 
								}
								catch (string msg)
								{
									yyerror(msg.c_str());
									printf("At %d.%d-%d.%d\n", @3.first_line, @3.first_column, @3.last_line, @3.last_column);
								}
							}
|   Expr '>' Expr           { $$ = t_less($3, $1); }
|   Expr '<' Expr           { $$ = t_less($1, $3); }
|   Expr T_Ge Expr          { $$ = t_greateq($1, $3); }
|   Expr T_Le Expr          { $$ = t_greateq($3, $1); }
|   Expr T_Eq Expr          { $$ = t_eq($1, $3); }
|   Expr T_Ne Expr          { $$ = t_neq($1, $3); }
|   Expr T_Or Expr          { $$ = t_or($1, $3); }
|   Expr T_And Expr         { $$ = t_and($1, $3); }
|   '-' Expr %prec '!'      { $$ = t_neg($1); }
|   '!' Expr                { $$ = t_not($1); }
|   T_IntConstant           { $$ = t_num($1); }  
|   T_RealConstant          { $$ = t_num($1); }
|   T_Identifier            { $$ = t_id($1); }
|   CallExpr                { $$ = $1; }
|   '(' Expr ')'            { $$ = $2; }
;


%%

int main() {
    return yyparse();
}