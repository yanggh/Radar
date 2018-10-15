#include "DataBlock.h"
#include <iostream>

int main()
{
    DataBlock  datablock;

    char  message[] = "1234567890123456789012\17\0\0\0a23456789012345012345678901234567891234567890123456789012\17\0\0\0a23456789012345012345678901234567891234567890123456789012\17\0\0\0a23456789012345012345678901234567891234567890123456789012\17\0\0\0a2345678901234501234567890123456789";
    size_t  pos = 0;

    for(int i = 0; i < 4; i ++)
    {
        pos = datablock.DataBlockHandle(message, pos);
        std::cout << "pos = " << pos << std::endl;
        cout << datablock;
        cout << "----------------" << endl;
    }
}
