#include <gtest/gtest.h>
#include <vector>
#include "Header.h"

using namespace std;

TEST(IntArrayClassTest, ClassSortWorksCorrectly) 
{
    IntArray arr({ 4, 2, 7, 1, 3 });
    arr.sort();
    vector<int> expected = { 1, 2, 3, 4, 7 };
    EXPECT_EQ(arr.getArray(), expected);
}

TEST(IntArrayClassTest, ClassInsertWorksCorrectly) {
    IntArray arr({ 1, 3, 5, 7 });
    arr.insert(4);
    vector<int> expected = { 1, 3, 4, 5, 7 };
    EXPECT_EQ(arr.getArray(), expected);
}

TEST(IntArrayClassTest, ClassBinarySearchWorksCorrectly) {
    IntArray arr({ 1, 2, 3, 4, 5 });
    int index = arr.binarySearch(3);
    EXPECT_EQ(index, 2);
}

TEST(IntArrayClassTest, ClassMergeWorksCorrectly) {
    IntArray arr1({ 1, 3, 5 });
    IntArray arr2({ 2, 4, 6 });
    vector<int> merged = arr1.mergeWith(arr2);
    vector<int> expected = { 1, 2, 3, 4, 5, 6 };
    EXPECT_EQ(merged, expected);
}

TEST(IntArrayClassTest, ClassIntersectWorksCorrectly) {
    IntArray arr1({ 1, 3, 5, 7 });
    IntArray arr2({ 3, 4, 5, 8 });
    vector<int> intersection = arr1.intersectWith(arr2);
    vector<int> expected = { 3, 5 };
    EXPECT_EQ(intersection, expected);
}
