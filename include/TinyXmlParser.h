#ifndef  TinyXmlParser_H
#define  TinyXmlParser_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;
class Arg{
private:
    string  _Sort;
    string  _ArgLen;
    string  _ArgType;
public:
    void SetSort(const string& Sort)
    {
        _Sort = Sort;
    }
    void SetArgLen(const string& ArgLen)
    {
        _ArgLen = ArgLen;
    }
    void SetArgType(const string& ArgType)
    {
        _ArgType = ArgType;          
    }
    
    string GetSort()
    {
        return _Sort;
    } 

    string GetArgLen()
    {
        return _ArgLen;
    } 

    string GetArgType()
    {
        return _ArgType;
    }

    friend ostream& operator<<(ostream& out, const Arg& arg)
    {
        out << "Sort is: " << arg._Sort << endl; 
        out << "ArgLen is: " << arg._ArgLen << endl; 
        out << "ArgType is: " << arg._ArgType << endl; 
    }
};

class  DLL{
private:
    string  _Dll;
    string  _Fun;
    vector<Arg> _VecArg;
public:
    void SetDll(const string& Dll)
    {
        _Dll = Dll;
    }

    void SetFun(const string& Fun)
    {
        _Fun = Fun;
    }

    void AddArg(const Arg& arg)
    {
        _VecArg.push_back(arg);
    }

    string GetDll()
    {
        return _Dll;
    }

    string GetFun()
    {
        return _Fun;
    }
    
    friend ostream& operator<<(ostream& out, const DLL& dll)
    {
        out << "Dll is : " << dll._Dll << endl;
        out << "Fun is : " << dll._Fun << endl;

        for(auto &val : dll._VecArg)
            out << val << endl;

        return out;
    }
};

class XmlConf
{
private:
    string _SegmentsIden;
    string _ValidMessageIden;
    vector<DLL> VecFunc;
public:
    void SetSegmentsIden(const string& SegmentsIden)
    {
        _SegmentsIden = SegmentsIden;
    }
    
    void SetValidMessageIden(const string& ValidMessageIden)
    {
        _ValidMessageIden = ValidMessageIden;
    }

    void AddDll(const DLL& dll)
    {
        VecFunc.push_back(dll);
    }

    string GetValidMessageIden()
    {
        return _ValidMessageIden;
    }

    string GetSegmentsIden()
    {
        return _SegmentsIden;
    }

    friend ostream& operator<<(ostream& out, const XmlConf& xmlconf)
    {
        out << "SegmentsIden is : " << xmlconf._SegmentsIden << endl;
        out << "ValidMessageIden is : " << xmlconf._ValidMessageIden << endl;

        for(auto &val : xmlconf.VecFunc)
            out << val << endl;

        return out;
    }
};

bool LoadXml(const string  xmlfile,   XmlConf& xmlconf);
#endif
