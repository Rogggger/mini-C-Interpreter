#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include <iostream>
#include <string>
#include <vector>
#include "symtab.hpp"
#include "exprtree.h"

using namespace std;
extern vector<EXPR_DATA> global_var;
extern int getType(vector<EXPR_DATA>&, string*, int&);

class Parameters
{
public:
    //attribute:
    vector<pair<int, string*>> args;
    /* A vector to save arguments */
    //methods:
    void append(pair<int, string*> a)
    {
        args.push_back(a);
        return ;
    }
    
};

class VarDecl
{
public:
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
    void execute(vector<EXPR_DATA>& vars)
    {
        /*为当前作用域添加变量*/
        for (std::vector<string*>::iterator i = decl.begin(); i != decl.end(); ++i)
        {
            int tempType=0;
            int pos = getType(vars, *i, tempType);
            if (pos == vars.size())
            {
                continue;
            }
            EXPR_DATA a;
            a.type = type;
            a.name = **i;
            if (type == 260)//is string
            {
                a.data.str = new string();
            }
            else // is int or num;
            {
                a.data.num = 0;
            }
            vars.push_back(a); // add a to scope;
        }
        return ;
    }
};

class VarDecls
{
public:
    vector<VarDecl*> decls;
    void append(VarDecl* a)
    {
        decls.push_back(a);
        return ;
    }
    void execute(vector<EXPR_DATA>& vars)
    {
        for (vector<VarDecl*>::iterator i = decls.begin(); i != decls.end(); ++i)
        {
            (*i)->execute(vars);
        }
    }
};



class Actuals
{
public:
    vector<Expression*> actus;
    void append(Expression* a)
    {
        actus.push_back(a);
    }
    
};

class Function
{
public:
	int retType;
	string funcName;
	/*parameters's vector*/
	Parameters* para;
	/*vardecls's pointer*/
	VarDecls* varDecs;
	/*Expression's pointer*/
	Expressions* Stmts;
	/*Execute this function's method*/
	vector<EXPR_DATA> vars;
	/*This functions scope*/
	double execute()
	{
		Stmts->execute(vars);
	}
	void initialize(Actuals* actuals)
	{
		/*make paras to actuals*/
		/*检查实参形参是否一样*/
		/*将对应名称的实参放到作用域里*/
		if (para->args.size() != actuals->actus.size())
		{
			throw string("Function initialization failed, args not match");
		}
		for (int i = 0; i < para->args.size(); ++i)
		{
            ExprRet r = actuals->actus[i]->execute;
			if (para->args[i].first != r)//参数不同
			{
                throw string("Function initialization failed, args not match");
			}
            EXPR_DATA a;
            a.name = *(para->args[i].second);
            a.type = *(para->args[i].first);
            a.data.
		}
	}
	
};

vector<Function*> global_functions;


Function* t_func(int retType, string* funcName, Parameters* args, VarDecls* varDec
					expressions stmts);

Parameters* t_single_para(token retType, str identifier);
Parameters* t_append_para(parameters args, token retType, str identifier);

VarDecls* t_single_decls(vardecl varDec);
VarDecls* t_append_decls(vardecls varDecs, vardecl varDec);

VarDecl* t_single_decl(token varType, str identifier);
VarDecl* t_append_decl(vardecl varDec, str identifier);
Actuals* t_single_actuals(expression expr);
Actuals* t_append_actuals(actuals acts, expression expr);
Expression* t_call(string* identifier, Actuals* actuals);

#endif
