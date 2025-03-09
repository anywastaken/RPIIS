#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <utility>

using namespace std;

struct HashTable {
    vector<list<pair<string, string>>> table;
    int tableSize;
};

void initHashTable(HashTable& ht, int size);
int hashFunction(const string& key, int tableSize);
void insert(HashTable& ht, const string& key, const string& value);
bool search(const HashTable& ht, const string& key, string& value);
void remove(HashTable& ht, const string& key);
void display(const HashTable& ht);
