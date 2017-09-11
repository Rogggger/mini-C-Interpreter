#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
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
    Parameters(pair<int, string*> p)
    {
        push(p);
    }
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
    VarDecl(int t, string* a)
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
    VarDecls(VarDecl* a)
    {
        push(a);
    }
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
    Function(int r, string* f, Parameters* a, VarDecls* v, Expressions* s)
    {
        this->retType = r;
        this->funcName = *f;
        this->para = a;
        this->varDecs = v;
        this->Stmts = s;
        vars = global_var;
    }
	double execute()
	{
		Stmts->execute(vars);
	}
	void initialize(Actuals* actuals)
	{
		/*make paras to actuals*/
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
            r.type == 260 ? a.data.str = r.str : a.data.num = r.num;
            vars.push_back(a);
		}
	}

};

vector<Function*> global_functions;

Function* t_func(int retType, string* funcName, Parameters* args, VarDecls* varDec, Expressions* stmts)
{
    return new Function(retType, funcName, args, varDec, stmts);
}

Parameters* t_single_para(int retType, string* identifier)
{
    return new Parameters(make_pair(retType, identifier));
}

Parameters* t_append_para(Parameters* args, int retType, string* identifier)
{
    if (args && identifier)
        args->append(make_pair(retType, identifier));
    return args;
}

VarDecls* t_single_decls(VarDecl* varDec)
{
    return new VarDecls(varDec);
}

VarDecls* t_append_decls(VarDecls* varDecs, VarDecl* varDec)
{
    if (varDecs && varDec)
        varDecs->append(varDec);
    return varDecs;
}

VarDecl* t_single_decl(int varType, string* identifier)
{
    return new VarDecl(varType, identifier);
}

VarDecl* t_append_decl(VarDecl* varDec, string* identifier)
{
    if (varDec && identifier)
        varDec->append(identifier);
    return varDec;
}

Actuals* t_single_actuals(Expression* expr)
{
    return new Actuals(expr);
}

Actuals* t_append_actuals(Actuals* acts, Expression* expr)
{
    if (acts && expr)
        acts->append(expr);
    return acts;
}

Expression* t_call(string* identifier, Actuals* actuals)
{
    return new Expr_call(identifier, actuals);
}

#endif
