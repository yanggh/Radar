#!/bin/bash

CPP=".cpp"
OUT="_test"
TEST="_test"
JSON=".json"
XML=".xml"

BINPATH="./bin/"
SRCPATH="./src/"
PATHRESULT="./result/"

if [ $# -lt 1 ]
then
    echo "请输入测试项目"
else
for i in $*
do
    echo "-------------${i} start ---------------------------"
    g++ ${SRCPATH}${i}${TEST}${CPP}  ../src/${i}.cpp  -I ../include/ -lgtest -ldl  -lgtest_main -pthread -std=c++11  -o ${BINPATH}${i}${OUT}
    ${BINPATH}${i}${OUT} --gtest_color=yes --gtest_print_time=1  --gtest_output=json:${PATHRESULT}${i}${OUT}${JSON}
    echo "-------------${i} end------------------------------"
    echo "---------------------------------------------------"
done
fi
