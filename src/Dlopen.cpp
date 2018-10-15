#include <stdlib.h>
#include "Dlopen.h"

DLOPEN::DLOPEN(const string dll)
{
    //打开动态链接库
    handle = dlopen(dll.c_str(), RTLD_NOW);
    if (!handle)
    {
        cout << dlerror() << endl;
        //清除之前存在的错误
        exit(EXIT_SUCCESS);
    }
}

DLOPEN::~DLOPEN()
{
    //关闭动态链接库
    dlclose(handle);
}

FUNC DLOPEN::search_func(string func)
{
    //获取一个函数
    FUNC cac_func = NULL;
    cac_func = (FUNC)dlsym(handle, func.c_str());
    if ((error = dlerror()) != NULL)
    {
        cerr << error << endl;
        exit(EXIT_SUCCESS);
    }
    return cac_func;
}
