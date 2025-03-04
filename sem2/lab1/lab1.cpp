#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include <cassert>
using namespace std;

void SufArray(string s, vector<string>& suf, vector<int>& pos);
int SuffShift(string s);
string MaxPreff(string s, string s1, string s2);
void testSufArray();
void testSuffShift();
void testMaxPreff();

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "Введите строку: ";
    string s;
    cin >> s;
    vector<string> suf;
    vector<int> pos;
    SufArray(s, suf, pos);

    int choice;

    do {
        cout << "Меню:\n"
            << "1 - Ввести новую строку.\n"
            << "2 - Построить суффиксный массив из строки.\n"
            << "3 - Найти наименьший циклический сдвиг строки.\n"
            << "4 - Найти наибольший общий префикс двух подстрок.\n"
            << "5 - Тест\n"
            << "6 - Выход\n";
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "Введите строку: ";
            cin >> s;
            break;
        }

        case 2: {
            SufArray(s, suf, pos);
            cout << "Позиции: ";
            for (int i = 0; i < pos.size(); i++) cout << pos[i] << " ";
            cout << endl;
            cout << "Суффиксы:" << endl;
            for (int i = 0; i < suf.size(); i++) cout << suf[i] << endl;
            break;
        }

        case 3: {
            cout << "Наименьший циклический сдвиг строки: " << SuffShift(s) << endl;
            break;
        }

        case 4: {
            cout << "Введите две подстроки: " << endl;
            string s1, s2;
            cin >> s1 >> s2;
            string result = MaxPreff(s, s1, s2);
            if (!result.empty()) cout << "Наибольший общий префикс: " << result << endl;
            break;
        }

        case 5: {
            cout << "Проверка функции SufArray." << endl;
            testSufArray();
            cout << "Проверка функции SuffShift." << endl;
            testSuffShift();
            cout << "Проверка функции MaxPreff." << endl;
            testMaxPreff();
            cout << "Все тесты пройдены успешно!" << endl;
            break;
        }

        default: {
            cout << "Неверный выбор. Попробуйте снова." << endl;
            break;
        }
        }
    } while (choice != 6);

    return 0;
}

void SufArray(string s, vector<string>& suf, vector<int>& pos) {
    suf.clear();
    pos.clear();
    for (int i = 0; i < s.size(); i++) {
        suf.push_back(s.substr(i));
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
        cout << "Нет общих префиксов." << endl;
        return "";
    }
    return s1.substr(0, count);
}

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
