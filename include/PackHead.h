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
    string    GetRaw() const;

    void  SetMsgNo(const uint32_t MsgNo);
    void  SetMsgType(const uint8_t MsgType);
    void  SetMsgVer(const uint8_t MsgVer);
    void  SetHlen(const uint16_t Hlen);
    void  SetSlen(const uint32_t Slen);
    void  SetTest(const uint32_t Test);
    void  SetDate(const string& Date);
    void  SetSessId(const uint32_t SessId);
    void  SetResNo(const uint8_t ResNo);
    void  SetErrCode(const uint8_t ErrCode);
    void  SetDivNo(const uint8_t DivNo);
    void  SetDivs(const uint16_t Divs);
    void  SetDiv(const uint16_t Div);
    void  SetBlocks(const uint16_t Blocks);
    void  SetBak(const string& Bak);

    friend ostream& operator<<(ostream& out, const PackHead&  packhead);
private:
    uint32_t _MsgNo{0};
    uint8_t  _MsgType{0};
    uint8_t  _MsgVer{0};
    uint16_t _Hlen{0};
    uint32_t _Slen{0};
    uint32_t _Test{0};
    string   _Date;
    uint32_t _SessId{0};
    uint8_t  _ResNo{0};
    uint8_t  _ErrCode{0};
    uint8_t  _DivNo{0};
    uint16_t _Divs{0};
    uint16_t _Div{0};
    uint16_t _Blocks{0};
    string   _Raw;
    string   _Bak; 
};
#endif
