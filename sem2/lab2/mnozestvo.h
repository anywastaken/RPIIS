#ifndef mnozestvo_h
#define mnozestvo_h

#include <iostream>
#include <string>

using namespace std;
bool check(int n, int k);
void vvod(int* arr, int size);
void dobavA(int*& arrA, int& sizeA);
void dobavB(int*& arrB, int& sizeB);
void symmetricDifference(int* arrA, int sizeA, int* arrB, int sizeB);
void vyvod(int* arr, int size);
void save(int* arrA, int sizeA, int* arrB, int sizeB, const string& filename);
void load(int*& arrA, int& sizeA, int*& arrB, int& sizeB, const string& filename);
#endif
