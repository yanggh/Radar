g++  -fPIC  -shared  ../lib/test_so.cpp -std=c++11  -Wall -o  ../lib/test_so
g++ ../src/tree.cpp  -I../include -std=c++11 -ldl -Wall -c
