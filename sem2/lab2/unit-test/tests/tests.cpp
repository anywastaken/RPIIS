#include <gtest/gtest.h>

#include "SymmetricalDifference.hpp"

TEST(SymmetricalDifferenceTest, Test1)
{
	Set<int> s[3];
	
	s[0].insert(1, 2);
	s[0].insert(2, 1);
	s[0].insert(5, 3);
	s[0].insert(6, 1);
	
	s[1].insert(2, 3);
	s[1].insert(4, 2);
	s[1].insert(5, 2);
	s[1].insert(6, 1);
	s[1].insert(7, 1);
	
	s[2].insert(3, 1);
	s[2].insert(4, 1);
	s[2].insert(7, 1);
	s[2].insert(9, 1);
	s[2].insert(15, 1);
	
	Set<int> expectedResult;
	expectedResult.insert(1, 2);
	expectedResult.insert(2, 2);
	expectedResult.insert(3, 1);
	expectedResult.insert(4, 1);
	expectedResult.insert(5, 1);
	expectedResult.insert(9, 1);
	expectedResult.insert(15, 1);
	
	ASSERT_EQ(symmetricalDifference(s, 3), expectedResult);
}

TEST(SymmetricalDifferenceTest, Test2)
{
	Set<char> s[2];
	
	s[0].insert('a', 1);
	s[0].insert('b', 1);
	s[0].insert('c', 1);
	
	s[1].insert('c', 1);
	s[1].insert('b', 1);
	s[1].insert('a', 1);
	s[1].insert('e', 2);
	
	Set<char> expectedResult;
	expectedResult.insert('e', 2);
	
	ASSERT_EQ(symmetricalDifference(s, 2), expectedResult);
}

TEST(SymmetricalDifferenceTest, Test3)
{
	Set<float> s[4];
	
	Set<float> expectedResult;
	
	ASSERT_EQ(symmetricalDifference(s, 4), expectedResult);
}

TEST(SymmetricalDifferenceTest, Test4)
{
	Set<int> s[1];
	
	s[0].insert(1, 1);
	s[0].insert(2, 1);
	
	Set<int> expectedResult;
	expectedResult.insert(1, 1);
	expectedResult.insert(2, 1);
	
	ASSERT_EQ(symmetricalDifference(s, 1), expectedResult);
}

TEST(SymmetricalDifferenceTest, Test5)
{
	Set<int> s[2];
	
	s[0].insert(1, 2);
	s[0].insert(6, 1);
	s[0].insert(5, 3);
	s[0].insert(2, 1);
	
	s[1].insert(2, 3);
	s[1].insert(5, 2);
	s[1].insert(4, 2);
	s[1].insert(7, 1);
	s[1].insert(6, 1);
	
	Set<int> expectedResult;
	expectedResult.insert(2, 2);
	expectedResult.insert(4, 2);
	expectedResult.insert(1, 2);
	expectedResult.insert(7, 1);
	expectedResult.insert(5, 1);
}

int main(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

/*
    [==========] Running 5 tests from 1 test suite.
    [----------] Global test environment set-up.
    [----------] 5 tests from SymmetricalDifferenceTest
    [ RUN      ] SymmetricalDifferenceTest.Test1
    [       OK ] SymmetricalDifferenceTest.Test1 (0 ms)
    [ RUN      ] SymmetricalDifferenceTest.Test2
    [       OK ] SymmetricalDifferenceTest.Test2 (0 ms)
    [ RUN      ] SymmetricalDifferenceTest.Test3
    [       OK ] SymmetricalDifferenceTest.Test3 (0 ms)
    [ RUN      ] SymmetricalDifferenceTest.Test4
    [       OK ] SymmetricalDifferenceTest.Test4 (0 ms)
    [ RUN      ] SymmetricalDifferenceTest.Test5
    [       OK ] SymmetricalDifferenceTest.Test5 (0 ms)
    [----------] 5 tests from SymmetricalDifferenceTest (0 ms total)

    [----------] Global test environment tear-down
    [==========] 5 tests from 1 test suite ran. (0 ms total)
    [  PASSED  ] 5 tests.
 */