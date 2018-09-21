#include "PackHead.h"

PackHead::PackHead()
{
    MsgNo.resize(4);;
    MsgType.resize(1);
    MsgVer.resize(1);
    Hlen.resize(2);
    SLen.resize(4);
    Test.resize(4);
    Date.resize(9);
    SessId.resize(4);
    ResNo.resize(1);
    ErrCode.resize(1);
    DivNo.resize(1);
    Divs.resize(2);
    Div.resize(2);
    Blocks.resize(2);
    Bak.resize(20);
}

size_t PackHead::PackHeadHandle(const char* message, const size_t pos)
{
    size_t   cur = 0;
    uint32_t data_len = 0;

    MsgNo.assign(message + pos + cur, 4);
    cur += 4;

    MsgType.assign(message + pos + cur, 1);
    cur += 1;

    MsgVer.assign(message + pos + cur, 1);
    cur += 1;

    Hlen.assign(message + pos + cur, 2);
    cur += 2;

    SLen.assign(message + pos + cur, 4);
    cur += 4;

    Test.assign(message + pos + cur, 4);
    cur += 4;

    Date.assign(message + pos + cur, 9);
    cur += 9;

    SessId.assign(message + pos + cur, 4);
    cur += 4;

    ResNo.assign(message + pos + cur, 1);
    cur += 1;

    ErrCode.assign(message + pos + cur, 1);
    cur += 1;

    DivNo.assign(message + pos + cur, 1);
    cur += 1;

    Divs.assign(message + pos + cur, 2);
    cur += 2;

    Div.assign(message + pos + cur, 2);
    cur += 2;

    Blocks.assign(message + pos + cur, 2);
    cur += 2;

    Bak.assign(message + pos + cur, 20);
    cur += 20;

    return cur;
}

ostream& operator<<(ostream& out, const PackHead&  packhead)
{
    out << "MsgNo:" << packhead.MsgNo<< endl;
    out << "MsgType:" << packhead.MsgType<< endl;
    out << "MsgVer:" << packhead.MsgVer<< endl;
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


