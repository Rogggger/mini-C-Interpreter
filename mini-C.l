%{
#include <string>
#include "caltype.h"
#include "exprtree.h"
#define T_Int 258
#define T_Real 259
#define T_String 260
#define T_Return 261
#define T_Print 262
#define T_ReadInt 263
#define T_If 264
#define T_Else 265
#define T_While 266
#define T_Break 267
#define T_Continue 268
#define T_And 269
#define T_Or 270
#define T_Le 271
#define T_Ge 272
#define T_Eq 273
#define T_Ne 274
#define T_IntConstant 275
#define T_RealConstant 276
#define T_StringConstant 277
#define T_Identifier 278
using namespace std;
int cur_line = 1;
void yyerror(const char *msg);
void unrecognized_char(char c);
void unterminate_string();
typedef union YYSTYPE
 {
    Expressions* expressions;
    Expression*  expression;
    Function*    function
    Parameters*  parameters;
    VarDecls*    vardecls;
    VarDecl*     vardecl;
    PHint        phint;
    Actuals*     actuals;
    string*      str;
    double       num;
    int          token;
 }YYSTYPE;

  extern YYSTYPE yylval;
%}

/* note \042 is '"' */
WHITESPACE          ([ \t\r\a]+)
SINGLE_COMMENT1     ("//"[^\n]*)
OPERATOR            ([+*-/%=,;!<>(){}])
INTEGER             ([0-9]+)
REAL                ([0-9]+\.[0-9]*)
IDENTIFIER          ([_a-zA-Z][_a-zA-Z0-9]*)
UNTERM_STRING       (\042[^\042\n]*)
STRING              (\042[^\042\n]*\042)

%%

\n                  { cur_line++; }
{WHITESPACE}        { /* ignore every whitespace */ }
{SINGLE_COMMENT1}   { /* skip for single line comment */    }

{OPERATOR}          { return yytext[0]; }
"int"               { return T_Int; }
"real"			    { return T_Real; }
"string"			{ return T_String; }
"void"              { return T_Void; }
"return"            { return T_Return; }
"print"             { return T_Print; }
"readint"           { return T_ReadInt; }
"while"             { return T_While; }
"if"                { return T_If; }
"else"              { return T_Else; }
"break"             { return T_Break; }
"continue"          { return T_Continue; }
"<="                { return T_Le; }
">="                { return T_Ge; }
"=="                { return T_Eq; }
"!="                { return T_Ne; }
"&&"                { return T_And; }
"||"                { return T_Or; }

{INTEGER}           { yylval.num = atof(yytext); return T_IntConstant; }
{REAL}				{ yylval.num = atof(yytext); return T_RealConstant; }
{STRING}            { 
						yylval.str = new string(yytext); 
						yylval.str = yylval.str.substr(2,yylval.str.length()-2);
						return T_StringConstant; 
					}
{IDENTIFIER}        { 
						yylval.str = new string(yytext); 
						return T_Identifier; 
					}

{UNTERM_STRING}     { unterminate_string(); }
.                   { unrecognized_char(yytext[0]); }

%%

int yywrap(void) { 
    return 1;
}

void unrecognized_char(char c) {
    char buf[32] = "Unrecognized character: ?";
    buf[24] = c;
    yyerror(buf);
}

void unterminate_string() {
    yyerror("Unterminate string constant");
}

void yyerror(const char *msg) {
    fprintf(stderr, "Error at line %d:\n\t%s\n", cur_line, msg);
    exit(-1);
}