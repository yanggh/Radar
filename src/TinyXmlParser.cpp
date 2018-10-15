#include "tinyxml/tinyxml.h"
#include "TinyXmlParser.h"

using namespace std;
/******************Arg Part*******************/
void Arg::SetSort(const int Sort)
{
    _Sort = Sort;
}

void Arg::SetArgLen(const int ArgLen)
{
    _ArgLen = ArgLen;
}

void Arg::SetArgType(const int ArgType)
{
    _ArgType = ArgType;
}

int Arg::GetSort() const
{
    return _Sort;
}

int Arg::GetArgLen() const
{
    return _ArgLen;
}

int Arg::GetArgType() const
{
    return _ArgType;
}

ostream& operator<<(ostream& out, const Arg& arg)
{
    out << "Sort is: " << arg._Sort << endl;
    out << "ArgType is: " << arg._ArgType << endl;
    out << "ArgLen is: " << arg._ArgLen << endl;
}

/******************DLL Part*******************/
void DLL::SetDll(const string& Dll)
{
    _Dll = Dll;
}

void DLL::SetFun(const string& Fun)
{
    _Fun = Fun;
}

void DLL::SetEventCode(const string& EventCode)
{
    _EventCode = EventCode;
}

void DLL::AddArg(const Arg& arg)
{
    _VecArg.push_back(arg);
}

string DLL::GetDll() const
{
    return _Dll;
}

string DLL::GetFun() const
{
    return _Fun;
}

string  DLL::GetEventCode() const
{
    return  _EventCode;
}

DLL& DLL::operator=(const DLL dll)
{
    _EventCode = dll.GetEventCode();
    _Dll = dll.GetDll();
    _Fun = dll.GetFun();

    _VecArg = dll._VecArg;
    return *this;
}

ostream& operator<<(ostream& out, const DLL& dll)
{
    out << "EventCode is : " << dll._EventCode << endl;
    out << "Dll is : " << dll._Dll << endl;
    out << "Fun is : " << dll._Fun << endl;

    for(auto &val : dll._VecArg)
        out << val << endl;

    return out;
}

/******************XmlConf Part*******************/
void XmlConf::SetSegmentsIden(const uint32_t SegmentsIden)
{
    _SegmentsIden = SegmentsIden;
}

void XmlConf::SetValidMessageIden(const uint32_t ValidMessageIden)
{
    _ValidMessageIden = ValidMessageIden;
}

void XmlConf::AddDll(const DLL& dll)
{
    VecFunc.push_back(dll);
}

uint32_t XmlConf::GetSegmentsIden() const
{
    return _SegmentsIden;
}

uint16_t XmlConf::GetValidMessageIden() const
{
    return _ValidMessageIden;
}

void XmlConf::SearchFun(DLL& dll, const string& EventCode)
{
    for(auto val : VecFunc)
    {
        if(EventCode == val.GetEventCode())
        {
            dll = val;
        }
    }
}

ostream& operator<<(ostream& out, const XmlConf& xmlconf)
{
    out << "SegmentsIden is : " << xmlconf._SegmentsIden << endl;
    out << "ValidMessageIden is : " << xmlconf._ValidMessageIden << endl;

    for(auto &val : xmlconf.VecFunc)
        out << val << endl;

    return out;
}

bool LoadXml(const string  xmlfile,   XmlConf& xmlconf)
{
    TiXmlDocument doc;//申明一个文档类型变量，用来存储读取的xml文档
    if (!doc.LoadFile(xmlfile.c_str())) //检测xml文档是否存在
    {
        cerr << doc.ErrorDesc() << endl;
        return false;
    }

    TiXmlElement* root = doc.FirstChildElement();//指向xml文档的根元素
    if (root == NULL)//检测根元素存在性
    {
        cerr << "Failed to load file: No root element." << endl;
        doc.Clear();
        return false;
    }

    //elem指向根的第一个孩子元素
    xmlconf.SetSegmentsIden(stoi(root->FirstChildElement("SegmentsIden")->GetText()));
    xmlconf.SetValidMessageIden(stoi(root->FirstChildElement("ValidMessageIden")->GetText()));
    for (TiXmlElement* elem = root->FirstChildElement("V_RadarComponents"); elem != NULL; elem = elem->NextSiblingElement())
    {
        for (TiXmlElement* radar = elem->FirstChildElement("V_RadarComponent"); radar != NULL; radar = radar->NextSiblingElement())
        {
            for (TiXmlElement* comps = radar->FirstChildElement("ComponentConfigurations"); comps != NULL; comps = comps->NextSiblingElement())
            {
                for (TiXmlElement* vradar = comps->FirstChildElement("V_RadarComponentConfiguration"); vradar != NULL; vradar = vradar->NextSiblingElement())
                {
                    DLL  dll;

                    TiXmlElement* EventCode = vradar->FirstChildElement("EventCode");
                    dll.SetEventCode(EventCode->GetText());

                    for (TiXmlElement* func = vradar->FirstChildElement("FunConfigurationModel"); func != NULL; func = func->NextSiblingElement())
                    {
                        dll.SetDll(func->FirstChildElement("DllName")->GetText());
                        dll.SetFun(func->FirstChildElement("FunName")->GetText());
                        for (TiXmlElement* args = func->FirstChildElement("Args"); args != NULL; args = args->NextSiblingElement())
                        {
                            Arg temp;
                            for (TiXmlElement* arg = args->FirstChildElement("V_FunArg"); arg  != NULL; arg = arg->NextSiblingElement())
                            {
                                temp.SetSort(atoi(arg->FirstChildElement("Sort")->GetText()));
                                temp.SetArgLen(atoi(arg->FirstChildElement("ArgLength")->GetText()));
                                temp.SetArgType(atoi(arg->FirstChildElement("ArgType")->GetText()));
                                dll.AddArg(temp);
                            }
                        }
                    }
                    xmlconf.AddDll(dll);
                }
            }
        }
    }
    return true;
}

