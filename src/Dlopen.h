#ifndef _DLOPEN_H_
#define _DLOPEN_H_
#include <dlfcn.h>
#include <string>
#include <iostream>
using namespace std;

typedef int (*FUNC)(int* out1_len, void* out1, int in1_len, void* in1, int in2_len, void* in2, int in3_len, void* in3, int in4_len, void* in4, int in5_len, void* in5);

class DLOPEN
{
private:
    void    *handle;
    char    *error;
public:
    DLOPEN(const string dll);
    ~DLOPEN();
    FUNC search_func(string func);
};
#endif
