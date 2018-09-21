#include <stdio.h>
#include "test_so.h"

using namespace std;

int add(int* out1_len, void* out1, int in1_len, void* in1, int in2_len, void* in2, int in3_len, void* in3, int in4_len, void* in4, int in5_len, void* in5)
{
    printf("asdfasdfasdfasdfasdfsadadd  add\n");
    return in1_len +in2_len;
}

int sub(int* out1_len, void* out1, int in1_len, void* in1, int in2_len, void* in2, int in3_len, void* in3, int in4_len, void* in4, int in5_len, void* in5)
{
    printf("asdfasdfasdfasdfasdfsadadd  sub\n");
    return in1_len - in2_len;
}
