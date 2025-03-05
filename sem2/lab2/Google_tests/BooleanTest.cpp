#include "gtest/gtest.h"
#include "Set_lib/Set.hpp"
#include <iostream>
#include <vector>

TEST(BooleanTest, StandardTest){
    Set testSet("A = {a,b,c}");
    std::vector< Set> boolean;
    boolean = testSet.getBoolean();
    EXPECT_NO_FATAL_FAILURE(boolean[0].getBoolean());
}

TEST(BooleanTest, ErrorHandling){
    Set testSet("A = {{}");
    std::vector< Set> boolean;
    boolean = testSet.getBoolean();
    EXPECT_NO_FATAL_FAILURE(boolean[0].getBoolean());
}