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
	union data {
		string* str;
		double num;
	};
};

vector<EXPR_DATA> global_var;

int getType(string * identifier, int& type);
{
	int i=0;
	for (i=0; i<global_var.size(); i++) 
	{
		if (global_var[i].name == *identifier)
		{
			type = global_var[i].type;
			return i;
		}
	}
	return i;
}

void SetValue(string* identifier, const int& pos, const int& num)
{
   if (pos == global_var.size())
   {
   		EXPR_DATA a;
   		a.name = *identifier;
   		a.type = INT;
   		a.data.num = num;
   		global_var.push_back(a);
   		return ;
   }
   global_var[pos].data.num = num;
   return ;
}

void SetValue(string* identifier, const int& pos, const double& num)
{
   if (pos == global_var.size())
   {
   		EXPR_DATA a;
   		a.name = *identifier;
   		a.type = REAL;
   		a.data.num = num;
   		global_var.push_back(a);
   		return ;
   }
   global_var[pos].data.num = num;
   return ;
}

void SetValue(string* identifier, const int& pos, string* str)
{
   if (pos == global_var.size())
   {
   		throw string("Undeclared identifier");
   		return;
   }
   global_var[pos].data.str = str;
   return ;
}

double GetValue(string* name)
{
 	int type = 0;
 	int pos = getType(name, type);
 	string msg;
 	if (pos == global_var.size())
 	{
 		msg = "Undeclared identifier, set it to int";
 		SetValue(name, pos, 0);
 		throw msg;
 		return 0;
 	}
 	if (type == STRING)
 	{
 		mes = "Invalid usage, cannot get string";
 		throw msg;
 		return 0;
 	}
    return global_var[pos].data.num;
}

string* GetString(string* name)
{
	int type = 0;
 	int pos = getType(name, type);
 	string msg;
 	if (pos == global_var.size())
 	{
 		msg = "Undeclared identifier";
 		throw msg;
 		return 0;
 	}
 	if (type != STRING)
 	{
 		mes = "Invalid usage, cannot get string";
 		throw msg;
 		return 0;
 	}
    return global_var[pos].data.str;
}

#endif
