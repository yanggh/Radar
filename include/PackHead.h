#ifndef _PackHead_H
#define _PackHead_H

#include <iostream>
#include <cstdint>
using namespace std;
class PackHead
{
public:
    PackHead();
    size_t PackHeadHandle(const char* message, const size_t pos);
string  GetMsgNo();
string  GetMsgType();
string  GetMsgVer();
string  GetHlen();
string  GetSlen();
string  GetTest();
string  GetDate();
string  GetSessId();
string  GetResNo();
string  GetErrCode();
string  GetDivNo();
string  GetDivs();
string  GetDiv();
string  GetBlocks();
string  GetBak();

    friend ostream& operator<<(ostream& out, const PackHead&  packhead);
private:
    string   MsgNo;
    string   MsgType;
    string   MsgVer;
    string   Hlen;
    string   Slen;
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
