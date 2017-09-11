#ifndef SYMTAB_HPP
#define SYMTAB_HPP
#include <string>
#include <vector>
using namespace std;
#define INT 258
#define REAL 259
#define STRING 260

struct EXPR_DATA
{
	string name;
	int type;
	union {
		string* str;
		double num;
	}data;
};

vector<EXPR_DATA> global_var;

int getType(vector<EXPR_DATA>& vars, string * identifier, int& type)
{
	int i=0;
	for (i=0; i<vars.size(); i++) 
	{
		if (vars[i].name == *identifier)
		{
			type = vars[i].type;
			return i;
		}
	}
	return i;
}

void SetValue(vector<EXPR_DATA>& vars, string* identifier, const int& pos, const int& num)
{
   if (pos == vars.size())
   {
   		EXPR_DATA a;
   		a.name = *identifier;
   		a.type = INT;
        a.data.num = num;
   		vars.push_back(a);
   		return ;
   }
   vars[pos].data.num = num;
   return ;
}

void SetValue(vector<EXPR_DATA>& vars, string* identifier, const int& pos, const double& num)
{
   if (pos == vars.size())
   {
   		EXPR_DATA a;
   		a.name = *identifier;
   		a.type = REAL;
   		a.data.num = num;
   		vars.push_back(a);
   		return ;
   }
   vars[pos].data.num = num;
   return ;
}

void SetValue(vector<EXPR_DATA>& vars, string* identifier, const int& pos, string* str)
{
   if (pos == vars.size())
   {
   		throw string("Undeclared identifier");
   		return;
   }
   vars[pos].data.str = str;
   return ;
}

double GetValue(vector<EXPR_DATA>& vars, string* name)
{//get value from scope vars
 	int type = 0;
 	int pos = getType(vars, name, type);
 	string msg;
 	if (pos == vars.size())
 	{
 		msg = "Undeclared identifier, set it to int";
 		SetValue(vars, name, pos, 0);
 		throw msg;
 		return 0;
 	}
 	if (type == STRING)
 	{
 		msg = "Invalid usage, cannot get string";
 		throw msg;
 		return 0;
 	}
    return vars[pos].data.num;
}

string* GetString(vector<EXPR_DATA>& vars, string* name)
{
	int type = 0;
 	int pos = getType(vars, name, type);
 	string msg;
 	if (pos == vars.size())
 	{
 		msg = "Undeclared identifier";
 		throw msg;
 		return 0;
 	}
 	if (type != STRING)
 	{
 		msg = "Invalid usage, cannot get string";
 		throw msg;
 		return 0;
 	}
    return vars[pos].data.str;
}

#endif
