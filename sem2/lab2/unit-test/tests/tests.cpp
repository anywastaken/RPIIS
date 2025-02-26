#include <gtest/gtest.h>

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

TEST(SymmetricalDifferenceTest, Test6)
{
	Set< Set<int> > s[1];
	
	Set<int> ss;
	ss.insert(1, 1);
	ss.insert(2, 1);
	
	s[0].insert(ss, 1);
	
	Set< Set<int> > expectedResult;
	
	Set<int> ssExpected;
	ssExpected.insert(1, 1);
	ssExpected.insert(2, 1);
	
	expectedResult.insert(ssExpected, 1);
	
	ASSERT_EQ(symmetricalDifference(s, 1), expectedResult);
}

TEST(SymmetricalDifferenceTest, Test7)
{
	Set<int> s[2];
	
	Set<int> ss;
	ss.insert(1, 1);
	ss.insert(2, 1);
	
	s[0].insert(1, 1);
	s[0].insert(ss, 1);
	
	s[1].insert(ss, 1);
	s[1].insert(1, 1);
	
	Set<int> expectedResult;
	
	ASSERT_EQ(symmetricalDifference(s, 2), expectedResult);
}

TEST(SymmetricalDifferenceTest, Test8)
{
	Set<int> s[2];
	
	Set<int> ss;
	ss.insert(1, 1);
	
	s[0].insert(ss, 1);
	
	s[1].insert(1, 1);
	
	Set<int> expectedResult;
	expectedResult.insert(ss, 1);
	expectedResult.insert(1, 1);
	
	ASSERT_EQ(symmetricalDifference(s, 2), expectedResult);
}

TEST(SymmetricalDifferenceTest, Test9)
{
	Set<int> s[2];
	s[0].insert(1, 1);
	s[0].insert(s[0], 1);
	s[0].insert(s[0], 1);
	
	s[1].insert(1, 1);
	
	Set<int> expectedResult;
	
	Set<int> s1;
	s1.insert(1, 1);
	
	Set<int> ss1;
	ss1.insert(1, 1);
	ss1.insert(s1, 1);
	
	expectedResult.insert(s1, 1);
	expectedResult.insert(ss1, 1);
	
	ASSERT_EQ(symmetricalDifference(s, 2), expectedResult);
}

int main(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}