#include <iostream>
#include <string>
#include <vector>
#include "symtab.h"
using namespace std;
#define INT 258
#define REAL 259
#define STRING 260
extern void yyerror(const char *);


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
    type = -1;
	return -1;
}

void SetValue(vector<EXPR_DATA>& local_var, string* identifier, const int& pos, const int& num)
{
    if (pos == -1)
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
   if (pos == -1)
   {//identifier does not exist
   		EXPR_DATA a;
   		a.name = *identifier;
   		a.type = INT;// Undeclare set to INT
   		a.data.num = num;
   		local_var.push_back(a);
   		return ;
   }
   local_var[pos].data.num = num;
   return ;
}

void SetValue(vector<EXPR_DATA>& local_var, string* identifier, const int& pos, string* str)
{
   if (pos == -1)
   {//identifier does not exist
       string msg = "Error : \"" + *identifier + "\" Undeclared identifier";
       yyerror(msg.c_str());
   }
   local_var[pos].data.str = str;
   return ;
}

double GetValue(vector<EXPR_DATA>& local_var, string* name, const int& pos)
{//get value from scope local_var
 	if (pos == -1)
 	{
 		SetValue(local_var, name, pos, 0);
        std::cout<< "Warning : \""+ *name + "\" Undeclared identifier, it\'ll be regard as a INT\n";
 	}
    return local_var[pos].data.num;
}

string* GetString(vector<EXPR_DATA>& local_var, string* name, const int& pos)
{
 	if (pos == -1)
 	{
        string msg = "Error : \""+ *name + "\" Undeclared identifier";
 		yyerror(msg.c_str());
 		return 0;
 	}
    return local_var[pos].data.str;
}
