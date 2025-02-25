#include <iostream>
#include <string>
#include "mnozestvo.h"
#include <fstream>
using namespace std;
int main() {
    setlocale(0, "rus");
    int a, b;
    int* arrA ;
    int* arrB ;
    int choice;
    
    
   
    load(arrA,a,arrB,b, "D:\\Уник\\Пиовис\\lab2\\soxr.txt");
    while (true) {
        cout << "Меню:" << endl;
        cout << "1) Добавить множество А" << endl;
        cout << "2) Добавить множество B" << endl;
        cout << "3) Просмотр множество А" << endl;
        cout << "4) Просмотр множество B" << endl;
        cout << "5) Просмотр симетрической разности" << endl;
        cout << "6) Сохранить файл" << endl;
        cout << "7) Закрыть программу" << endl;
        cout << "Выберите пункт меню: ";
        cin >> choice;

        if (choice == 1) {
            dobavA(arrA, a);      
        }
        else if (choice == 2) {
           dobavB(arrB, b); 
        }
        else if (choice == 3) {

            cout << "A="; vyvod(arrA, a);
        }
        else if (choice == 4) {

            cout << "B="; vyvod(arrB, b);
        }
        else if (choice == 5) {
            
            symmetricDifference(arrA, a, arrB, b);
        }
        else if (choice == 6) {
            save(arrA, a, arrB, b, "D:\\Уник\\Пиовис\\lab2\\soxr.txt");
        }
        else if (choice == 7) {

            cout << "Программа закрыта." << endl;
            return 0;
        }
        else {
            cout << "Некорректный выбор. Пожалуйста, выберите существующий пункт меню." << endl;
        }
    }
    return 0;
   

    delete[] arrA;
    delete[] arrB;
    return 0;
}




