#include "mnozestvo.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void dobavA(int*& arrA, int& sizeA) {
    if (sizeA > 0) {
        cout << "Множество A уже добавлено." << endl;
        return;
    }
    do {
        cout << "Введите мощность множества A от 1 до 10: ";
        while (!(cin >> sizeA)) {
            cout << "Мощность множества A должна быть числом, введите значение ещё раз: ";
            cin.clear();
            cin.ignore(123, '\n');
        }
        if (sizeA < 1 || sizeA > 10) {
            cout << "Значение мощности превышает лимит, введите значение ещё раз \n ";
        }
    } while (sizeA < 1 || sizeA > 10);

    arrA = new int[sizeA]();

    vvod(arrA, sizeA);
}

void dobavB(int*& arrB, int& sizeB) {
    if (sizeB > 0) {
        cout << "Множество B уже добавлено." << endl;
        return;
    }
    do {
        cout << "Введите мощность множества B от 1 до 10: ";
        while (!(cin >> sizeB)) {
            cout << "Мощность множества B должна быть числом, введите значение ещё раз: ";
            cin.clear();
            cin.ignore(123, '\n');
        }
        if (sizeB < 1 || sizeB > 10) {
            cout << "Значение мощности превышает лимит, введите значение ещё раз \n ";
        }
    } while (sizeB < 1 || sizeB > 10);

    arrB = new int[sizeB]();

    vvod(arrB, sizeB);
}
void vvod(int* arr, int size) {
    for (int i = 0; i < size; ) {
        cout << "Введите элемент от 1 до 100 " << (i + 1) << ": ";
        int input;


        if (cin >> input) {

            bool unique = true;
            if (!check(input, 100)) {
                cout << "Элемент " << input << " выходит за пределы допустимого диапазона. Пожалуйста, введите элемент еще раз." << endl;
                continue;
            }

            for (int j = 0; j < i; j++) {
                if (arr[j] == input) {
                    cout << "Элемент " << input << " уже введен. Пожалуйста, введите элемент еще раз." << endl;
                    unique = false;
                    break;
                }
            }


            if (unique) {
                arr[i] = input;
                i++;
            }
        }
        else {
            cout << "Элементы должны быть числами, введите элемент еще раз: ";
            cin.clear();
            cin.ignore(123, '\n');
        }
    }
}
bool check(int n, int k) {
    return n >= 1 && n <= k;
}

void symmetricDifference(int* arrA, int sizeA, int* arrB, int sizeB) {
    cout << endl << "Симметрическая разность A и B: {";
    bool found = false; // Флаг для проверки, были ли найдены элементы

    // Элементы, которые есть в A, но нет в B
    for (int i = 0; i < sizeA; i++) {
        bool isInB = false;
        for (int j = 0; j < sizeB; j++) {
            if (arrA[i] == arrB[j]) {
                isInB = true;
                break;
            }
        }
        if (!isInB) {
            if (found) {
                cout << ", "; 
            }
            cout << arrA[i]; 
            found = true; 
        }
    }

    // Элементы, которые есть в B, но нет в A
    for (int i = 0; i < sizeB; i++) {
        bool isInA = false;
        for (int j = 0; j < sizeA; j++) {
            if (arrB[i] == arrA[j]) {
                isInA = true;
                break;
            }
        }
        if (!isInA) {
            if (found) {
                cout << ", ";
            }
            cout << arrB[i]; 
            found = true; 
        }
    }

    if (!found) {
        cout << "0 - пустое множество"; 
    }
    cout << "}" << endl; 
}
void vyvod(int* arr, int size) {
    if (size <= 0) {
        cout << "Множество пустое." << endl;
        return;
    }

    cout << "{ ";
    for (int i = 0; i < size; i++) {
        cout << arr[i];
        if (i < size - 1) {
            cout << ", ";
        }
    }
    cout << " }" << endl;
}

void save(int* arrA, int sizeA, int* arrB, int sizeB, const string& filename) {
    ofstream fout(filename);
    if (!fout.is_open()) {
        cout << "Ошибка открытия файла для записи\n";
        return;
    }

    fout << sizeA << endl;
    for (int i = 0; i < sizeA; i++) {
        fout << arrA[i] << (i < sizeA - 1 ? " " : "");
    }
    fout << endl;

    fout << sizeB << endl; 
    for (int i = 0; i < sizeB; i++) {
        fout << arrB[i] << (i < sizeB - 1 ? " " : "");
    }
    fout << endl;

    fout << "Симметрическая разность AB = { ";
    bool found = false;

    // Элементы, которые есть в A, но нет в B
    for (int i = 0; i < sizeA; i++) {
        bool isInB = false;
        for (int j = 0; j < sizeB; j++) {
            if (arrA[i] == arrB[j]) {
                isInB = true;
                break;
            }
        }
        if (!isInB) {
            if (found) {
                fout << ", "; 
            }
            fout << arrA[i]; 
            found = true; 
        }
    }

    // Элементы, которые есть в B, но нет в A
    for (int i = 0; i < sizeB; i++) {
        bool isInA = false;
        for (int j = 0; j < sizeA; j++) {
            if (arrB[i] == arrA[j]) {
                isInA = true;
                break;
            }
        }
        if (!isInA) {
            if (found) {
                fout << ", "; 
            }
            fout << arrB[i]; 
            found = true; 
        }
    }

    if (!found) {
    }

    fout << " }\n"; 

    fout.close();
    cout << "Данные сохранены в файл " << filename << endl;
}

void load(int*& arrA, int& sizeA, int*& arrB, int& sizeB, const string& filename) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        cout << "Ошибка открытия файла: " << filename << endl;
        return;
    }

    // Загрузка множества A
    fin >> sizeA;
    arrA = new int[sizeA];
    for (int i = 0; i < sizeA; i++) {
        fin >> arrA[i];
    }

    // Загрузка множества B
    fin >> sizeB;
    arrB = new int[sizeB];
    for (int i = 0; i < sizeB; i++) {
        fin >> arrB[i];
    }

   
    string temp;
    getline(fin, temp); // Читаем строку с симметрической разностью

    fin.close();
    cout << "Данные загружены из файла " << filename << endl;
}
