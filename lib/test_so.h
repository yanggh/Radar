#ifndef _TEST_SO_
#define _TEST_SO_
#include <string>
using namespace std;
extern "C"
{
int add(int* out1_len, void* out1, int in1_len, void* in1, int in2_len, void* in2, int in3_len, void* in3, int in4_len, void* in4, int in5_len, void* in5);

int sub(int* out1_len, void* out1, int in1_len, void* in1, int in2_len, void* in2, int in3_len, void* in3, int in4_len, void* in4, int in5_len, void* in5);
}
#endif
