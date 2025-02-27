#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Header.h"

using namespace std;


int main() {
    vector<Union> testi;
    int n;
    cout << "Введите 1, если хотите считать множества из файла" << endl;
    cout << "Введите 2, если хотите ввести множеств в ручную" << endl;
    cin >> n;
    switch (n) {
    case 1: {
        shitivanie_file(testi);
       
    }break;
    case 2: {
        cout << "Введите количество множеств: " << endl;
        int size1;
        cin >> size1;
        cin.ignore();
        testi.resize(size1);
        for (int i = 0; i < size1; i++) {
            cout << "Заполните множество " << i + 1 << ":" << endl;
            testi[i].shitivanie();
        }
     

    }break;
    default: {
        cout << "вы ввели неправильный номер операции, программа завершена";
    }break;

    }
  

    for (int i = 0; i < testi.size(); i++) {
        auto& vec = testi[i].get_vector();
        for (auto& el : vec) {
            /* el.erase(remove(el.begin(), el.end(), ' '), el.end());*/
            string result = sort_set(el);
            el = result;
        }
    }
   
    for (int i = 0; i < testi.size(); i++) {
        bool flag = true;
        for (auto &el : testi[i].get_vector()) {
            checking_znaki(el);
            if (!checking_pravilnost_stroki(el) || !check_podrad(el)) {
                flag = false;
                break;
            }
        }
        if (!flag) {
            cout << endl << "Элемент множества " << ' ' << i + 1 << ' ' << "заполнен не корректно! Пргорамма завершается!" << endl;
            return 0;
        }
    }
    cout << endl << "Отсортированные множества:" << endl;
    for (int i = 0; i < testi.size(); i++) {
        testi[i].print();
        cout << endl;
    }
    vector <string> result = testi[0].get_vector();
    cout << "Пересечение множеств:" << endl;
    main_peresechenie(testi, result);
    for (auto& els : result) {
        cout << els << ' ' << ' ';
    }
    return 0;
}
