#include "Solution.h"
#include <gtest/gtest.h>
#include <string>

TEST(SolutionTest, TestAdd) {
    Solution sol;
    testing::internal::CaptureStdout();
    sol.setQueue("One");
    sol.setQueue("Two");
    sol.setQueue("Three");
    sol.Take(2);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Two\n");
}

TEST(SolutionTest, TestOverflow) {
    Solution sol;
    testing::internal::CaptureStdout();
    sol.setQueue("One");
    sol.setQueue("Two");
    sol.setQueue("Three");
    sol.Take(4);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Error\n");
}

TEST(SolutionTest, TestHollowQueue) {
    Solution sol;
    testing::internal::CaptureStdout();
    sol.Take(1);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Error\n");
}
 
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
