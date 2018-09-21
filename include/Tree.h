#ifndef __Tree_H
#define __Tree_H
#include <vector>
#include <string>
using namespace std;


typedef int (*FUNC)(int* out1_len, void* out1, int in1_len, void* in1, int in2_len, void* in2, int in3_len, void* in3, int in4_len, void* in4, int in5_len, void* in5);
class ConfItem{
public:
    string  radar;
    string  event;
    string  dll;
    string  func;
    void*   dp{NULL};

    ConfItem& operator=(const ConfItem& conf)
    {
        radar = conf.radar;
        event == conf.event;
        dll=conf.dll;
        func=conf.func;
        dp=conf.dp;
        return *this;
    }

    bool operator==(const ConfItem& conf)
    {
        return ((radar+event) == conf.radar);
    }
};

class Tree{
public:
    Tree();
    ~Tree();

    FUNC Handle(string key, string target);

private:
    vector<ConfItem> Conf;
    void AddTree(ConfItem item);
};

#endif
