g++ TinyXmlParser.cpp  TinyXmlParser_test.cpp  tinyxml/*.cpp   -std=c++11 -I ../include -o ../bin/TinyXmlParser_test
g++ -rdynamic Dlopen.cpp TinyXmlParser.cpp  DataBlock.cpp PackHead.cpp  PackHead_test.cpp  tinyxml/*.cpp  -std=c++11 -I../include  -ldl -o ../bin/PackHead_test
g++ DataBlock.cpp DataBlock_test.cpp  -std=c++11 -I../include -o ../bin/DataBlock_test
