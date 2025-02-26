#include <iostream>
#include <string>
#include "mn.h"
#include <fstream>
using namespace std;


int main() {
    setlocale(0, "rus");
    int** sets = nullptr;  
    int* sizes = nullptr; 
    int numSets = 0; 
    int choice;
    load(sets, sizes, numSets, "D:\\Уник\\Пиовис\\laba2\\soxr.txt");
    while (true) {
        cout << "Меню:" << endl;
        cout << "1) Добавить множества " << endl;
        cout << "2) Просмотр множеств " << endl;
        cout << "3) Просмотр симетрической разности" << endl;
        cout << "4) Сохранить файл" << endl;
        cout << "5) Закрыть программу" << endl;
        cout << "Выберите пункт меню: ";
        cin >> choice;

        if (choice == 1) {
            createSets(sets,  sizes, numSets);
        }
       
        else if (choice == 2) {

            vyvod(sets, sizes, numSets);
        }
       
        else if (choice == 3) {
            int resultSize; 
            int* result = symDifference(sets, sizes, numSets, resultSize); // Вызов функции

           
            cout << "Симметрическая разность={ ";
            for (int i = 0; i < resultSize; ++i) {
                cout << result[i] << " ";
            }
            cout <<"}" <<endl;

            delete[] result;
        }
        else if (choice == 4) {
           
            save(sets, sizes, numSets, "D:\\Уник\\Пиовис\\laba2\\soxr.txt");
        }
        else if (choice == 5) {

            cout << "Программа закрыта." << endl;
            return 0;
        }
        else {
            cout << "Некорректный выбор. Пожалуйста, выберите существующий пункт меню." << endl;
        }
    }
    return 0;

    
    for (int i = 0; i < numSets; ++i) {
        delete[] sets[i];
    }
    delete[] sets;
    delete[] sizes;

    return 0;
}




