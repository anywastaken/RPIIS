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

    cout << "Тест SufArray пройден!" << endl;
}

void testSuffShift() {
    assert(SuffShift("earth") == 1);
    assert(SuffShift("goideuu") == 3);
    assert(SuffShift("assyours") == 0);
    cout << "Тест SuffShift пройден!" << endl;
}

void testMaxPreff() {
    string s = "hihealertu";
    assert(MaxPreff(s, "heal", "healert") == "heal");
    assert(MaxPreff(s, "heal", "iheal") == "");
    assert(MaxPreff(s, "lert", "le") == "le");
    cout << "Тест MaxPreff пройден!" << endl;
}
