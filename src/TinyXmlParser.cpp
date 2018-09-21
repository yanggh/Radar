#include "tinyxml/tinyxml.h"
#include "TinyXmlParser.h"

using namespace std;

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
    xmlconf.SetSegmentsIden(root->FirstChildElement("SegmentsIden")->GetText());
    xmlconf.SetValidMessageIden(root->FirstChildElement("ValidMessageIden")->GetText());
    for (TiXmlElement* elem = root->FirstChildElement("V_RadarComponents"); elem != NULL; elem = elem->NextSiblingElement())
    {
        for (TiXmlElement* radar = elem->FirstChildElement("V_RadarComponent"); radar != NULL; radar = radar->NextSiblingElement())
        {
//            cout << "ComponentId: " << radar->FirstChildElement("ComponentId")->GetText() << endl;
//            cout << "ComponentNo: " << radar->FirstChildElement("ComponentNo")->GetText() << endl;
//            cout << "ParentComponentId: " << radar->FirstChildElement("ParentComponentId")->GetText() << endl;
            for (TiXmlElement* comps = radar->FirstChildElement("ComponentConfigurations"); comps != NULL; comps = comps->NextSiblingElement())
            {
                for (TiXmlElement* vradar = comps->FirstChildElement("V_RadarComponentConfiguration"); vradar != NULL; vradar = vradar->NextSiblingElement())
                {
//                    cout << "RadarComponent_Fun_Id: " << vradar->FirstChildElement("RadarComponent_Fun_Id")->GetText() << endl;
//                    cout << "RadarId: " << vradar->FirstChildElement("RadarId")->GetText() << endl;
//                    cout << "RadarComponentId: " << vradar->FirstChildElement("RadarComponentId")->GetText() << endl;
//                    cout << "FunConfigurationName: " << vradar->FirstChildElement("FunConfigurationName")->GetText() << endl;
                    DLL  dll; 
                    for (TiXmlElement* func = vradar->FirstChildElement("FunConfigurationModel"); func != NULL; func = func->NextSiblingElement())
                    {
                        dll.SetDll(func->FirstChildElement("DllName")->GetText());
                        dll.SetFun(func->FirstChildElement("FunName")->GetText());
                        for (TiXmlElement* args = func->FirstChildElement("Args"); args != NULL; args = args->NextSiblingElement())
                        {
                            Arg temp;
                            for (TiXmlElement* arg = args->FirstChildElement("V_FunArg"); arg  != NULL; arg = arg->NextSiblingElement())
                            {
                                temp.SetSort(arg->FirstChildElement("Sort")->GetText());
                                temp.SetArgLen(arg->FirstChildElement("ArgLength")->GetText());
                                temp.SetArgType(arg->FirstChildElement("ArgType")->GetText());
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


