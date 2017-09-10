#include <iostream>
#include <string>
#include "exprtree.h"

class Function{};

class Parameters{};

class VarDecls{};

class VarDecl{};

class Actuals{};


Function* t_func(token retType, str funcName, parameters args, vardecls varDec
					expressions stmts);

Parameters* t_single_para(token retType, str identifier);
Parameters* t_append_para(parameters args, token retType, str identifier);

VarDecls* t_single_decls(vardecl varDec);
VarDecls* t_append_decls(vardecls varDecs, vardecl varDec);

VarDecl* t_single_decl(token varType, str identifier);
VarDecl* t_append_decl(vardecl varDec, str identifier);
Actuals* t_single_actuals(expression expr);
Actuals* t_append_actuals(actuals acts, expression expr);