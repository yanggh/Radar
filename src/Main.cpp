#include "HandleApi.h"

char  message[] = "123456\x3a\x0\x16\x03\x0\x0testdatetimersessred\1\0\1\0\100\00001234567890123456789sess456789012345678901\17\0\0\00001234567890123401234567890123456789sess456789012345678901\17\0\0\00001234567890123401234567890123456789sess456789012345678901\17\0\0\00001234567890123401234567890123456789sess456789012345678901\17\0\0\00001234567890123401234567890123456789sess456789012345678901\17\0\0\00001234567890123401234567890123456789sess456789012345678901\17\0\0\00001234567890123401234567890123456789sess456789012345678901\17\0\0\00001234567890123401234567890123456789sess456789012345678901\17\0\0\00001234567890123401234567890123456789sess456789012345678901\17\0\0\00001234567890123401234567890123456789sess456789012345678901\17\0\0\00001234567890123401234567890123456789sess456789012345678901\17\0\0\00001234567890123401234567890123456789sess456789012345678901\17\0\0\00001234567890123401234567890123456789";

using namespace std;

int  main(int argc, char** argv)
{
    PackHead   packhead;

    XmlConf          xmlconf;
    LoadXml(argv[1], xmlconf);
    cout << xmlconf;
    //分片索引完成或者不分片数据标志
    bool        isAll = true;

    while(1)
    {
        //TODO
        //接收模块部分

        //解析信息头
        packhead.PackHeadHandle(message, 0);

        //检查报文标志
        //if(xmlconf.GetSegmentsIden() == packhead.GetMsgNo())
        {
            //请求响应标志，如是响应则过滤
            if(packhead.GetResNo() == 1)
            {
                cout << "响应数据..." << endl;
                continue;
            }

            //去掉信息头，获取有效数据
            string payload;
            int    payload_len = packhead.GetSlen() - packhead.GetHlen();
            payload.resize(payload_len);
            payload.assign(message + packhead.GetHlen(), payload_len);
            //cout << packhead << endl;

            //分片标志,进行分片处理
            if(packhead.GetDivNo() == 1)
            {
                string ss;
                isAll = DivsHandle(packhead.GetSessId(), packhead.GetDivs(), packhead.GetDiv(), payload, ss);
                payload = ss;
            }

            if(isAll)
            {
                vector<string>        arrayReplys;     //数据块处理结果队列
                vector<std::pair<int, string>> replys; //待模块个数与发送数据内容,报文分片队列

                //Api函数处理
                ApiHandle(arrayReplys, packhead.GetBlocks(), payload, xmlconf);

                //组包处理模块
                //replys待发送模块数量与内容
                PackageMods(replys, arrayReplys);

                //TODO
                //发送处理模块
                Sendto(packhead.GetRaw(), replys);
            }
        }
        cout << "单次循环退出" << endl;
        break;
    }
}
