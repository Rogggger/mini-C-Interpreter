#ifndef SYMTAB_H
#define SYMTAB_H

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

extern vector<EXPR_DATA> global_var;

int getType(vector<EXPR_DATA>& local_var, string * identifier, int& type);
void SetValue(vector<EXPR_DATA>& local_var, string* identifier, const int& pos, const int& num);

void SetValue(vector<EXPR_DATA>& local_var, string* identifier, const int& pos, const double& num);

void SetValue(vector<EXPR_DATA>& local_var, string* identifier, const int& pos, string* str);
double GetValue(vector<EXPR_DATA>& local_var, string* name, const int& pos);

string* GetString(vector<EXPR_DATA>& local_var, string* name, const int& pos);

#endif
