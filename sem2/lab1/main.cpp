#include "spisok.h"

int main()
{
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
            << "5 - Выход\n";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Введите строку: ";
            cin >> s;
            break;

        case 2:
            SufArray(s, suf, pos);
            for (int i = 0; i < pos.size(); i++) cout << pos[i] << " ";
            cout << endl;
            for (int i = 0; i < suf.size(); i++) cout << suf[i] << endl;
            break;

        case 3:
            cout << "Наименьший циклический сдвиг строки: " << SuffShift(s) << endl;
            break;

        case 4:
            cout << "Введите две подстроки: " << endl;
            string s1, s2;
            cin >> s1;
            cin >> s2;
            string result = MaxPreff(s, s1, s2);
            cout << "Наибольший общий префикс: " << result << endl;
            break;
        }
    } while (choice != 5);
    return 0;
}
