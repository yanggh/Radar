#ifndef  DataBlock_H
#define  DataBlock_H
#include <string>
#include <cstdint>
using namespace std;
class  DataBlock{
private:
    std::string _eventCode;
    uint16_t    _validIdentity;
    uint32_t    _data_len;
    std::string _data;
    std::string _bak;
public:
    DataBlock();

    std::string  GetEventCode();
    uint16_t     GetValidIdentity();
    uint32_t     GetDataLen();
    std::string  GetData();
    std::string  GetBak();
    
    friend ostream& operator<<(ostream& out, const DataBlock& datablock);
    size_t  DataBlockHandle(const char* message, const size_t pos);
};
#endif
