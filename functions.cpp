#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "functions.h"

using namespace std;
extern vector<EXPR_DATA> global_var;
extern int getType(vector<EXPR_DATA>&, string*, int&);
extern vector<Function*> global_functions;
extern void yyerror(const char *);

Parameters::Parameters()
{
    ;
}

Parameters::Parameters(pair<int, string*> p)
{
    this->append(p);
}

void Parameters::append(pair<int, string*> a)
{
    //cout<< a.second->c_str();
    this->args.push_back(a);
    return ;
}

VarDecl::VarDecl(int t, string* a)
{
    this->type = t;
    this->decl.push_back(a);
}
void VarDecl::append(string* a)
{
    decl.push_back(a);
    return ;
}
void VarDecl::execute(vector<EXPR_DATA>& vars)
{
    /*为当前作用域添加变量*/
    for (std::vector<string*>::iterator i = decl.begin(); i != decl.end(); ++i)
    {
        int tempType=0;
        int pos = getType(vars, *i, tempType);
        if (pos != -1 && tempType == type)
        {
            yyerror("Variable multipal declaration");
            return ;
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


VarDecls::VarDecls(VarDecl* a)
{
    append(a);
}
void VarDecls::append(VarDecl* a)
{
    decls.push_back(a);
    return ;
}
void VarDecls::execute(vector<EXPR_DATA>& vars)
{
    for (vector<VarDecl*>::iterator i = decls.begin(); i != decls.end(); ++i)
    {
        (*i)->execute(vars);
    }
}

Actuals::Actuals(Expression * a)
{
    append(a);
}
void Actuals::append(Expression* a)
{
    actus.push_back(a);
    return;
}


Function::Function(int r, string* f, Parameters* a, VarDecls* v, Expressions* s)
{
    this->retType = r;
    this->funcName = *f;
    this->para = a;
    this->varDecs = v;
    this->Stmts = s;
    vars = global_var;
}
ExprRet Function::execute()
{
    if (varDecs && varDecs->decls.size())
        varDecs->execute(vars);
    return Stmts->execute(vars);
}
void Function::initialize(ExprRet* a, const int & length)
{
    /*make paras to actuals*/
    for (int i=0; i<length; i++)
    {
        EXPR_DATA temp;
        temp.type = para->args[i].first;
        if (temp.type == 260)
        {
            temp.data.str = new string(a[i].str);
        }
        else
        {
            temp.data.num = a[i].num;
        }
        temp.name = *(para->args[i].second);
        vars.push_back(temp);
    }
}

Expr_call::Expr_call(string* id, Actuals* act)
{
    if (id)
    {
        identifier = id;
        actuals = act;
    }
}
 ExprRet Expr_call::execute(vector<EXPR_DATA>& v)
{
    ExprRet *a = new ExprRet[actuals->actus.size()];
    ExprRet ret ;
    for (int i=0; i<actuals->actus.size(); i++) {
        a[i] = actuals->actus[i]->execute(v);
    }
    for (int i = 0; i < global_functions.size(); ++i)
    {
        if (global_functions[i]->funcName == *identifier)
        {
            int flag = 0;
            for (int j=0; j<actuals->actus.size(); j++)
            {
                /*  parameters type == Actuals' value */
                if (global_functions[i]->para->args[j].first
                    != a[j].type)
                {
                    flag = 1;
                    break;
                }
            }
            if (flag)
            {
                continue;
            }
            else
            {
                global_functions[i]->initialize(a, actuals->actus.size());
                ret = global_functions[i]->execute();
                break;
            }
        }
    }
    return ret;
}

Function* t_func(int retType, string* funcName, Parameters* args, VarDecls* varDec, Expressions* stmts)
{
    //printf("Type:%d\nName:%s\n", retType, funcName->c_str());
    Function * f = new Function(retType, funcName, args, varDec, stmts);
    global_functions.push_back(f);
    return f;
}
Parameters* t_single_para(int retType, string* identifier)
{
    if (identifier == NULL) {
        return new Parameters();
    }
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
