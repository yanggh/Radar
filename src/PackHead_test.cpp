#include "PackHead.h"

int main(int argc, char** argv)
{
    PackHead  packhead;
    
    char  message[] = "1234567890123456789012\17\0\0\0a234567890123456789012345678901234567890";
    size_t  pos = packhead.PackHeadHandle(message, 0);
    cout << "pos = " << pos << endl;
    
    cout << packhead << endl;
}
