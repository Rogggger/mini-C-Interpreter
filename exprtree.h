#ifndef EXPRTREE_H
#define EXPRTREE_H
#include "functions.hpp"
#include "phint.hpp"

class Expression;
class Expressions;
class Expr_plus;
class Expr_assign;
class Expr_num;

void Execute(Expression* e);
void Execute(Expressions* exprs);

Expression* t_id(char* name);
Expression* t_num(double num);
Expression* t_string(string* str);

Expression* t_assign(char* name, Expression* e);

Expression* t_plus(Expression* e1, Expression* e2);
Expression* t_sub(Expression* e1, Expression* e2);
Expression* t_mul(Expression* e1, Expression* e2);
Expression* t_div(Expression* e1, Expression* e2);
Expression* t_mod(Expression* e1, Expression* e2)
Expression* t_neg(Expression* e1, Expression* e2)

Expression* t_less(Expression* e1, Expression* e2);
Expression* t_greateq(Expression* e1, Expression* e2)
Expression* t_neq(Expression* e1, Expression* e2)
Expression* t_eq(Expression* e1, Expression* e2);

Expression* t_or(Expression* e1, Expression* e2)
Expression* t_and(Expression* e1, Expression* e2)
Expression* t_not(Expression* e1, Expression* e2);

Expression* t_if(Expression* con, Expression* et, Expression* ef);
Expression* t_while(Expression* con, Expression* expr);
Expression* t_break();
Expression* t_continue();

Expression* t_normal(Expression* expr);
Expression* t_block(Expressions* exprs);
Expression* t_out(int a, string* hint, string* content);
Expression* t_in(string* hint, string* identifier);
Expression* t_call(string* identifier, Actuals* actuals);
Expression* t_return(expression expr);


Expressions* t_single_exprs(Expression* e);
Expressions* t_append_exprs(Expressions* exprs, Expression* e);

#endif
