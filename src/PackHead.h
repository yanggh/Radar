#ifndef _PackHead_H
#define _PackHead_H

#include <iostream>
#include <cstdint>
using namespace std;
class PackHead
{
public:
    PackHead()
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
   
    size_t PackHeadHandle(const char* message, const size_t pos);

    friend ostream& operator<<(ostream& out, const PackHead&  packhead)
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

private:
    string   MsgNo;
    string   MsgType;
    string   MsgVer;
    string   Hlen;
    string   SLen;
    string   Test;
    string   Date;
    string   SessId;
    string   ResNo;
    string   ErrCode;
    string   DivNo;
    string   Divs;
    string   Div;
    string   Blocks;
    string   Bak; 
};
#endif
