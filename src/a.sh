g++ TinyXmlParser.cpp  TinyXmlParser_test.cpp  tinyxml/*.cpp   -std=c++11 -I ../include -o ../bin/TinyXmlParser_test
g++ -rdynamic Dlopen.cpp TinyXmlParser.cpp  DataBlock.cpp PackHead.cpp  Main.cpp HandleApi.cpp tinyxml/*.cpp  -std=c++11 -I../include  -ldl -o ../bin/Main
g++ -fPIC -shared test_so_file.cpp -o libcalc.so
g++ DataBlock.cpp DataBlock_test.cpp  -std=c++11 -I../include -o ../bin/DataBlock_test
