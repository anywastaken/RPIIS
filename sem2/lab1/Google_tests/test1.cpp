#include <gtest/gtest.h>
#include "../stack.h"


TEST(StackTest, CreateAndDeleteStack) {
    stack* s = allocate_stack();
    ASSERT_NE(s, nullptr);
    del_stack(s);
}

TEST(StackTest, PushAndPop) {
    stack* s = allocate_stack();
    push(10, s);
    push(20, s);
    EXPECT_EQ(pop(s), 20);
    EXPECT_EQ(pop(s), 10);
    del_stack(s);
}


TEST(StackTest, IsEmpty) {
    stack* s = allocate_stack();
    EXPECT_TRUE(isempty(s));
    push(30, s);
    EXPECT_FALSE(isempty(s));
    pop(s);
    EXPECT_TRUE(isempty(s));
    del_stack(s);
}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}