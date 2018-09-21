#include "DataBlock.h"
#include <iostream>
#include <cstring>

DataBlock::DataBlock(){
    _eventCode.resize(20);
    _validIdentity.resize(2); 
}

ostream& operator<<(ostream& out, const DataBlock& datablock)
{
    out << "eventCode:" << datablock._eventCode<< endl;
    out << "validIdentity :" << datablock._validIdentity<< endl;
    out << "data :" << datablock._data<< endl;
    out << "bak :" << datablock._bak<< endl;

    return out;
}

size_t  DataBlock::DataBlockHandle(const char* message, const size_t pos)
{
    size_t  cur = 0;
    uint32_t data_len = 0;

    _eventCode.assign(message + pos + cur, 20);
    cur += 20;

    _validIdentity.assign(message + pos + cur, 2);
    cur += 2;

    memcpy(&data_len, message + pos + cur, 4);
    cur += 4;
    cout << "data_len = " << data_len << endl; 

    _data.resize(data_len);
    _data.assign(message + pos + cur, data_len);
    cur += data_len;
    
    _bak.assign(message + pos + cur, 20);
    cur += 20;

    return cur;
}
