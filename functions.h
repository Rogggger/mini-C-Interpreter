#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "symtab.h"
#include "exprtree.h"

using namespace std;

class Parameters
{
public:
    //attribute:
    vector<pair<int, string*> > args;
    Parameters(pair<int, string*> p);
    /* A vector to save arguments */
    //methods:
    void append(pair<int, string*> a);
};

class VarDecl
{
public:
    int type;
    vector<string*> decl;
    VarDecl(int t, string* a);
    void append(string* a);
    void execute(vector<EXPR_DATA>& vars);
};

class VarDecls
{
public:
    vector<VarDecl*> decls;
    VarDecls(VarDecl* a);
    void append(VarDecl* a);
    void execute(vector<EXPR_DATA>& vars);
};

class Actuals
{
public:
    vector<Expression*> actus;
    Actuals(Expression * a);
    void append(Expression* a);
    
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
    Function(int r, string* f, Parameters* a, VarDecls* v, Expressions* s);
    ExprRet execute();
    void initialize(Actuals* actuals);
    
};


class Expr_call : public Expression
{
public:
    Expr_call(string* id, Actuals* act);
    virtual ExprRet execute(vector<EXPR_DATA>& v);
protected:
    string* identifier;
    Actuals* actuals;
    
};

Function* t_func(int retType, string* funcName, Parameters* args, VarDecls* varDec, Expressions* stmts);
Parameters* t_single_para(int retType, string* identifier);
Parameters* t_append_para(Parameters* args, int retType, string* identifier);
VarDecls* t_single_decls(VarDecl* varDec);
VarDecls* t_append_decls(VarDecls* varDecs, VarDecl* varDec);
VarDecl* t_single_decl(int varType, string* identifier);
VarDecl* t_append_decl(VarDecl* varDec, string* identifier);
Actuals* t_single_actuals(Expression* expr);
Actuals* t_append_actuals(Actuals* acts, Expression* expr);
Expression* t_call(string* identifier, Actuals* actuals);

#endif
