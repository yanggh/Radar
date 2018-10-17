#ifndef HANDLE_API_H
#define HANDLE_API_H
#include <vector>
#include <cstring>
#include <map>
#include <iostream>
#include "TinyXmlParser.h"
#include "PackHead.h"
#include "DataBlock.h"
#include "Dlopen.h"

//分片处理
bool  DivsHandle(const uint32_t  sessid, const uint16_t divs, const uint16_t div, const string  payload, string& ss);

//获取函数处理结果
string  GetReply(const string&  payload, const DLL& dll);

//DLL函数调用处理
void  ApiHandle(vector<string>& arrayReplys, const int blocks, const string& payload, XmlConf& xmlconf);

//组包处理模块
//mod记录模块数量, replys记录每次模块发送数据
void  PackageMods(vector<std::pair<int, string>>& replys, vector<string>&  arrayReplys);

//发送模块
//mod记录模块数量, reply记录每次模块发送数据
void Sendto(const string&  head, vector<std::pair<int, string>>& replys);
#endif
