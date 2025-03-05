#include "gtest/gtest.h"
#include "Set_lib/Set.hpp"
#include <iostream>

TEST(CorrectEntryTest, AllowedSymbols){
    std::string str = "{a,%,b}";
    EXPECT_FALSE(Set::isCorrect(str));
    str = "{a, b, c}";
    EXPECT_FALSE(Set::isCorrect(str));

    std::string str1 = "{a,b,c,4e}";
    EXPECT_TRUE(Set::isCorrect(str1 ));
}

TEST(CorrectEntryTest, IncorrectComma){
    std::string str = "{,a,b}";
    EXPECT_FALSE(Set::isCorrect(str));
    str = "{a,b,}";
    EXPECT_FALSE(Set::isCorrect(str));
    str = "<,a,b>";
    EXPECT_FALSE(Set::isCorrect(str));
    str = "<a,b,>";
    EXPECT_FALSE(Set::isCorrect(str));
    str = "{<a,b>,{c,e},}";
    EXPECT_FALSE(Set::isCorrect(str));
}

TEST(CorrectEntryTest, CorrectBrackets){
    std::string str = "{}";
    EXPECT_TRUE(Set::isCorrectBrackets(str));
    str = "{a,b,{c,d,e},{f,4}}";
    EXPECT_TRUE(Set::isCorrectBrackets(str));
    str = "{a,b,<c,d,e>,{f,4}}";
    EXPECT_TRUE(Set::isCorrectBrackets(str));
    str = "<>";
    EXPECT_TRUE(Set::isCorrectBrackets(str));
    str = "{a,<{<b,c,d>,<o,8,i>},{}>}";
    EXPECT_TRUE(Set::isCorrectBrackets(str));

    str = "{";
    EXPECT_FALSE(Set::isCorrectBrackets(str));
    str = "}";
    EXPECT_FALSE(Set::isCorrectBrackets(str));
    str = "{{}";
    EXPECT_FALSE(Set::isCorrectBrackets(str));
    str = "{}}";
    EXPECT_FALSE(Set::isCorrectBrackets(str));
    str = "<a,b,c}";
    EXPECT_FALSE(Set::isCorrectBrackets(str));
    str = "{{a,<b}>}";
    EXPECT_FALSE(Set::isCorrectBrackets(str));
    str = "a,b,c";
    EXPECT_FALSE(Set::isCorrectBrackets(str));
}
