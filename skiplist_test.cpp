#include <gtest/gtest.h>
#include"skiplist.h"

TEST(SkipListTest, Insert)
{
    SkipList* skipList = new SkipList();
    skipList->insert("xiaozhang", "28");
    skipList->insert("zhangsan", "26");
    skipList->insert("wanger", "76");
    EXPECT_EQ(skipList->search("wanger"),"76");
    EXPECT_EQ(skipList->search("xiaozhang"),"28");
    EXPECT_EQ(skipList->search("zhangsan"),"26");
    delete skipList;
}


int main(int argc, char** argv) { 
    testing::InitGoogleTest(&argc, argv); 

   // Runs all tests using Google Test. 
    return RUN_ALL_TESTS(); 
}