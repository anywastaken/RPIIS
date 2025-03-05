#pragma once

#include <vector>
#include <algorithm>  // Для функций lower_bound и sort

using namespace std;

class IntArray 
{
public:
    IntArray() = default; // Конструктор по умолчанию. Создаёт пустой массив.
    IntArray(const vector<int>& _arr); // Конструктор, который принимает вектор целых чисел для инициализации массива

    vector<int> getArray() const;
    void setArray(const vector<int>& _arr);
    void sort();
    void insert(int element);
    int binarySearch(int element) const;
    vector<int> mergeWith(const IntArray& other) const;
    vector<int> intersectWith(const IntArray& other) const;

private:
    vector<int> arr;
};
