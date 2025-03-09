#include "HashTable.h"

void initHashTable(HashTable& ht, int size) {
    ht.tableSize = size;
    ht.table.resize(size);
}

int hashFunction(const string& key, int tableSize) {
    int hash = 0;
    for (char ch : key) {
        hash = (hash * 31 + ch) % tableSize;
    }
    return hash;
}

void insert(HashTable& ht, const string& key, const string& value) {
    int index = hashFunction(key, ht.tableSize);
    for (auto& item : ht.table[index]) {
        if (item.first == key) {
            item.second = value;
            return;
        }
    }
    ht.table[index].emplace_back(key, value);
}

bool search(const HashTable& ht, const string& key, string& value) {
    int index = hashFunction(key, ht.tableSize);
    for (const auto& item : ht.table[index]) {
        if (item.first == key) {
            value = item.second;
            return true;
        }
    }
    return false;
}

void remove(HashTable& ht, const string& key) {
    int index = hashFunction(key, ht.tableSize);
    auto& bucket = ht.table[index];
    for (auto it = bucket.begin(); it != bucket.end(); it++) {
        if (it->first == key) {
            bucket.erase(it);
            return;
        }
    }
}

void display(const HashTable& ht) {
    for (size_t i = 0; i < ht.tableSize; ++i) {
        cout << "Index " << i << ": ";
        for (const auto& item : ht.table[i]) {
            cout << "(" << item.first << ", " << item.second << ") -> ";
        }
        cout << "nullptr" << endl;
    }
}
