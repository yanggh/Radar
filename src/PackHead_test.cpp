#include <vector>
#include <cstring>
#include <map>
#include "TinyXmlParser.h"
#include "PackHead.h"
#include "DataBlock.h"
#include "Dlopen.h"

char  message[] = "123456\072\0\x07\x03\0\000testdatetimersessrednonono01234567890123456789sess456789012345678901\17\0\0\00001234567890123401234567890123456789sess456789012345678901\17\0\0\00001234567890123401234567890123456789sess456789012345678901\17\0\0\00001234567890123401234567890123456789sess456789012345678901\17\0\0\00001234567890123401234567890123456789sess456789012345678901\17\0\0\00001234567890123401234567890123456789sess456789012345678901\17\0\0\00001234567890123401234567890123456789sess456789012345678901\17\0\0\00001234567890123401234567890123456789sess456789012345678901\17\0\0\00001234567890123401234567890123456789sess456789012345678901\17\0\0\00001234567890123401234567890123456789sess456789012345678901\17\0\0\00001234567890123401234567890123456789sess456789012345678901\17\0\0\00001234567890123401234567890123456789sess456789012345678901\17\0\0\00001234567890123401234567890123456789";

const int  MAXNUM = 1024000;
bool  DivsHandle(const uint32_t  sessid, const uint16_t divs, const uint16_t div, const string  payload, string& ss)
{
    static map<uint32_t, vector<string>>  msgs;
    bool  isAll = true;

    auto  it = msgs.find(sessid);
    if(it != msgs.end())
    {
        it->second[div].assign(payload);

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

string  GetReply(const string&  payload, const DLL& dll)
{
    size_t  offset = 0;
    string  outParameter;

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

            //func...................
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

    string      replyhead;
    while(1)
    {
        packhead.PackHeadHandle(message, 0);

        if(xmlconf.GetSegmentsIden() == packhead.GetMsgNo())
        {
            if(packhead.GetResNo() == 1)
            {
                continue;
            }

            //分片处理
            string payload;
            int    payload_len = packhead.GetSlen() - packhead.GetHlen();
            payload.resize(payload_len);
            payload.assign(message + packhead.GetHlen(), payload_len);

            if(packhead.GetDivNo() == 1)
            {
                string ss;
                isAll = DivsHandle(packhead.GetSessId(), packhead.GetDivs(), packhead.GetDiv(), payload, ss);
                payload = ss;
            }

            if(isAll)
            {
                //函数API处理
                vector<string>  arrayReplys;
                size_t          pos = 0;
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

                }while(payload.length() > pos);

                
                //组包处理
                pos = 0;
                for(auto&  val : arrayReplys)
                {
                    pos += val.length();
                    if(pos > MAXNUM)
                        reply += val;
                }
            }
        }
    }
}
