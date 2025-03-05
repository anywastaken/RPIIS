#pragma once

#include <vector>

using namespace std;

namespace ArrayUtils 
{

    void sortArray(vector<int>& arr);

    void insertElement(vector<int>& arr, int element);

    int binarySearch(const vector<int>& arr, int element);

    vector<int> mergeArrays(const vector<int>& arr1, const vector<int>& arr2);

    vector<int> intersectArrays(const vector<int>& arr1, const vector<int>& arr2);
}
