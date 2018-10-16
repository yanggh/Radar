#include <cstring>
#include "PackHead.h"

PackHead::PackHead()
{
    _Date.resize(9);
    _Bak.resize(20);
}

size_t PackHead::PackHeadHandle(const char* message, const size_t pos)
{
    size_t   cur = 0;

    memcpy(&_MsgNo, message + pos + cur, 4);
    cur += 4;

    memcpy(&_MsgType, message + pos + cur, 1);
    cur += 1;

    memcpy(&_MsgVer, message + pos + cur, 1);
    cur += 1;

    memcpy(&_Hlen, message + pos + cur, 2);
    cur += 2;

    memcpy(&_Slen, message + pos + cur, 4);
    cur += 4;

    memcpy(&_Test, message + pos + cur, 4);
    cur += 4;

    _Date.assign(message + pos + cur, 9);
    cur += 9;

    memcpy(&_SessId, message + pos + cur, 4);
    cur += 4;

    memcpy(&_ResNo, message + pos + cur, 1);
    cur += 1;

    memcpy(&_ErrCode, message + pos + cur, 1);
    cur += 1;

    memcpy(&_DivNo, message + pos + cur, 1);
    cur += 1;

    memcpy(&_Divs, message + pos + cur, 2);
    cur += 2;

    memcpy(&_Div, message + pos + cur, 2);
    cur += 2;

    memcpy(&_Blocks, message + pos + cur, 2);
    cur += 2;

    _Bak.assign(message + pos + cur, 20);
    cur += 20;

    _Raw.resize(_Hlen);
    _Raw.assign(message, _Hlen);
    return cur + pos;
}

uint32_t PackHead::GetMsgNo() const
{
    return _MsgNo;
}

uint8_t PackHead::GetMsgType() const
{
    return _MsgType;
}

uint8_t  PackHead::GetMsgVer() const
{
    return _MsgVer;
}

uint16_t  PackHead::GetHlen() const
{
    return _Hlen;
}

uint32_t  PackHead::GetSlen() const
{
    return _Slen;
}

uint32_t  PackHead::GetTest() const
{
    return _Test;
}

string  PackHead::GetDate() const
{
    return _Date;
}

uint32_t  PackHead::GetSessId() const
{
    return _SessId;
}

uint8_t  PackHead::GetResNo() const
{
    return _ResNo;
}

uint8_t  PackHead::GetErrCode() const
{
    return _ErrCode;
}

uint8_t  PackHead::GetDivNo() const
{
    return _DivNo;
}

uint16_t  PackHead::GetDivs() const
{
    return _Divs;
}

uint16_t  PackHead::GetDiv() const
{
    return _Div;
}

uint16_t  PackHead::GetBlocks() const
{
    return _Blocks;
}

string  PackHead::GetBak() const
{
    return _Bak;
}

string  PackHead::GetRaw() const
{
    return _Raw;
}

void  PackHead::SetMsgNo(const uint32_t MsgNo)
{
}

void  PackHead::SetMsgType(const uint8_t MsgType)
{
}

void  PackHead::SetMsgVer(const uint8_t MsgVer)
{
}

void  PackHead::SetHlen(const uint16_t Hlen)
{
}

void  PackHead::SetSlen(const uint32_t Slen)
{
    _Raw.replace(8, 4, to_string(Slen));
}

void  PackHead::SetTest(const uint32_t Test)
{
}

void  PackHead::SetDate(const string& Date)
{
}

void  PackHead::SetSessId(const uint32_t SessId)
{
}

void  PackHead::SetResNo(const uint8_t ResNo)
{
    _Raw[29] = ResNo;
}

void  PackHead::SetErrCode(const uint8_t ErrCode)
{
    _Raw[30] = ErrCode; 
}

void  PackHead::SetDivNo(const uint8_t DivNo)
{
    _Raw[31] = DivNo;
}

void  PackHead::SetDivs(const uint16_t Divs)
{
    //memcpy(_Raw+32, &Divs, 2);
    //(uint16_t*)(_Raw + 32) = Divs;
}

void  PackHead::SetDiv(const uint16_t Div)
{
    _Raw.replace(34, 2, to_string(Div));
}

void  PackHead::SetBlocks(const uint16_t Blocks)
{
    _Raw.replace(36, 2, to_string(Blocks));
}

void  PackHead::SetBak(const string& Bak)
{
}

ostream& operator<<(ostream& out, const PackHead&  packhead)
{
    out << "MsgNo:"   << packhead._MsgNo << endl;
    out << "MsgType:" << packhead._MsgType << endl;
    out << "MsgVer:"  << packhead._MsgVer << endl;
    out << "Hlen:"    << packhead._Hlen << endl;
    out << "Slen:"    << packhead._Slen << endl;
    out << "Test:"    << packhead._Test << endl;
    out << "Date:"    << packhead._Date << endl;
    out << "SessId:"  << packhead._SessId << endl;
    out << "ResNo:"   << packhead._ResNo << endl;
    out << "ErrCode:" << packhead._ErrCode << endl;
    out << "DivNo:"   << packhead._DivNo << endl;
    out << "Divs:"    << packhead._Divs << endl;
    out << "Div:"     << packhead._Div << endl;
    out << "Blocks:"  << packhead._Blocks << endl;
    out << "Bak:"     << packhead._Bak << endl;
    out << "Raw:"     << packhead._Raw << endl;
    return out;
}

