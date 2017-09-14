%{
#include <string>
#include <sstream>
#include "functions.h"

#define T_Int 258
#define T_Real 259
#define T_String 260
#define T_Print 261
#define T_Read 262
#define T_If 263
#define T_Else 264
#define T_While 265
#define T_And 266
#define T_Or 267
#define T_Le 268
#define T_Ge 269
#define T_Eq 270
#define T_Ne 271
#define T_IntConstant 272
#define T_RealConstant 273
#define T_StringConstant 274
#define T_Identifier 275
#define T_Return 276
#define T_Break 277
#define T_Continue 278
#define T_Do 279
#define T_Until 280

using namespace std;
int cur_line = 1;
void yyerror(const char *msg);
void unrecognized_char(char c);
void unterminate_string();
string * handleEscapeCharacter(char * s);
typedef struct yy_buffer_state * YY_BUFFER_STATE;
stringstream is;
extern int yyparse();
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);extern vector<EXPR_DATA> global_var;
extern vector<Function*>global_functions;
extern int global_return_flag;
extern ExprRet global_return_value;
typedef union YYSTYPE
 {
    Expressions* expressions;
    Expression*  expression;
    Function*    function;
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
OPERATOR            ([+*-/%^$#=,;!<>(){}])
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
"out"               { return T_Print; }
"in"                { return T_Read; }
"do"                { return T_Do; }
"until"             { return T_Until; }
"while"             { return T_While; }
"return"            { return T_Return; }
"if"                { return T_If; }
"else"              { return T_Else; }
"<="                { return T_Le; }
">="                { return T_Ge; }
"=="                { return T_Eq; }
"<>"                { return T_Ne; }
"&&"                { return T_And; }
"||"                { return T_Or; }

{INTEGER}           { yylval.num = atof(yytext); return T_IntConstant; }
{REAL}				{ yylval.num = atof(yytext); return T_RealConstant; }
{STRING}            { 
                        yylval.str = handleEscapeCharacter(yytext);
						return T_StringConstant; 
					}
{IDENTIFIER}        { 
						yylval.str = new string(yytext); 
						return T_Identifier; 
					}

{UNTERM_STRING}     { unterminate_string(); }
.                   { unrecognized_char(yytext[0]); }

%%

string * handleEscapeCharacter(char * s)
{
    string temp(s);
    if (temp == "\"\"")
    {
        string *str = new string("");
        return str;
    }
    string *str = new string(temp.substr(1,temp.length()-2));
    for (int i=0; i<str->size()-1; i++) 
    {
        if ((*str)[i] == '\\')
        {
            switch((*str)[i+1])
            {
                case 'a':
                    (*str)[i] = '\a'; //replace the character
                    str->erase(str->begin()+i+1);//erase No i+1
                    break;
                case 'b':
                    (*str)[i] = '\b'; //replace the character
                    str->erase(str->begin()+i+1);//erase No i+1
                    break;
                case 'f':
                    (*str)[i] = '\f'; //replace the character
                    str->erase(str->begin()+i+1);//erase No i+1
                    break;
                case 'n':
                    (*str)[i] = '\n'; //replace the character
                    str->erase(str->begin()+i+1);//erase No i+1
                    break;
                case 'r':
                    (*str)[i] = '\r'; //replace the character
                    str->erase(str->begin()+i+1);//erase No i+1
                    break;
                case 't':
                    (*str)[i] = '\t'; //replace the character
                    str->erase(str->begin()+i+1);//erase No i+1
                    break;
                case 'v':
                    (*str)[i] = '\v'; //replace the character
                    str->erase(str->begin()+i+1);//erase No i+1
                    break;
                case '\\':
                    (*str)[i] = '\\'; //replace the character
                    str->erase(str->begin()+i+1);//erase No i+1
                    break;
                case '\'':
                    (*str)[i] = '\''; //replace the character
                    str->erase(str->begin()+i+1);//erase No i+1
                    break;
                case '\"':
                    (*str)[i] = '\"'; //replace the character
                    str->erase(str->begin()+i+1);//erase No i+1
                    break;
                case '0':
                    (*str)[i] = '\0'; //replace the character
                    str->erase(str->begin()+i+1);//erase No i+1
                    break;
                default:
                    break;
            }
        }
    }
    return str;
}

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
	system("pause");
    exit(-1);
}

int main(int argc, char ** argv) {
    //yydebug = 1;
    //char * str = "int main() { int a; in a; out a; }";
    is<<argv[2];
    YY_BUFFER_STATE buffer = yy_scan_string(argv[1]);
    if(yyparse() == 0)
    {
        for (int i=0; i<global_functions.size(); i++)
        {
            if (global_functions[i]->funcName == "main")
            {
                int size = global_functions[i]->para->args.size();
                ExprRet * b = new ExprRet[size];
                global_functions[i]->initialize(b, size);
                global_functions[i]->execute();
                break;
            }
        }
    }
    yy_delete_buffer(buffer);
}