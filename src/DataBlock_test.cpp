#include "DataBlock.h"
#include <iostream>

int main()
{
    DataBlock  datablock;
    
    char  message[] = "1234567890123456789012\17\0\0\0a234567890123456789012345678901234567890";

    size_t  pos = datablock.DataBlockHandle(message, 0);
    std::cout << "pos = " << pos << std::endl;

    cout << datablock;
}
