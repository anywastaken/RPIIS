#include <gtest/gtest.h>
#include <vector>
#include "Header.h"

using namespace std;
using namespace ArrayUtils;

//сортировка массива
TEST(SortArrayTest, SortsCorrectly) {
    vector<int> arr = { 4, 2, 7, 1, 3 };
    vector<int> expected = { 1, 2, 3, 4, 7 };

    sortArray(arr);

    // Сравниваем весь вектор
    EXPECT_EQ(arr, expected);
}

//вставка элемента
TEST(InsertElementTest, InsertsMaintainingOrder) {
    vector<int> arr = { 1, 3, 5, 7 };
    int newElem = 4;
    vector<int> expected = { 1, 3, 4, 5, 7 };

    insertElement(arr, newElem);

    EXPECT_EQ(arr, expected);
}

//бинарный поиск
TEST(BinarySearchTest, FindsExistingElement) {
    vector<int> arr = { 1, 2, 3, 4, 5 };
    int elemToSearch = 3;

    int index = binarySearch(arr, elemToSearch);

    EXPECT_EQ(index, 2);
}

//бинарный поиск, когда элементанет
TEST(BinarySearchTest, ReturnsNegativeForAbsentElement) {
    vector<int> arr = { 1, 2, 3, 4, 5 };
    int elemToSearch = 10;

    int index = binarySearch(arr, elemToSearch);

    EXPECT_EQ(index, -1);
}

//объединение двух отсортированных массивов
TEST(MergeArraysTest, MergesTwoSortedArrays) {
    vector<int> arr1 = { 1, 3, 5 };
    vector<int> arr2 = { 2, 4, 6 };
    vector<int> expected = { 1, 2, 3, 4, 5, 6 };

    vector<int> merged = mergeArrays(arr1, arr2);

    EXPECT_EQ(merged, expected);
}

//пересечение двух отсортированных массивов
TEST(IntersectArraysTest, FindsCommonElements) {
    vector<int> arr1 = { 1, 3, 5, 7 };
    vector<int> arr2 = { 3, 4, 5, 8 };
    vector<int> expected = { 3, 5 };

    vector<int> intersection = intersectArrays(arr1, arr2);

    EXPECT_EQ(intersection, expected);
}
