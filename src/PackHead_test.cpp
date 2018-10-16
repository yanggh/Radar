#include <vector>
#include <cstring>
#include <map>
#include <iostream>

#include "TinyXmlParser.h"
#include "PackHead.h"
#include "DataBlock.h"
#include "Dlopen.h"

char  message[] = "123456\x3a\x0\x16\x03\x0\x0testdatetimersessred\1\0\1\0\1\00001234567890123456789sess456789012345678901\17\0\0\00001234567890123401234567890123456789sess456789012345678901\17\0\0\00001234567890123401234567890123456789sess456789012345678901\17\0\0\00001234567890123401234567890123456789sess456789012345678901\17\0\0\00001234567890123401234567890123456789sess456789012345678901\17\0\0\00001234567890123401234567890123456789sess456789012345678901\17\0\0\00001234567890123401234567890123456789sess456789012345678901\17\0\0\00001234567890123401234567890123456789sess456789012345678901\17\0\0\00001234567890123401234567890123456789sess456789012345678901\17\0\0\00001234567890123401234567890123456789sess456789012345678901\17\0\0\00001234567890123401234567890123456789sess456789012345678901\17\0\0\00001234567890123401234567890123456789sess456789012345678901\17\0\0\00001234567890123401234567890123456789";

const int  MAXNUM = 1024000;
using namespace std;
//分片处理，组包接口
bool  DivsHandle(const uint32_t  sessid, const uint16_t divs, const uint16_t div, const string  payload, string& ss)
{
    static map<uint32_t, vector<string>>  msgs;
    bool  isAll = true;

    //查找回话ID
    auto  it = msgs.find(sessid);
    if(it != msgs.end())
    {
        it->second[div].assign(payload);

        //检查集齐分片数据
        for(auto& val : it->second)
        {
            if(val.length() == 0)
            {
                isAll = false;
                break;
            }
        }
    }
    else
    {
        //插入新加入数据
        vector<string>  msg;
        msg.resize(divs);
        msg[div] = payload;
        msgs.insert(std::pair<uint32_t, vector<string>>(sessid, msg));
        isAll = false;
    }

    if(isAll)
    {
        for(auto& val : it->second)
        {
            ss += val;
        }

        msgs.erase(it);
    }

    return isAll;
}

//获取函数处理结果
string  GetReply(const string&  payload, const DLL& dll)
{
    size_t  offset = 0;
    string  outParameter;

    //检查DLL函数是否存在
    if(!dll.GetDll().empty() && (!dll.GetFun().empty()))
    {
        vector<string>  inParameter;
        inParameter.resize(5);

        for(auto& val : dll._VecArg)
        {
            if(val.GetArgLen() > 0)
            {
                if(val.GetArgType() == 1)
                {
                    inParameter[val.GetSort() - 1].resize(val.GetArgLen());
                    offset += val.GetArgLen();
                }
                else
                {
                    outParameter.resize(val.GetArgLen());
                }
            }
        }

        //检查函数有没有越界,填充输入参数
        if(offset <= payload.length())
        {
            offset = 0;
            for(auto& val : inParameter)
            {
                if(val.length() > 0)
                {
                    val.assign(payload.data() + offset, val.length());
                    offset += val.length();
                }
            }

            DLOPEN dlopen(dll.GetDll());
            FUNC  func = dlopen.search_func(dll.GetFun());

            //func处理
            uint32_t  len = outParameter.length() + 20 + 6;
        }
    }

    return  move(outParameter);
}

int  main(int argc, char** argv)
{
    PackHead   packhead;
    DataBlock  datablock;

    XmlConf          xmlconf;
    LoadXml(argv[1], xmlconf);

    bool        isAll = true;

    while(1)
    {        
        //接收模块部分
        //TODO


        //解析信息头
        packhead.PackHeadHandle(message, 0);
        //检查报文标志
//      if(xmlconf.GetSegmentsIden() == packhead.GetMsgNo())
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
            cout << packhead << endl;
            cout << "去掉信息头，获取有效数据, DataLen = " << payload_len << endl;

            //分片标志,进行分片处理
            if(packhead.GetDivNo() == 1)
            {
                string ss;
                isAll = DivsHandle(packhead.GetSessId(), packhead.GetDivs(), packhead.GetDiv(), payload, ss);
                payload = ss;

                cout << "进行分片处理" << endl;
            }

            if(isAll)
            {
                vector<string>  arrayReplys;
                int             block = 0;//模块个数
                size_t          pos = 0;
                
                //循环函数API处理
                cout << "循环函数API处理" << endl;
                do
                {
                    string  arrayReply;
                    pos = datablock.DataBlockHandle(payload.data(), pos);

                    arrayReply += datablock.GetEventCode();
                    arrayReply += datablock.GetValidIdentity();

                    DLL dll;
                    xmlconf.SearchFun(dll, datablock.GetEventCode());
                    arrayReply += GetReply(datablock.GetData(), dll);

                    arrayReply += datablock.GetBak();
                    arrayReplys.push_back(arrayReply);

                    block++; 
                }while((packhead.GetBlocks() > block) && (payload.length() > pos));

                //组包处理模块
                //mod记录模块数量, replys记录每次模块发送数据
                int    mod = 0;
                string reply;
                vector<std::pair<int, string>> replys;//模块个数与发送数据内容

                pos = 0;
                for(auto&  val : arrayReplys)
                {
                    cout << "----------------" << val<< endl;
                    pos += val.length();
                    if(pos < MAXNUM)
                    {
                        mod += 1;
                        reply += val;
                    }
                    else
                    {
                        replys.push_back(std::pair<int, string>(mod, reply));

                        mod = 1;
                        reply = val;
                        pos = val.length();
                    }
                }
                replys.push_back(std::pair<int, string>(mod, reply));

                //发送处理模块
                //div当前分片数, val.first模块总数, val.second要发送的有效数据
                int  div = 0;
                for(auto& val : replys)
                {
                    //val.firsthead + val.second()
                    cout << "1st = :" << val.first << endl;     //
                    cout << "2nd = : " << val.second << endl;
                    div += 1;
                } 
            }
        }
        cout << "单次循环退出" << endl;
        break;
    }
}
