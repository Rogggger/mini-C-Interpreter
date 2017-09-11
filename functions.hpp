#include <iostream>
#include <string>
#include <vector>
#include "symtab.hpp"
#include "exprtree.h"

using namespace std;
extern vector<EXPR_DATA> global_var;

vector<Function*> global_functions;

class Function
{
public:
	int retType;
	string funcName;
	/*parameters's vector*/
	Parameters* args;
	/*vardecls's pointer*/
	varDecls* varDecs;
	/*Expression's pointer*/
	Expressions* Stmts;
	/*Execute this function's method*/
	double execute()
	{

	}
	void initialize(Actuals* actuals)
	{

	}
	/*make paras to actuals*/
	
}

class Parameters
{
	//attribute:
	vector<pair<int, string*>> args;
	/* A vector to save arguments */
	//methods:
	void append(pair<int, string*>) {};

}

class VarDecls
{
	vector<VarDecl*> decls;
	void append(VarDecl* a)
	{
		decls.push_back(a);
		return ;
	}
	void execute()
	{
		for (vector<VarDecl*>::iterator i = decls.begin(); i != decls.end(); ++i)
		{
			i->execute();
		}
	}
}

class VarDecl
{
	int type;
	vector<string*> decl;
	void initialize(int t, string* a)
	{
		this->type = t;
		this->decl.push_back(a);
	}
	void append(string* a)
	{
		decl.push_back(a);
		return ;
	}
	void execute()
	{
		/*为当前作用域添加变量*/
	}
}

class Actuals
{
	vector<Expression*> actus;
	void append(Expression* a)
	{
		actus.push_back(a);
	}

}


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