#include <cstring>
#include "PackHead.h"

PackHead::PackHead()
{
    Date.resize(9);
    Bak.resize(20);
}

size_t PackHead::PackHeadHandle(const char* message, const size_t pos)
{
    size_t   cur = 0;

    memcpy(&MsgNo, message + pos + cur, 4);
    cur += 4;

    memcpy(&MsgType, message + pos + cur, 1);
    cur += 1;

    memcpy(&MsgVer, message + pos + cur, 1);
    cur += 1;

    memcpy(&Hlen, message + pos + cur, 2);
    cur += 2;

    memcpy(&Slen, message + pos + cur, 4);
    cur += 4;

    memcpy(&Test, message + pos + cur, 4);
    cur += 4;

    Date.assign(message + pos + cur, 9);
    cur += 9;

    memcpy(&SessId, message + pos + cur, 4);
    cur += 4;

    memcpy(&ResNo, message + pos + cur, 1);
    cur += 1;

    memcpy(&ErrCode, message + pos + cur, 1);
    cur += 1;

    memcpy(&DivNo, message + pos + cur, 1);
    cur += 1;

    memcpy(&Divs, message + pos + cur, 2);
    cur += 2;

    memcpy(&Div, message + pos + cur, 2);
    cur += 2;

    memcpy(&Blocks, message + pos + cur, 2);
    cur += 2;

    Bak.assign(message + pos + cur, 20);
    cur += 20;

    return cur + pos;
}

uint32_t PackHead::GetMsgNo() const
{
    return MsgNo;
}

uint8_t PackHead::GetMsgType() const
{
    return MsgType;
}

uint8_t  PackHead::GetMsgVer() const
{
    return MsgVer;
}

uint16_t  PackHead::GetHlen() const
{
    return Hlen;
}

uint32_t  PackHead::GetSlen() const
{
    return Slen;
}

uint32_t  PackHead::GetTest() const
{
    return Test;
}

string  PackHead::GetDate() const
{
    return Date;
}

uint32_t  PackHead::GetSessId() const
{
    return SessId;
}

uint8_t  PackHead::GetResNo() const
{
    return ResNo;
}

uint8_t  PackHead::GetErrCode() const
{
    return ErrCode;
}

uint8_t  PackHead::GetDivNo() const
{
    return DivNo;
}

uint16_t  PackHead::GetDivs() const
{
    return Divs;
}

uint16_t  PackHead::GetDiv() const
{
    return Div;
}

uint16_t  PackHead::GetBlocks() const
{
    return Blocks;
}

string  PackHead::GetBak() const
{
    return Bak;
}

ostream& operator<<(ostream& out, const PackHead&  packhead)
{
    out << "MsgNo:" << packhead.MsgNo<< endl;
    out << "MsgType:" << packhead.MsgType<< endl;
    out << "MsgVer:" << packhead.MsgVer<< endl;
    out << "Hlen:" << packhead.Hlen << endl;
    out << "Slen:" << packhead.Slen << endl;
    out << "Test:" << packhead.Test<< endl;
    out << "Date:" << packhead.Date<< endl;
    out << "SessId:" << packhead.SessId<< endl;
    out << "ResNo:" << packhead.ResNo<< endl;
    out << "ErrCode:" << packhead.ErrCode<< endl;
    out << "DivNo:" << packhead.DivNo<< endl;
    out << "Divs:" << packhead.Divs<< endl;
    out << "Div:" << packhead.Div<< endl;
    out << "Blocks:" << packhead.Blocks<< endl;
    out << "Bak:" << packhead.Bak<< endl;

    return out;
}

