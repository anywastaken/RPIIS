#include <iostream>
#include <vector>
#include <string>
#include <cassert>
using namespace std;

void testSufArray() {
    vector<string> suf;
    vector<int> pos;
    SufArray("banana", suf, pos);
    assert(suf[0] == "a");
    assert(suf[1] == "ana");
    assert(suf[2] == "anana");
    assert(suf[3] == "banana");
    assert(suf[4] == "na");
    assert(suf[5] == "nana");
  
    assert(pos[0] == 5);
    assert(pos[1] == 3);
    assert(pos[2] == 1);
    assert(pos[3] == 0);
    assert(pos[4] == 4);
    assert(pos[5] == 2);

    cout << "Тест пройден!" << endl;
}

void testSuffShift() {
    assert(SuffShift("banana") == 5); 
    assert(SuffShift("abacaba") == 0); 
    assert(SuffShift("aaaa") == 0); 
    cout << "Тест пройден!" << endl;
}

void testMaxPreff() {
    string s = "abacaba";
    assert(MaxPreff(s, "hihealer", "hiheatt") == "hihea");
    assert(MaxPreff(s, "aba", "caba") == "");
    assert(MaxPreff(s, "aba", "xyz") == "");
    cout << "Тест пройден!" << endl;
}
