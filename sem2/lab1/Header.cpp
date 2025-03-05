#include "Header.h"

using namespace std;

IntArray::IntArray(const vector<int>& _arr) : arr(_arr) {} //конструктор (инициализирует массив значениями из вектора _arr)

vector<int> IntArray::getArray() const //геттер  (возвращает копию массива)
{
    return arr;
}

void IntArray::setArray(const vector<int>& _arr) //сеттер (заменяет текущий массив новым)
{
    arr = _arr;
}

void IntArray::sort() 
{
    std::sort(arr.begin(), arr.end());
}

void IntArray::insert(int element) 
{
    vector<int>::iterator it = lower_bound(arr.begin(), arr.end(), element);
    arr.insert(it, element);
}

int IntArray::binarySearch(int element) const 
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

    return -1; // если элемент не найден
}

vector<int> IntArray::mergeWith(const IntArray& other) const 
{
    vector<int> result;
    size_t i = 0, j = 0;

    while (i < arr.size() && j < other.arr.size()) 
    {
        if (arr[i] < other.arr[j]) 
        {
            result.push_back(arr[i]);
            ++i;
        }
        else 
        {
            result.push_back(other.arr[j]);
            ++j;
        }
    }

    while (i < arr.size()) 
    {
        result.push_back(arr[i]);
        ++i;
    }
    while (j < other.arr.size()) 
    {
        result.push_back(other.arr[j]);
        ++j;
    }

    return result;
}

vector<int> IntArray::intersectWith(const IntArray& other) const 
{
    vector<int> result;
    size_t i = 0, j = 0;

    while (i < arr.size() && j < other.arr.size()) 
    {
        if (arr[i] < other.arr[j])
            ++i;
        else if (arr[i] > other.arr[j])
            ++j;
        else 
        {
            result.push_back(arr[i]);
            ++i;
            ++j;
        }
    }
    return result;
}
