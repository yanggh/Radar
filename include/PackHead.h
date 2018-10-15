#ifndef _PackHead_H
#define _PackHead_H

#include <iostream>
#include <cstdint>
using namespace std;
class PackHead
{
public:
    PackHead();
    size_t    PackHeadHandle(const char* message, const size_t pos);
    uint32_t  GetMsgNo() const;
    uint8_t   GetMsgType() const;
    uint8_t   GetMsgVer() const;
    uint16_t  GetHlen() const;
    uint32_t  GetSlen() const;
    uint32_t  GetTest() const;
    string    GetDate() const;
    uint32_t  GetSessId() const;
    uint8_t   GetResNo() const;
    uint8_t   GetErrCode() const;
    uint8_t   GetDivNo() const;
    uint16_t  GetDivs() const;
    uint16_t  GetDiv() const;
    uint16_t  GetBlocks() const;
    string    GetBak() const;

    friend ostream& operator<<(ostream& out, const PackHead&  packhead);
private:
    uint32_t MsgNo{0};
    uint8_t  MsgType{0};
    uint8_t  MsgVer{0};
    uint16_t Hlen{0};
    uint32_t Slen{0};
    uint32_t Test{0};
    string   Date;
    uint32_t SessId{0};
    uint8_t  ResNo{0};
    uint8_t  ErrCode{0};
    uint8_t  DivNo{0};
    uint16_t Divs{0};
    uint16_t Div{0};
    uint16_t Blocks{0};
    string   Bak; 
};
#endif
