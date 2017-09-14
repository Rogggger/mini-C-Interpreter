/*
                   _ooOoo_
                  o8888888o
                  88" . "88
                  (| -_- |)
                  O\  =  /O
               ____/`---'\____
             .'  \\|     |//  `.
            /  \\|||  :  |||//  \
           /  _||||| -:- |||||-  \
           |   | \\\  -  /// |   |
           | \_|  ''\---/''  |   |
           \  .-\__  `-`  ___/-. /
         ___`. .'  /--.--\  `. . __
      ."" '<  `.___\_<|>_/___.'  >'"".
     | | :  ` - `.;`\ _ /`;.`/ - ` : | |
     \  \ `-.   \_ __\ /__ _/   .-` /  /
======`-.____`-.___\_____/___.-`____.-'======
                   `=---='
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
            佛祖保佑       永无BUG
*/

#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <math.h>
#include "exprtree.h"
using namespace std;

extern void yyerror(const char *);

using namespace std;
bool float_eq(double id, double num)
{
  double sub = id - num;
  if (sub < 0.00001f && sub > -0.00001f)
    return true;
  return false;
}

ExprRet::ExprRet(const double& a, const string& s,const int &t)
{
    num = a;
    str = s;
    type = t;
}
ExprRet::ExprRet()
{
    num = 0;
    str = "";
    type = 258;
}

Expression::Expression()
{
    return ;
}

ExprRet Expression::execute(vector<EXPR_DATA>& v)
{
    return ExprRet();
}

Expressions::Expressions(Expression* e)
{
    push(e);
}

void Expressions::push(Expression* e)
{
    m_vExpr.push_back(e);
}
ExprRet Expressions::execute(vector<EXPR_DATA>& v)
{
    for (int i = 0; i < m_vExpr.size(); i++)
    {
        if (m_vExpr[i])
            m_vExpr[i]->execute(v);
    }
    return ExprRet();
};


Expr_plus::Expr_plus(Expression* e1, Expression* e2)
{
    m_e1 = e1;
    m_e2 = e2;
}
ExprRet Expr_plus::execute(vector<EXPR_DATA>& v)
{
    if (!m_e1 || !m_e2)
        return ExprRet();
    ExprRet num1 = m_e1->execute(v);
    ExprRet num2 = m_e2->execute(v);
    if (num1.type == 258 && num2.type == 258)
    {
        return ExprRet((int)num1.num + (int)num2.num, "",258);
    }
    else if ((num1.type == 259 || num2.type == 259) && (num1.type != 260 && num2.type != 260))
    {
        return ExprRet(num1.num + num2.num, "", 259);
    }
    else
    {
        yyerror("string can not be used in addition\n");
        return ExprRet();
    }
}


Expr_sub::Expr_sub(Expression* e1, Expression* e2)
{
    m_e1 = e1;
    m_e2 = e2;
}
 ExprRet Expr_sub::execute(vector<EXPR_DATA>& v)
{
    if (!m_e1 || !m_e2)
        return ExprRet();
    ExprRet num1 = m_e1->execute(v);
    ExprRet num2 = m_e2->execute(v);
    if (num1.type == 258 && num2.type == 258)
    {
        return ExprRet((int)num1.num - (int)num2.num, "", 258);
    }
    else if ((num1.type == 259 || num2.type == 259) && (num1.type != 260 && num2.type != 260))
    {
        return ExprRet(num1.num - num2.num, "", 259);
    }
    else
    {
        yyerror("string can not be used in subtraction\n");
        return ExprRet();
    }
}


Expr_mul::Expr_mul(Expression* e1, Expression* e2)
{
    m_e1 = e1;
    m_e2 = e2;
}
 ExprRet Expr_mul::execute(vector<EXPR_DATA>& v)
{
    if (!m_e1 || !m_e2)
        return ExprRet();
    ExprRet num1 = m_e1->execute(v);
    ExprRet num2 = m_e2->execute(v);
    if (num1.type == 258 && num2.type == 258)
    {
        return ExprRet((int)num1.num * (int)num2.num, "", 258);
    }
    else if ((num1.type == 259 || num2.type == 259) && (num1.type != 260 && num2.type != 260))
    {
        return ExprRet(num1.num * num2.num, "", 259);
    }
    else
    {
        yyerror("string can not be multiplied\n");
        return ExprRet();
    }
}


Expr_div::Expr_div(Expression* e1, Expression* e2)
{
    m_e1 = e1;
    m_e2 = e2;
}
 ExprRet Expr_div::execute(vector<EXPR_DATA>& v)
{
    if (!m_e1 || !m_e2)
        return ExprRet();
    ExprRet num1 = m_e1->execute(v);
    ExprRet num2 = m_e2->execute(v);
    if (num1.type == 258 && num2.type == 258)
    {
        if ((int)num2.num==0)
        {
            yyerror("divided by zero\n");
            return ExprRet();
        }
        else 
            return ExprRet((int)num1.num / (int)num2.num, "", 258);
    }
    else if ((num1.type == 259 || num2.type == 259) && (num1.type != 260 && num2.type != 260))
    {
        if (float_eq(num2.num,0))
        {
            yyerror("divided by zero");
            return ExprRet();
        }
        else 
            return ExprRet(num1.num / num2.num, "", 259);
    }
    else
    {
        yyerror("string can not be divided");
        return ExprRet();
    }
}

Expr_mod::Expr_mod(Expression* e1, Expression* e2)
{
    m_e1 = e1;
    m_e2 = e2;
}
ExprRet Expr_mod::execute(vector<EXPR_DATA>& v)
{
    if (!m_e1 || !m_e2)
        return ExprRet();
    ExprRet num1 = m_e1->execute(v);
    ExprRet num2 = m_e2->execute(v);
    if (num1.type == 258 && num2.type == 258)
    {
        if ((int)num2.num == 0)
        {
            yyerror("moded by zero");
            return ExprRet();
        }
        else
            return ExprRet((int)num1.num % (int)num2.num, "", 258);
    }
    else
    {
        yyerror("Only an integer can take the remainder");
        return ExprRet();
    }
}
Expr_pow::Expr_pow(Expression* e1, Expression* e2)
{
	m_e1 = e1;
	m_e2 = e2;
}
ExprRet Expr_pow::execute(vector<EXPR_DATA>& v)
{
	if (!m_e1 || !m_e2)
		return ExprRet();
	ExprRet num1 = m_e1->execute(v);
	ExprRet num2 = m_e2->execute(v);
	if (num1.type == 260 || num2.type == 260)
	{
		yyerror("string can not participate in the power operation");
		return ExprRet();
	}
	else if (num2.num < 1&&num1.num<0)
	{
		yyerror("Unable to calculate");
		return ExprRet();
	}
	else if (num1.type == 258 && num1.type == 258)
	{
		return ExprRet((int)pow(num1.num, num2.num), "", 258);
	}
	else
	{
		return ExprRet(pow(num1.num, num2.num), "", 259);
	}
}
Expr_splus::Expr_splus(Expression* e1, Expression* e2)
{
	m_e1 = e1;
	m_e2 = e2;
}
ExprRet Expr_splus::execute(vector<EXPR_DATA>& v)
{
	if (!m_e1 || !m_e2)
		return ExprRet();
	ExprRet num1 = m_e1->execute(v);
	ExprRet num2 = m_e2->execute(v);
	if (num1.type == 260 && num2.type == 260)
	{
		return ExprRet(0, num1.str + num2.str, 260);
	}
	else
	{
		yyerror("only type string can be used in this operation");
		return ExprRet();
	}
}
Expr_ssub::Expr_ssub(Expression* e1)
{
	m_e1 = e1;
}
ExprRet Expr_ssub::execute(vector<EXPR_DATA>& v)
{
	if (!m_e1)
		return ExprRet();
	ExprRet num1 = m_e1->execute(v);
	if (num1.type != 260)
	{
		yyerror("only type string can be used in this operation");
		return ExprRet();
	}
	else
	{
		string tmp = num1.str.substr(0, num1.str.length() - 1);
		return ExprRet(0,tmp,260);
	}
}
Expr_assign::Expr_assign(string* name, Expression* e)
{
    if (name)
        m_name = name;
    m_e = e;
}
 ExprRet Expr_assign::execute(vector<EXPR_DATA>& v)
{
    if (!m_name || !m_e)
        return ExprRet();
    ExprRet ace = m_e->execute(v);
    int pos, type;
    pos = getType(v, m_name, type);
    
    if (ace.type == 258)
    {
        if (pos == -1) {
            cout<<"Warning: try to assign a undeclared variable \"" + *m_name << " \", it\'ll be regard as a INT\n";
        }
        SetValue(v, m_name, pos, (int)ace.num);
    }
    else if (ace.type == 259)
    {
        if (pos == -1) {
            cout<<"Warning: try to assign a undeclared variable \"" + *m_name << " \", it\'ll be regard as a INT\n";
        }
        SetValue(v, m_name, pos, ace.num);
    }
    else if (ace.type == 260)
    {
        if (pos == -1) {
            string msg = "Error: undeclared variable \"" + *m_name + "\" cannot be assigned by a string\n";
            yyerror(msg.c_str());
        }
        else if (type == 258 || type == 259) {
            string msg = "Error: a INT or REAL variable \"" + *m_name + "\" cannot be assigned by a string\n";
            yyerror(msg.c_str());
        }
        string * temp = new string(ace.str);
        SetValue(v, m_name, pos, temp);
    }
    return ace;
}


Expr_num_double::Expr_num_double(double num)
{
    m_num = num;
}
 ExprRet Expr_num_double::execute(vector<EXPR_DATA>& v)
{
    return ExprRet(m_num, "", 259);
}

Expr_num_int::Expr_num_int(int num)
{
    m_num = num;
}
 ExprRet Expr_num_int::execute(vector<EXPR_DATA>& v)
{
    return ExprRet(m_num, "", 258);
}


Expr_num_string::Expr_num_string(string* num)
{
    m_num = *num;
}
 ExprRet Expr_num_string::execute(vector<EXPR_DATA>& v)
{
    return ExprRet(0,m_num, 260);
}


Expr_out::Expr_out(Expression* _printTimes, string* _printHint, Expression* _printContent)
{
    printTimes = _printTimes;
    printHint = _printHint;
    printContent = _printContent;
}
 ExprRet Expr_out::execute(vector<EXPR_DATA>& v)
{
    ExprRet times = printTimes->execute(v);
    ExprRet content = printContent->execute(v);
    if (printHint)
    {
        printf("%s", printHint->c_str());
    }
    for (int i = 0; i < (int)times.num; i++)
    {
		if (content.type == 258)
		{
			if ((int)content.num > 32767 || (int)content.num < -32768)
			{
				printf("warning: Beyond the range of values of int\n");
			}
			printf("%d", (int)content.num);
		}
        else if (content.type == 259)
            printf("%lf", content.num);
        else if (content.type == 260)
            printf("%s", content.str.c_str());
    }
    return ExprRet();
}


Expr_in::Expr_in(string* _readHint, string* _identifier)
{
    readHint = _readHint;
    identifier = _identifier;
}
 ExprRet Expr_in::execute(vector<EXPR_DATA>& v)
{
    if (readHint)
    {
        printf("%s", readHint->c_str());
    }
    int _type;
    int pos = getType(v,identifier, _type);
    if (_type == 258 || _type == 0)//int,
    {
        int tmp;
        scanf("%d", &tmp);
        SetValue(v,identifier, pos, tmp);
    }
    else if (_type == 259)//real	
    {
        double tmp;
        scanf("%lf", &tmp);
        SetValue(v,identifier, pos, tmp);
    }
    else if (_type == 260)//string
    {
        string* tmp = new string;
        cin >> *tmp;
        SetValue(v,identifier, pos, tmp);
    }
    return ExprRet();
}


Expr_ID::Expr_ID(string* name)
{
    if (name)
        m_name = name;
}
 ExprRet Expr_ID::execute(vector<EXPR_DATA>& v)
{
    if (!m_name)
        return ExprRet();
    int type;
    int pos = getType(v, m_name, type);
    if (pos == -1) {
        type = 258;
    }
    if (type == 258)
    {
        int num = GetValue(v, m_name, pos);
        return ExprRet(num, "", 258);
    }
    else if (type == 259)
    {
        double num = GetValue(v, m_name, pos);
        return ExprRet(num, "", 259);
    }
    else
    {
        string num = *GetString(v, m_name, pos);
        return ExprRet(0, num, 260);
    }
}


Expr_if::Expr_if(Expression* con, Expression* et, Expression* ef)
{
    m_con = con;
    m_et = et;
    m_ef = ef;
}
Expr_if::Expr_if(Expression* con, Expression* et)
{
    m_con = con;
    m_et = et;
    m_ef = NULL;
}
 ExprRet Expr_if::execute(vector<EXPR_DATA>& v)
{
    if (!m_con || !m_et) {
        return ExprRet();
    }
    else {
        if (m_ef) {
            ExprRet b = m_con->execute(v);
            if (b.type == 260)
            {
                yyerror("string can not be a Value");
                return ExprRet();
            }
            if (float_eq(b.num,0))
                m_ef->execute(v);
            else
                m_et->execute(v);
        }
        else {
            ExprRet b = m_con->execute(v);
            if (b.type == 260)
            {
                yyerror("string can not be a Value");
                return ExprRet();
            }
            if (!float_eq(b.num,0)) {
                m_et->execute(v);
            }
        }
        return ExprRet();
    }
}


Expr_less::Expr_less(Expression* e1, Expression* e2)
{
    m_e1 = e1;
    m_e2 = e2;
}

 ExprRet Expr_less::execute(vector<EXPR_DATA>& v)
{
    if (!m_e1 || !m_e2)
        return ExprRet();

    ExprRet num1 = m_e1->execute(v);
    ExprRet num2 = m_e2->execute(v);
    if (num1.type == 260 || num2.type == 260)
    {
        yyerror("string can not be compared");
        return ExprRet();
    }
    if (num1.num < num2.num)
    {
        return ExprRet(1,"",258);
    }
    else
        return ExprRet(0, "", 258);
}


Expr_greateq::Expr_greateq(Expression* e1, Expression* e2)
{
    m_e1 = e1;
    m_e2 = e2;
}

 ExprRet Expr_greateq::execute(vector<EXPR_DATA>& v)
{
    if (!m_e1 || !m_e2)
        return ExprRet();
    ExprRet num1 = m_e1->execute(v);
    ExprRet num2 = m_e2->execute(v);
    if (num1.type == 260 || num2.type == 260)
    {
        yyerror("string can not be compared");
        return ExprRet();
    }
    if (num1.num >= num2.num)
    {
        return ExprRet(1, "", 258);
    }
    else return ExprRet(0, "", 258);
}


Expr_eq::Expr_eq(Expression* e1, Expression* e2)
{
    m_e1 = e1;
    m_e2 = e2;
}
  
 ExprRet Expr_eq::execute(vector<EXPR_DATA>& v)
{
    if (!m_e1 || !m_e2)
        return ExprRet();
      
    ExprRet num1 = m_e1->execute(v);
    ExprRet num2 = m_e2->execute(v);
    if (num1.type == 260 || num2.type == 260)
    {
        yyerror("string can not be compared");
        return ExprRet();
    }
    if (float_eq(num1.num, num2.num))
    {
        return ExprRet(1, "", 258);
    }
    return ExprRet(0, "", 258);
}


Expr_neq::Expr_neq(Expression* e1, Expression* e2)
{
    m_e1 = e1;
    m_e2 = e2;
}

 ExprRet Expr_neq::execute(vector<EXPR_DATA>& v)
{
    if (!m_e1 || !m_e2)
        return ExprRet();

    ExprRet num1 = m_e1->execute(v);
    ExprRet num2 = m_e2->execute(v);
    if (num1.type == 260 || num2.type == 260)
    {
        yyerror("string can not be compared");
        return ExprRet();
    }
    if (!float_eq(num1.num, num2.num))
    {
        return ExprRet(1, "", 258);
    }
    return ExprRet(0, "", 258);
}

Expr_or::Expr_or(Expression* e1, Expression* e2)
{
    m_e1 = e1;
    m_e2 = e2;
}

 ExprRet Expr_or::execute(vector<EXPR_DATA>& v)
{
    if (!m_e1 || !m_e2)
        return ExprRet();

    ExprRet num1 = m_e1->execute(v);
    ExprRet num2 = m_e2->execute(v);
    if (num1.type == 260 || num2.type == 260)
    {
        yyerror("string can not be compared");
        return ExprRet();
    }
    return ExprRet((int)num1.num || (int)num2.num, "", 258);
}

Expr_and::Expr_and(Expression* e1, Expression* e2)
{
    m_e1 = e1;
    m_e2 = e2;
}

 ExprRet Expr_and::execute(vector<EXPR_DATA>& v)
{
    if (!m_e1 || !m_e2)
        return ExprRet();

    ExprRet num1 = m_e1->execute(v);
    ExprRet num2 = m_e2->execute(v);
    if (num1.type == 260 || num2.type == 260)
    {
        yyerror("string can not be compared");
        return ExprRet();
    }
    return ExprRet((int)num1.num && (int)num2.num, "", 258);
}

Expr_neg::Expr_neg(Expression* e)
{
    m_e = e;
}

 ExprRet Expr_neg::execute(vector<EXPR_DATA>& v)
{
    if (!m_e)
        return ExprRet();
    ExprRet num = m_e->execute(v);
    if (num.type == 260)
    {
        yyerror("string can not be a value");
        return ExprRet();
    }
    return ExprRet(-num.num, "", num.type);
}

Expr_not::Expr_not(Expression* e)
{
    m_e = e;
}
 ExprRet Expr_not::execute(vector<EXPR_DATA>& v)
{
    if (!m_e)
        return ExprRet();
    ExprRet num = m_e->execute(v);
    if (num.type == 260)
    {
        yyerror("string can not be a value");
        return ExprRet();
    }
    return ExprRet(!(int)num.num, "", 258);
}

Expr_while::Expr_while(Expression* con, Expression* e)
{
    m_con = con;
    m_e = e;
}

 ExprRet Expr_while::execute(vector<EXPR_DATA>& v)
{
    if (!m_con || !m_e)
      return ExprRet();

    ExprRet ace = m_con->execute( v);
    if (ace.type == 260)
    {
        yyerror("string can not be a value");
        return ExprRet();
    }
    while (!float_eq(ace.num, 0))
    {
        m_e->execute(v);
        ace = m_con->execute(v);
    }

    return ExprRet();
}
 Expr_dountil::Expr_dountil(Expression* e,Expression* con)
 {
	 m_con = con;
	 m_e = e;
 }
 ExprRet Expr_dountil::execute(vector<EXPR_DATA>& v)
 {
	 if (!m_con || !m_e)
		 return ExprRet();

	 ExprRet ace = m_con->execute(v);
	 if (ace.type == 260)
	 {
		 yyerror("string can not be a value");
		 return ExprRet();
	 }
	 do
	 {
		 m_e->execute(v);
		 ace = m_con->execute(v);
	 } while (float_eq(ace.num, 0));
	 return ExprRet();
 }
Expr_break::Expr_break()
{
    ;
}
ExprRet Expr_break::execute(vector<EXPR_DATA>& v)
{
    return ExprRet();
}
Expr_continue::Expr_continue()
{
    ;
}
ExprRet Expr_continue::execute(vector<EXPR_DATA>& v)
{
    return ExprRet();
}
Expr_return::Expr_return()
{
    ;
}
Expr_return::Expr_return(Expression* expr)
{
    this->m_e = expr;
}
ExprRet Expr_return::execute(vector<EXPR_DATA>& v)
{
    return ExprRet();
}
Expr_block::Expr_block(Expressions* exprs)
{
    m_exprs = exprs;
}

ExprRet Expr_block::execute(vector<EXPR_DATA>& v)
{
    if (!m_exprs)
        return ExprRet();
    return m_exprs->execute(v);
}


Expression* t_id(string* name)
{
  return new Expr_ID(name);
}

Expression* t_num_int(int num)
{
  return new Expr_num_int(num);
}

Expression* t_num_double(double num)
{
    return new Expr_num_double(num);
}

Expression* t_num_string(string* num)
{
    return new Expr_num_string(num);
}

Expression* t_assign(string* name, Expression* e)
{
  return new Expr_assign(name, e);
}

Expression* t_plus(Expression* e1, Expression* e2)
{
  return new Expr_plus(e1, e2);
}

Expression* t_sub(Expression* e1, Expression* e2)
{
  return new Expr_sub(e1, e2);
}

Expression* t_mul(Expression* e1, Expression* e2)
{
  return new Expr_mul(e1, e2);
}

Expression* t_div(Expression* e1, Expression* e2)
{
  return new Expr_div(e1, e2);
}
Expression* t_mod(Expression* e1, Expression* e2)
{
	return new Expr_mod(e1, e2);
}
Expression* t_pow(Expression* e1, Expression* e2)
{
	return new Expr_pow(e1, e2);
}
Expression* t_splus(Expression* e1, Expression* e2)
{
	return new Expr_splus(e1, e2);
}
Expression* t_ssub(Expression* e1)
{
	return new Expr_ssub(e1);
}
Expression* t_if(Expression* con, Expression* et, Expression* ef)
{
  return new Expr_if(con, et, ef);
}

Expression* t_if(Expression* con, Expression* et)
{
    return new Expr_if(con, et);
}

Expression* t_less(Expression* e1, Expression* e2)
{
  return new Expr_less(e1, e2);
}

Expression* t_greateq(Expression* e1, Expression* e2)
{
	return new Expr_greateq(e1, e2);
}
Expression* t_eq(Expression* e1, Expression* e2)
{
	return new Expr_eq(e1, e2);
}
Expression* t_neq(Expression* e1, Expression* e2)
{
	return new Expr_neq(e1, e2);
}
Expression* t_or(Expression* e1, Expression* e2)
{
	return new Expr_or(e1, e2);
}
Expression* t_and(Expression* e1, Expression* e2)
{
	return new Expr_and(e1, e2);
}
Expression* t_neg(Expression* e1)
{
	return new Expr_neg(e1);
}
Expression* t_not(Expression* e1)
{
	return new Expr_not(e1);
}
Expression* t_while(Expression* con, Expression* e)
{
  return new Expr_while(con, e);
}
Expression* t_dountil(Expression* con, Expression* e)
{
	return new Expr_dountil(con, e);
}
Expression* t_break()
{
    return new Expr_break();
}
Expression* t_continue()
{
    return new Expr_continue();
}
Expression* t_return(Expression* con)
{
    return new Expr_return(con);
}
Expression* t_block(Expressions* exprs)
{
  return new Expr_block(exprs);
}

Expression* t_out(Expression* _printTimes, string* _printHint, Expression* _printContent)
{
    return new Expr_out(_printTimes, _printHint, _printContent);
}

Expression* t_in(string* _readHint, string* _identifier)
{
    return new Expr_in(_readHint, _identifier);
}

Expressions* t_single_exprs(Expression* e)
{
  return new Expressions(e);
}

Expressions* t_append_exprs(Expressions* exprs, Expression* e)
{
  if (exprs && e)
	exprs->push(e);
  return exprs;
}
