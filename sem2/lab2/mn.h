#ifndef mn_h
#define mn_h

#include <iostream>
#include <string>

using namespace std;
void createMN(string**& mn, int*& sizes, int& nummn);
void dobavMn(string*& mn, int& size, char Name);
void vvod(string* mn, int size);
bool povtor(string* mn, int size, const string& elem);
string checkGroupElements(const string& elem);
void printMN(string** mn, int* sizes, int nummn);
void symmetricDifference(string** mn, int* sizes, int nummn);
void save(string**& mn, int*& sizes, int& nummn, const string& filename);
void load(string**& mn, int*& sizes, int& nummn, const string& filename);
#endif

