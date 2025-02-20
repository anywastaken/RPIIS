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
	Set<int> s[2];
	
	s[0].insert(1, 1);
	s[0].insert(2, 1);
	s[0].insert(3, 1);
	
	s[1].insert(3, 1);
	s[1].insert(2, 1);
	s[1].insert(1, 1);
	s[1].insert(5, 2);
	
	Set<int> expectedResult;
	expectedResult.insert(5, 2);
	
	ASSERT_EQ(symmetricalDifference(s, 2), expectedResult);
}

TEST(SymmetricalDifferenceTest, Test3)
{
	Set<int> s[4];
	
	Set<int> expectedResult;
	
	ASSERT_EQ(symmetricalDifference(s, 4), expectedResult);
}

int main(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

/*

    [==========] Running 3 tests from 1 test suite.
    [----------] Global test environment set-up.
    [----------] 3 tests from SymmetricalDifferenceTest
    [ RUN      ] SymmetricalDifferenceTest.Test1
    [       OK ] SymmetricalDifferenceTest.Test1 (0 ms)
    [ RUN      ] SymmetricalDifferenceTest.Test2
    [       OK ] SymmetricalDifferenceTest.Test2 (0 ms)
    [ RUN      ] SymmetricalDifferenceTest.Test3
    [       OK ] SymmetricalDifferenceTest.Test3 (0 ms)
    [----------] 3 tests from SymmetricalDifferenceTest (0 ms total)

    [----------] Global test environment tear-down
    [==========] 3 tests from 1 test suite ran. (0 ms total)
    [  PASSED  ] 3 tests.

 */