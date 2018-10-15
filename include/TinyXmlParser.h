#ifndef  TinyXmlParser_H
#define  TinyXmlParser_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;
class Arg{
private:
    int  _Sort;
    int  _ArgLen;
    int  _ArgType;
public:
    void SetSort(const int Sort);
    void SetArgLen(const int ArgLen);
    void SetArgType(const int ArgType);

    int  GetSort() const;
    int  GetArgLen() const;
    int  GetArgType() const;
    friend ostream& operator<<(ostream& out, const Arg& arg);
};

class  DLL{
private:
    string  _EventCode;
    string  _Dll;
    string  _Fun;
public:
    vector<Arg> _VecArg;
    void AddArg(const Arg& arg);

    void SetDll(const string& Dll);
    void SetFun(const string& Fun);
    void SetEventCode(const string& EventCode);

    string GetDll() const;
    string GetFun() const;
    string GetEventCode() const;

    DLL& operator=(const DLL dll);
    friend ostream& operator<<(ostream& out, const DLL& dll);
};

class XmlConf
{
private:
    uint32_t _SegmentsIden;
    uint16_t _ValidMessageIden;
public:
    vector<DLL> VecFunc;
    void AddDll(const DLL& dll);

    void SetSegmentsIden(const uint32_t SegmentsIden);
    void SetValidMessageIden(const uint32_t ValidMessageIden);

    uint32_t GetSegmentsIden() const;
    uint16_t GetValidMessageIden() const;

    void SearchFun(DLL& dll, const string& EventCode);

    friend ostream& operator<<(ostream& out, const XmlConf& xmlconf);
};

bool LoadXml(const string  xmlfile,   XmlConf& xmlconf);
#endif
