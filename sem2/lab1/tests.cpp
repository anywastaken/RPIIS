#include <gtest/gtest.h>
#include "queue.h"
//cmake -Bbuild 
//cmake --build build
//./build/a.out
TEST(ExampleTest, Test1){
    queue q1;
    q1.push(15);
    q1.push(20);
    EXPECT_EQ(q1.peek(),15);
    EXPECT_EQ(q1.pop(),15);
    EXPECT_EQ(q1.pop(),20);
}

TEST(ExampleTest, Test2){
    queue q1;
    q1.push(10);
    EXPECT_EQ(q1.pop(),10);
    EXPECT_ANY_THROW(q1.pop());
}

TEST(MyTest,Test3){
    queue q1;
    q1.push(10);
    EXPECT_EQ(q1.pop(),10);

}


int main(int argc,char **argv){
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
