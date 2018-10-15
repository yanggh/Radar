#include "DataBlock.h"
#include <iostream>
#include <cstring>

DataBlock::DataBlock(){
    _eventCode.resize(20);
}

std::string  DataBlock::GetEventCode()
{
    return _eventCode;
}

uint16_t DataBlock::GetValidIdentity()
{
    return _validIdentity;
}

uint32_t DataBlock::GetDataLen()
{
    return  _data_len;
}

std::string DataBlock::GetData()
{
    return _data;
}

std::string DataBlock::GetBak()
{
    return _bak;
}

ostream& operator<<(ostream& out, const DataBlock& datablock)
{
    out << "eventCode:" << datablock._eventCode<< endl;
    out << "validIdentity :" << datablock._validIdentity<< endl;
    out << "data_len :" << datablock._data_len << endl;
    out << "data :" << datablock._data<< endl;
    out << "bak :" << datablock._bak<< endl;

    return out;
}

size_t  DataBlock::DataBlockHandle(const char* message, const size_t pos)
{
    size_t  cur = 0;

    _eventCode.assign(message + pos + cur, 20);
    cur += 20;

    memcpy(&_validIdentity, message + pos + cur, 2);
    cur += 2;

    memcpy(&_data_len, message + pos + cur, 4);
    cur += 4;

    _data.resize(_data_len);
    _data.assign(message + pos + cur, _data_len);
    cur += _data_len;

    _bak.assign(message + pos + cur, 20);
    cur += 20;

    return cur + pos;
}
