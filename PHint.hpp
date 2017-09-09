#ifndef PHINT
#define PHINT
#include <iostream>
#include <cstring>
using namespace std;

class PHint {
public:
    int count;
    char str[32];
};

void t_out(int c, char* ch, char* s)
{
    cout<<ch;
    for (int i=0; i<c; i++) {
        cout<<s<<endl;
    }
    return ;
}

#endif
