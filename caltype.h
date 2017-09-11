#ifndef CALTYPE_H
#define CALTYPE_H
#include <string>

enum VarType 
{
	Int=258, Real=259, String=260
};

struct EXPR_DATA
{
	string name;
	VarType type;
	union data {
		string* str;
		double num;
	};
};

#endif
