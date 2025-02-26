#ifndef mn_h
#define mn_h

#include <iostream>
#include <string>

using namespace std;
void vvod(int* arr, int size);
bool check(int input, int max);
void dobavM(int*& arr, int& size, char setName);
void createSets(int**& sets, int*& sizes, int& numSets);
int* symDifference(int** sets, int* sizes, int numSets, int& resultSize);
void vyvod(int** sets, int* sizes, int numSets);
void save(int** sets, int* sizes, int numSets, const string& filename);
void load(int**& sets, int*& sizes, int& numSets, const string& filename);
#endif
