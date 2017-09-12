#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include "exprtree.h"

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
        throw(string("string can not be plused"));
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
        throw(string("string can not be subed"));
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
        throw(string("string can not be mul"));
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
            throw(string("divided by zero"));
        }
        else 
            return ExprRet((int)num1.num / (int)num2.num, "", 258);
    }
    else if ((num1.type == 259 || num2.type == 259) && (num1.type != 260 && num2.type != 260))
    {
        if (float_eq(num2.num,0))
        {
            throw(string("divided by zero"));
        }
        else 
            return ExprRet(num1.num / num2.num, "", 259);
    }
    else
    {
        throw(string("string can not be divided"));
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
            throw(string("divided by zero"));
        }
        else
            return ExprRet((int)num1.num % (int)num2.num, "", 258);
    }
    else
    {
        throw(string("Only an integer can take the remainder"));
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
        SetValue(v, m_name, pos, ace.num);
    }
    else if (ace.type == 259)
    {
        SetValue(v, m_name, pos, ace.num);
    }
    else if (ace.type == 260)
    {
        SetValue(v, m_name, pos, &ace.str);
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
        if(content.type==258)
            printf("%d", (int)content.num);
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
 ExprRet Expr_in::excute(vector<EXPR_DATA>& v)
{
    if (readHint)
    {
        printf("%s", readHint->c_str());
    }
    int _type;
    int pos = getType(v,identifier, _type);
    if (_type == 258 || _type == 0)//int,δ����
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
      if (!m_ef) {
          ExprRet b = m_con->execute(v);
          if (b.type == 260)
          {
              throw(string("string can not be a Value"));
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
              throw(string("string can not be a Value"));
          }
          if (!float_eq(b.num,0)) {
              m_et->execute(v);
          }
      }
  }
  return ExprRet();
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
        throw(string("string can not be compared"));
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
        throw(string("string can not be compared"));
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
        throw(string("string can not be compared"));
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
        throw(string("string can not be compared"));
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
        throw(string("string can not be compared"));
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
        throw(string("string can not be compared"));
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
        throw(string("string can not be a value"));
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
        throw(string("string can not be a value"));
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
        throw(string("string can not be a value"));
    }
    while (!float_eq(ace.num, 0))
    {
        m_e->execute(v);
        ace = m_con->execute(v);
    }

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
