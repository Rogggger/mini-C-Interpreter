#ifndef EXPRTREE_H
#define EXPRTREE_H
#include <string>
#include "symtab.h"
using namespace std;

struct ExprRet {
    ExprRet(const double& a, const string& s,const int &t);
    ExprRet();
    int type;
    double num;
    string str;
};

class Expression
{
public:
    Expression();
    virtual ExprRet execute(vector<EXPR_DATA>& v);
};

class Expressions
{
public:
    Expressions(Expression* e);
    void push(Expression* e);
    virtual ExprRet execute(vector<EXPR_DATA>& v);
    std::vector<Expression*> m_vExpr;
};

class Expr_plus : public Expression
{
public:
    Expr_plus(Expression* e1, Expression* e2);
    virtual ExprRet execute(vector<EXPR_DATA>& v);
protected:
    Expression* m_e1;
    Expression* m_e2;
};

class Expr_sub : public Expression
{
public:
    Expr_sub(Expression* e1, Expression* e2);
    virtual ExprRet execute(vector<EXPR_DATA>& v);
protected:
    Expression* m_e1;
    Expression* m_e2;
};

class Expr_mul : public Expression
{
public:
    Expr_mul(Expression* e1, Expression* e2);
    virtual ExprRet execute(vector<EXPR_DATA>& v);
protected:
    Expression* m_e1;
    Expression* m_e2;
};

class Expr_div : public Expression
{
public:
    Expr_div(Expression* e1, Expression* e2);
    virtual ExprRet execute(vector<EXPR_DATA>& v);
protected:
    Expression* m_e1;
    Expression* m_e2;
};

class Expr_mod : public Expression
{
public:
    Expr_mod(Expression* e1, Expression* e2);
    virtual ExprRet execute(vector<EXPR_DATA>& v);
protected:
    Expression* m_e1;
    Expression* m_e2;
};
class Expr_pow : public Expression
{
public :
	Expr_pow(Expression* e1, Expression* e2);
	virtual ExprRet execute(vector<EXPR_DATA>& v);
protected:
	Expression* m_e1;
	Expression* m_e2;
};
class Expr_splus:public Expression
{
public:
	Expr_splus(Expression* e1, Expression* e2);
	virtual ExprRet execute(vector<EXPR_DATA>& v);
protected:
	Expression* m_e1;
	Expression* m_e2;
};
class Expr_ssub :public Expression
{
public:
	Expr_ssub(Expression* e1);
	virtual ExprRet execute(vector<EXPR_DATA>& v);
protected:
	Expression* m_e1;
};

class Expr_assign : public Expression
{
public:
    Expr_assign(string* name, Expression* e);
    virtual ExprRet execute(vector<EXPR_DATA>& v);
protected:
    string*    m_name;
    Expression* m_e;
};

class Expr_num_double : public Expression
{
public:
    Expr_num_double(double num);
    virtual ExprRet execute(vector<EXPR_DATA>& v);
protected:
    double m_num;
};
class Expr_num_int : public Expression
{
public:
    Expr_num_int(int num);
    virtual ExprRet execute(vector<EXPR_DATA>& v);
protected:
    int m_num;
};

class Expr_num_string : public Expression
{
public:
    Expr_num_string(string* num);
    virtual ExprRet execute(vector<EXPR_DATA>& v);
protected:
    string m_num;
};

class Expr_out :public Expression
{
public:
    Expr_out(Expression* _printTimes, string* _printHint, Expression* _printContent);
    virtual ExprRet execute(vector<EXPR_DATA>& v);
protected:
    Expression* printContent;
    Expression*  printTimes;
    string*     printHint;
};

class Expr_in :public Expression
{
public:
    Expr_in(string* _readHint, string* _identifier);
    virtual ExprRet excute(vector<EXPR_DATA>& v);
protected:
    string* readHint;
    string* identifier;
};

class Expr_ID : public Expression
{
public:
    Expr_ID(string* name);
    virtual ExprRet execute(vector<EXPR_DATA>& v);
protected:
    string* m_name;
};

class Expr_if : public Expression
{
public:
    Expr_if(Expression* con, Expression* et, Expression* ef);
    Expr_if(Expression* con, Expression* et);
    virtual ExprRet execute(vector<EXPR_DATA>& v);
protected:
    Expression* m_con;
    Expression* m_et;
    Expression* m_ef;
};

class Expr_less : public Expression
{
public:
    Expr_less(Expression* e1, Expression* e2);
    
    virtual ExprRet execute(vector<EXPR_DATA>& v);
protected:
    Expression* m_e1;
    Expression* m_e2;
};
class Expr_greateq : public Expression
{
public:
    Expr_greateq(Expression* e1, Expression* e2);
    virtual ExprRet execute(vector<EXPR_DATA>& v);
protected:
    Expression* m_e1;
    Expression* m_e2;
};
class Expr_eq : public Expression
{
public:
    Expr_eq(Expression* e1, Expression* e2);
    virtual ExprRet execute(vector<EXPR_DATA>& v);
protected:
    Expression* m_e1;
    Expression* m_e2;
};

class Expr_neq : public Expression
{
public:
    Expr_neq(Expression* e1, Expression* e2);
    virtual ExprRet execute(vector<EXPR_DATA>& v);
protected:
    Expression* m_e1;
    Expression* m_e2;
};

class Expr_or : public Expression
{
public:
    Expr_or(Expression* e1, Expression* e2);
    virtual ExprRet execute(vector<EXPR_DATA>& v);
protected:
    Expression* m_e1;
    Expression* m_e2;
};

class Expr_and : public Expression
{
public:
    Expr_and(Expression* e1, Expression* e2);
    virtual ExprRet execute(vector<EXPR_DATA>& v);
protected:
    Expression* m_e1;
    Expression* m_e2;
};

class Expr_neg : public Expression
{
public:
    Expr_neg(Expression* e);
    virtual ExprRet execute(vector<EXPR_DATA>& v);
    
protected:
    Expression* m_e;
};

class Expr_not : public Expression
{
public:
    Expr_not(Expression* e);
    virtual ExprRet execute(vector<EXPR_DATA>& v);
    
protected:
    Expression* m_e;
};

class Expr_while : public Expression
{
public:
    Expr_while(Expression* con, Expression* e);
    virtual ExprRet execute(vector<EXPR_DATA>& v);
    
protected:
    Expression* m_con;
    Expression* m_e;
};
class Expr_dountil : public Expression
{
public:
	Expr_dountil(Expression* e, Expression* con);
	virtual ExprRet execute(vector<EXPR_DATA>& v);

protected:
	Expression* m_con;
	Expression* m_e;
};

class Expr_break : public Expression
{
public:
    Expr_break();
    virtual ExprRet execute(vector<EXPR_DATA>& v);
    
protected:
};
class Expr_continue : public Expression
{
public:
    Expr_continue();
    virtual ExprRet execute(vector<EXPR_DATA>& v);
    
protected:
};
class Expr_return : public Expression
{
public:
    Expr_return();
    Expr_return(Expression* e);
    virtual ExprRet execute(vector<EXPR_DATA>& v);
    
protected:
    Expression* m_e;
};
class Expr_block : public Expression
{
public:
    Expr_block(Expressions* exprs);
    virtual ExprRet execute(vector<EXPR_DATA>& v);
protected:
    Expressions* m_exprs;
};

class PHint {
public:
    Expression* count;
    string* str;
};

Expression* t_id(string* name);
Expression* t_num_double(double num);
Expression* t_num_int(int num);
Expression* t_num_string(string* num);


Expression* t_assign(string* name, Expression* e);

Expression* t_plus(Expression* e1, Expression* e2);
Expression* t_sub(Expression* e1, Expression* e2);
Expression* t_mul(Expression* e1, Expression* e2);
Expression* t_div(Expression* e1, Expression* e2);
Expression* t_mod(Expression* e1, Expression* e2);
Expression* t_pow(Expression* e1, Expression* e2);
Expression* t_splus(Expression* e1, Expression* e2);
Expression* t_ssub(Expression* e1);
Expression* t_neg(Expression* e1);

Expression* t_less(Expression* e1, Expression* e2);
Expression* t_greateq(Expression* e1, Expression* e2);
Expression* t_neq(Expression* e1, Expression* e2);
Expression* t_eq(Expression* e1, Expression* e2);

Expression* t_or(Expression* e1, Expression* e2);
Expression* t_and(Expression* e1, Expression* e2);
Expression* t_not(Expression* e1);

Expression* t_if(Expression* con, Expression* et, Expression* ef);
Expression* t_if(Expression* con, Expression* et);

Expression* t_while(Expression* con, Expression* expr);
Expression* t_dountil(Expression* e, Expression* con);
Expression* t_break();
Expression* t_continue();
Expression* t_return(Expression* expr);

Expression* t_block(Expressions* exprs);
Expression* t_out(Expression* _printTimes, string* _printHint, Expression* _printContent);
Expression* t_in(string* _readHint, string* _identifier);


Expressions* t_single_exprs(Expression* e);
Expressions* t_append_exprs(Expressions* exprs, Expression* e);

#endif
