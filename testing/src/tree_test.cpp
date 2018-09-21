#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "tree.h"

using namespace std;

vector<ConfItem> VecConf;
void ConfInit()
{
    ConfItem item;
    for(int i = 0; i < 2; i++)
    {
        item.radar = to_string(i);
        item.event = to_string(i);
        item.dll = "/home/lsl/std/dlopen/lib/test_so";
        item.func = "add";
        item.dp = NULL;

        VecConf.push_back(item);
        //MapConf.insert(pair<string, ConfItem>(item.radar+item.event, item));
    }
}

class TreeTest: public testing::TestWithParam<ConfItem>
{};

INSTANTIATE_TEST_CASE_P(demo, TreeTest, ::testing::ValuesIn(VecConf.begin(), VecConf.end()));
TEST(Handle, Handle)
{
    Tree tree;
    EXPECT_EQ(4, tree.Handle("11", "asdf")(2,2));
    EXPECT_EQ(1, tree.Handle("11", "asdf")(2,2));
    EXPECT_EQ(0,  tree.Handle("22", "asdf")(1,1));
    EXPECT_EQ(-1,  tree.Handle("22", "asdf")(1,1));
}

TEST_P(TreeTest, DefaultConstructor)
{
    auto  n = GetParam();
    EXPECT_STREQ("add", n.func.c_str()); 
}

int main(int argc, char ** argv)
{
    ConfInit();
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

//map<string, ConfItem> MapConf;
//class TreeMapTest: public testing::TestWithParam<pair<string, ConfItem>>
//{};

//INSTANTIATE_TEST_CASE_P(demo, TreeMapTest, ::testing::ValuesIn(MapConf.begin(), MapConf.end()));

//TEST_P(TreeMapTest, DefaultConstructor)
//{
//    auto  n = GetParam();
//}
