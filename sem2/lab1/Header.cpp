#include "Header.h"   
#include <algorithm> 
#include <vector>

using namespace std;

namespace ArrayUtils 
{
    void sortArray(vector<int>& arr) 
    {
        sort(arr.begin(), arr.end());
    }

    void insertElement(vector<int>& arr, int element) 
    {
        vector<int>::iterator it = lower_bound(arr.begin(), arr.end(), element);
        arr.insert(it, element);
    }

    
    int binarySearch(const vector<int>& arr, int element) 
    {
        int left = 0;
        int right = static_cast<int>(arr.size()) - 1;

        while (left <= right) 
        {
            int mid = left + (right - left) / 2;

            if (arr[mid] == element)
                return mid;
            else if (arr[mid] < element)
                left = mid + 1;
            else
                right = mid - 1;
        }

        return -1; //если нет
    }

    vector<int> mergeArrays(const vector<int>& arr1, const vector<int>& arr2) 
    {
        vector<int> result;  

        size_t i = 0, j = 0;

        while (i < arr1.size() && j < arr2.size()) 
        {
            if (arr1[i] < arr2[j]) 
            {
                result.push_back(arr1[i]);
                ++i;
            }
            else {
                result.push_back(arr2[j]);
                ++j;
            }
        }
        
        //если один закончился 
        while (i < arr1.size()) 
        {
            result.push_back(arr1[i]);
            ++i;
        }
        while (j < arr2.size()) {
            result.push_back(arr2[j]);
            ++j;
        }

        return result;
    }

    vector<int> intersectArrays(const vector<int>& arr1, const vector<int>& arr2) 
    {
        vector<int> result;  
        size_t i = 0, j = 0; 

        while (i < arr1.size() && j < arr2.size())
        {
            if (arr1[i] < arr2[j])
                ++i;
            else if (arr1[i] > arr2[j])
                ++j;
            else
            {
                result.push_back(arr1[i]);
                ++i;
                ++j;
            }
        }
        return result;
    }
}
