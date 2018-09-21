#ifndef  DataBlock_H
#define  DataBlock_H
#include <string>
#include <cstdint>
using namespace std;
class  DataBlock{
private:
    std::string _eventCode;
    std::string _validIdentity;
    std::string _data;
    std::string _bak;
public:
    DataBlock();
    friend ostream& operator<<(ostream& out, const DataBlock& datablock);
    size_t  DataBlockHandle(const char* message, const size_t pos);
};
#endif
