
#include <iostream>
#include <string>
#include "mn.h"
#include <fstream>
using namespace std;
int main() {
    setlocale(0, "rus");
    int choice;
    string** mn = nullptr; 
    int* sizes = nullptr; 
    int nummn; 
    
    load(mn, sizes, nummn, "D:\\Уник\\Пиовис\\Lab2\\soxr.txt");
    while (true) {
        cout << "Меню:" << endl;
        cout << "1) Добавить множества " << endl;
        cout << "2) Просмотр множеств " << endl;
        cout << "3) Просмотр симметрической разности" << endl;
        cout << "4) Сохранить файл" << endl;
        cout << "5) Закрыть программу" << endl;
        cout << "Выберите пункт меню: ";
        cin >> choice;
        if (choice == 1) {
            createMN(mn, sizes,  nummn);
            
        }

        else if (choice == 2) {
            if (mn != nullptr) {
                printMN(mn, sizes, nummn);
            }
            else {
                cout << "Множества еще не добавлены.\n";
            }
            
        }
        else if (choice == 3) {
            if (mn != nullptr) {
                symmetricDifference(mn, sizes, nummn);
            }
            else {
                cout << "Множества еще не добавлены.\n";
            }
        }
        else if (choice == 4) {
            save(mn, sizes, nummn, "D:\\Уник\\Пиовис\\Lab2\\soxr.txt");
        }
        else if (choice == 5) {
            cout << "Программа закрыта." << endl;
            break;
        }
        else {
            cout << "Некорректный выбор. Пожалуйста, выберите существующий пункт меню." << endl;
        }
    }

   

    return 0;
}

