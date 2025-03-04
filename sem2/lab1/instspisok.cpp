#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
using namespace std;

void SufArray(string s, vector<string>& suf, vector<int>& pos) {
    suf.clear();
    pos.clear();
    for (int i = 0; i < s.size(); i++) {
        suf.push_back(s.substr(i));
        pos.push_back(i);
    }

    for (int i = 0; i < suf.size() - 1; i++) {
        for (int j = i+1; j < suf.size(); j++) {
            if (suf[i] > suf[j]) {
                swap(suf[j], suf[i]);
                swap(pos[j], pos[i]);
            }
        }
    }
}

int SuffShift(string s) {
    string s2 = s + s;
    int size = s.size();
    vector<string> suf;
    vector<int> pos;
    for (int i = 0; i < size; i++) {
        suf.push_back(s2.substr(i, size));
        pos.push_back(i);
    }

    for (int i = 0; i < suf.size() - 1; i++) {
        for (int j = i + 1; j < suf.size(); j++) {
            if (suf[i] > suf[j]) {
                swap(suf[j], suf[i]);
                swap(pos[j], pos[i]);
            }
        }
    }
    if (pos[0] <= size / 2) return pos[0];
    else return (size - pos[0]);
}

string MaxPreff(string s, string s1, string s2) {
    if (s.find(s1) == string::npos || s.find(s2) == string::npos) {
        cout << "Данные строки не являются подстроками!" << endl;
        return "";
    }

    int count = 0;
    for (int i = 0; i < s1.size() && i < s2.size(); i++) {
        if (s1[i] == s2[i]) count++;
        else break;
    }

    if (count == 0) {
        cout << "Нету общих префиксов." << endl;
        return "";
    }
    return s1.substr(0, count);
}
