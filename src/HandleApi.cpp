//分片处理，组包接口
#include "HandleApi.h"

const int  MAXNUM = 1024000;

//分片处理
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
 
            int outlen = 0; 
            func(&outlen, (void*)outParameter.data(), inParameter[0].length(), (void*)inParameter[0].data(), inParameter[1].length(), (void*)inParameter[1].data(), inParameter[2].length(), (void*)inParameter[2].data(), inParameter[3].length(), (void*)inParameter[3].data(), inParameter[4].length(), (void*)inParameter[4].data());

            cout << "func handle after: " << outlen << endl;
            //func处理
            uint32_t  len = outParameter.length() + 20 + 6;
        }
    }

    return  move(outParameter);
}

//DLL函数调用处理
void  ApiHandle(vector<string>& arrayReplys, const int blocks, const string& payload, XmlConf& xmlconf)
{
    int             block = 0;//模块个数
    size_t          pos = 0;
    
    DataBlock  datablock;
    
    //循环函数API处理,结束条件是数据块个数用完或者payload有效数据使用完
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
    }while((blocks > block) && (payload.length() > pos));
}

//组包处理模块
//mod记录模块数量, reply记录每次模块发送数据
void  PackageMods(vector<std::pair<int, string>>& replys, vector<string>&  arrayReplys)
{
    int  mod = 0;
    int  pos = 0;
    string reply;
    for(auto&  val : arrayReplys)
    {
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
}

//发送处理模块
//div当前分片数, val.first模块总数, val.second要发送的有效数据
//TODO
void Sendto(vector<std::pair<int, string>>& replys)
{
    int  div = 0;
    for(auto& val : replys)
    {
        //val.firsthead + val.second()
        cout << "divs: " << replys.size() << endl;
        cout << "div: " << div << endl;
        cout << "mods:" << val.first << endl;
        cout << "data: " << val.second << endl;
        div += 1;
    } 
}


