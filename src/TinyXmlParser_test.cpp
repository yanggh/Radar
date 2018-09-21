#include "TinyXmlParser.h"

int  main(int argc, char** argv)
{
    XmlConf  xmlconf;

    LoadXml(argv[1],   xmlconf);
    cout << xmlconf;
}
