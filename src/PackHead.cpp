#include "PackHead.h"

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

