#include <string>
#include <vector>
#include "symtab.h"
using namespace std;
#define INT 258
#define REAL 259
#define STRING 260


 vector<EXPR_DATA> global_var;

int getType(vector<EXPR_DATA>& local_var, string * identifier, int& type)
{
    int i;
	for (i=local_var.size()-1; i>=0; i--)
	{
		if (local_var[i].name == *identifier)
		{
			type = local_var[i].type;
			return i;
		}
	}
	return i;
}

void SetValue(vector<EXPR_DATA>& local_var, string* identifier, const int& pos, const int& num)
{
    if (pos == local_var.size())
    {//identifier does not exist
   		EXPR_DATA a;
   		a.name = *identifier;
   		a.type = INT;
        a.data.num = num;
   		local_var.push_back(a);
   		return ;
    }
    local_var[pos].data.num = num;
    return ;
}

void SetValue(vector<EXPR_DATA>& local_var, string* identifier, const int& pos, const double& num)
{
   if (pos == local_var.size())
   {//identifier does not exist
   		EXPR_DATA a;
   		a.name = *identifier;
   		a.type = REAL;
   		a.data.num = num;
   		local_var.push_back(a);
   		return ;
   }
   local_var[pos].data.num = num;
   return ;
}

void SetValue(vector<EXPR_DATA>& local_var, string* identifier, const int& pos, string* str)
{
   if (pos == local_var.size())
   {//identifier does not exist
   		throw string("Undeclared identifier");
   		return;
   }
   local_var[pos].data.str = str;
   return ;
}

double GetValue(vector<EXPR_DATA>& local_var, string* name, const int& pos)
{//get value from scope local_var
 	string msg;
 	if (pos == local_var.size())
 	{
 		msg = "Undeclared identifier, set it to int";
 		SetValue(local_var, name, pos, 0);
 		throw msg;
 	}
    return local_var[pos].data.num;
}

string* GetString(vector<EXPR_DATA>& local_var, string* name, const int& pos)
{
 	string msg;
 	if (pos == local_var.size())
 	{
 		msg = "Undeclared identifier";
 		throw msg;
 		return 0;
 	}
    return local_var[pos].data.str;
}
