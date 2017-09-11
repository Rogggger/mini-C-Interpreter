
#include "exprtree.h"
#include "symtab.hpp"
#include <stdio.h>
#include <vector>
#include<string>
using namespaces std;
bool float_eq(double id, double num)
{
  double sub = id - num;
  if (sub < 0.00001f && sub > -0.00001f)
    return true;
  return false;
}

struct ExprRet {
    ExprRet(const double& a, const string& s,const int &t)
    {
        num = a;
		str = s;
		type = t;
    }
    ExprRet()
    {
        num = 0;
        str = "";
		type = 258;
    }
    int type;
    double num;
    string str;
};

class Expression
{
public:
  Expression(){};
  virtual ExprRet execute(vector<EXPR_DATA>& v)
  {
	return ExprRet();
  };
};

class Expressions
{
public:
  Expressions(Expression* e)
  {
    push(e);
  }

  void push(Expression* e)
  {
    m_vExpr.push_back(e);
  }
  virtual ExprRet execute(vector<EXPR_DATA>& v)
  {
    for (int i = 0; i < m_vExpr.size(); i++)
    {
		if (m_vExpr[i])
			m_vExpr[i]->execute(vector<EXPR_DATA>& v);
    }
	return ExprRet();
  };

  std::vector<Expression*> m_vExpr;
};

class Expr_plus : public Expression
{
public:
  Expr_plus(Expression* e1, Expression* e2)
  {
	m_e1 = e1;
	m_e2 = e2;
  }
  virtual ExprRet execute(vector<EXPR_DATA>& v)
  {
	if (!m_e1 || !m_e2)
	  return ExprRet();
	ExprRet num1 = m_e1->execute(vector<EXPR_DATA>& v);
	ExprRet num2 = m_e2->execute(vector<EXPR_DATA>& v);
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

protected:
  Expression* m_e1;
  Expression* m_e2;
};

class Expr_sub : public Expression
{
public:
  Expr_sub(Expression* e1, Expression* e2)
  {
	m_e1 = e1;
	m_e2 = e2;
  }
  virtual ExprRet execute(vector<EXPR_DATA>& v)
  {
	if (!m_e1 || !m_e2)
		return ExprRet();
	ExprRet num1 = m_e1->execute(vector<EXPR_DATA>& v);
	ExprRet num2 = m_e2->execute(vector<EXPR_DATA>& v);
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

protected:
  Expression* m_e1;
  Expression* m_e2;
};

class Expr_mul : public Expression
{
public:
  Expr_mul(Expression* e1, Expression* e2)
  {
	m_e1 = e1;
	m_e2 = e2;
  }
  virtual ExprRet execute(vector<EXPR_DATA>& v)
  {
	if (!m_e1 || !m_e2)
		return ExprRet();
	ExprRet num1 = m_e1->execute(vector<EXPR_DATA>& v);
	ExprRet num2 = m_e2->execute(vector<EXPR_DATA>& v);
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

protected:
  Expression* m_e1;
  Expression* m_e2;
};

class Expr_div : public Expression
{
public:
  Expr_div(Expression* e1, Expression* e2)
  {
	m_e1 = e1;
	m_e2 = e2;
  }
  virtual ExprRet execute(vector<EXPR_DATA>& v)
  {
	if (!m_e1 || !m_e2)
		return ExprRet();
	ExprRet num1 = m_e1->execute(vector<EXPR_DATA>& v);
	ExprRet num2 = m_e2->execute(vector<EXPR_DATA>& v);
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

protected:
  Expression* m_e1;
  Expression* m_e2;
};
class Expr_mod : public Expression
{
public:
	Expr_mod(Expression* e1, Expression* e2)
	{
		m_e1 = e1;
		m_e2 = e2;
	}
	virtual ExprRet execute(vector<EXPR_DATA>& v)
	{
		if (!m_e1 || !m_e2)
			return 0;
		ExprRet num1 = m_e1->execute(vector<EXPR_DATA>& v);
		ExprRet num2 = m_e2->execute(vector<EXPR_DATA>& v);
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

protected:
	Expression* m_e1;
	Expression* m_e2;
};
class Expr_assign : public Expression
{
public:
  Expr_assign(string* name, Expression* e)
  {
	  if (name)
		  m_name = name;
	  m_e = e;
  }
  virtual ExprRet execute(vector<EXPR_DATA>& v)
  {
	if (!m_name || !m_e)
		return ExprRet();
	
	ExprRet ace = m_e->execute(vector<EXPR_DATA>& v);
	int pos, type;
	pos = getType(v, m_name, type);
	if (ace.type == 258)
	{
		SetValue(v, m_name, pos,() ace.num);
	}
	else if (ace.type == 259)
	{
		SetValue(v, m_name, pos, ace.num);
	}
	else if (ace.type == 260)
	{
		SetValue(v, m_name, pos, ace.str);
	}
	return ace;
  }

protected:
  string*    m_name;
  Expression* m_e;
};

class Expr_num_double : public Expression
{
public:
  Expr_num_double(double num)
  {
	m_num = num;
  }
  virtual ExprRet execute(vector<EXPR_DATA>& v)
  {
	  return ExprRet(num, "", 259);
  }
protected:
  double m_num;
};
class Expr_num_int : public Expression
{
public:
	Expr_num_int(int num)
	{
		m_num = num;
	}
	virtual ExprRet execute(vector<EXPR_DATA>& v)
	{
		return ExprRet(num, "", 258);
	}
protected:
	int double m_num;
};
class Expr_out :public Expression
{
public:
	Expr_out(int _printTimes, string* _printHint, string* _printContent)
	{
		printTimes = _printTimes;
		printHint = _printHint;
		printContent = _printContent;
	}
	virtual ExprRet execute(vector<EXPR_DATA>& v))
	{
		if (printHint)
		{
			printf("%s", *printHint);
		}
		for (int i = 0; i < printTimes; i++)
		{
			printf("%s", *printContent);
		}
		return ExprRet();
	}
protected:
	int printTimes;
	string* printHint;
	string* printContent;
};
class Expr_in :public Expression
{
public:
	Expr_in(string* _readHint, string* _identifier)
	{
		readHint = _readHint;
		identifier = _identifier;
	}
	virtual ExprRet excute(vector<EXPR_DATA>& v)
	{
		if (readHint)
		{
			printf("%s", readHint);
		}
		int _type;
		int pos = getType(v,identifier, _type);
		if (_type == 258 || _type == 0)//int,Î´ÉùÃ÷
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
protected:
	string* readHint;
	string* identifier;
};
class Expr_ID : public Expression
{
public:
  Expr_ID(string* name)
  {
	  if (name)
		  m_name = name;
  }
  virtual ExprRet execute(vector<EXPR_DATA>& v)
  {
	if (!m_name)
	  return ExprRet();
	int type;
	int pos = getType(v, m_name, type);
	if (type == 258)
	{
		int num = getValue(v, m_name, pos);
		return ExprRet(num, "", 258);
	}
	else if (type == 259)
	{
		double num = getValue(v, m_name, pos);
		return ExprRet(num, "", 259);
	}
	else
	{
		string num = getString(v, m_name, pos);
		return ExprRet(0, num, 260);
	}
  }

protected:
  string* m_name;
};

class Expr_if : public Expression
{
public:
  Expr_if(Expression* con, Expression* et, Expression* ef)
  {
	m_con = con;
	m_et = et;
	m_ef = ef;
  }
  Expr_if(Expression* con, Expression* et)
    {
        m_con = con;
        m_et = et;
        m_ef = NULL;
    }
  virtual ExprRet execute(vector<EXPR_DATA>& v)
  {
      if (!m_con || !m_et) {
          if (!m_ef) {
			  ExprRet b = m_con->execute(v);
			  if (b.type == 260)
			  {
				  throw(string("string can not be a Value"));
			  }
              if (float(b.num,0))
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

protected:
  Expression* m_con;
  Expression* m_et;
  Expression* m_ef;
};

class Expr_less : public Expression
{
public:
  Expr_less(Expression* e1, Expression* e2)
  {
    m_e1 = e1;
    m_e2 = e2;
  }
  
  virtual ExprRet execute(vector<EXPR_DATA>& v)
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
    else return ExprRet(0, "", 258);
  }

protected:
  Expression* m_e1;
  Expression* m_e2;
};
class Expr_greateq : public Expression
{
public:
	Expr_greateq(Expression* e1, Expression* e2)
	{
		m_e1 = e1;
		m_e2 = e2;
	}

	virtual double execute(vector<EXPR_DATA>& v)
	{
		if (!m_e1 || !m_e2)
			return 0;
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

protected:
	Expression* m_e1;
	Expression* m_e2;
};
class Expr_eq : public Expression
{
public:
  Expr_eq(Expression* e1, Expression* e2)
  {
    m_e1 = e1;
    m_e2 = e2;
  }
  
  virtual ExprRet execute(vector<EXPR_DATA>& v)
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

protected:
  Expression* m_e1;
  Expression* m_e2;
};
class Expr_neq : public Expression
{
public:
	Expr_neq(Expression* e1, Expression* e2)
	{
		m_e1 = e1;
		m_e2 = e2;
	}

	virtual ExprRet execute(vector<EXPR_DATA>& v)
	{
		if (!m_e1 || !m_e2)
			return 0;

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

protected:
	Expression* m_e1;
	Expression* m_e2;
};
class Expr_or : public Expression
{
public:
	Expr_or(Expression* e1, Expression* e2)
	{
		m_e1 = e1;
		m_e2 = e2;
	}

	virtual ExprRet execute(vector<EXPR_DATA>& v)
	{
		if (!m_e1 || !m_e2)
			return 0;

		ExprRet num1 = m_e1->execute(v);
		ExprRet num2 = m_e2->execute(v);
		if (num1.type == 260 || num2.type == 260)
		{
			throw(string("string can not be compared"));
		}
		return ExprRet((int)num1.num || (int)num2.num, "", 258);
	}

protected:
	Expression* m_e1;
	Expression* m_e2;
};
class Expr_and : public Expression
{
public:
	Expr_and(Expression* e1, Expression* e2)
	{
		m_e1 = e1;
		m_e2 = e2;
	}

	virtual ExprRet execute(vector<EXPR_DATA>& v)
	{
		if (!m_e1 || !m_e2)
			return 0;

		ExprRet num1 = m_e1->execute(v);
		ExprRet num2 = m_e2->execute(v);
		if (num1.type == 260 || num2.type == 260)
		{
			throw(string("string can not be compared"));
		}
		return ExprRet((int)num1.num && (int)num2.num, "", 258);
	}

protected:
	Expression* m_e1;
	Expression* m_e2;
};
class Expr_neg : public Expression
{
public:
	Expr_neg(Expression* e)
	{
		m_e = e;
	}
	virtual ExprRet execute(vector<EXPR_DATA>& v)
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

protected:
	Expression* m_e;
};
class Expr_not : public Expression
{
public:
	Expr_not(Expression* e)
	{
		m_e = e;
	}
	virtual ExprRet execute(vector<EXPR_DATA>& v)
	{
		if (!m_e)
			return ExprRet(v);
		ExprRet num = m_e->execute(v);
		if (num.type == 260)
		{
			throw(string("string can not be a value"));
		}
		return ExprRet(!(int)num.num, "", 258);
	}

protected:
	Expression* m_e;
};
class Expr_while : public Expression
{
public:
  Expr_while(Expression* con, Expression* e)
  {
    m_con = con;
    m_e = e;
  }
  
  virtual ExprRet execute(vector<EXPR_DATA>& v)
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

protected:
  Expression* m_con;
  Expression* m_e;
};

class Expr_block : public Expression
{
public:
  Expr_block(Expressions* exprs)
  {
    m_exprs = exprs;
  }
  
  virtual ExprRet execute(vector<EXPR_DATA>& v)
  {
	if (!m_exprs)
	  return ExprRet();
    return m_exprs->execute(v);
  }

protected:
  Expressions* m_exprs;
};

Expression* t_id(char* name)
{
  return new Expr_ID(name);
}

Expression* t_num(double num)
{
  return new Expr_num(num);
}

Expression* t_assign(char* name, Expression* e)
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
	return new Expr_eq(e1);
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
