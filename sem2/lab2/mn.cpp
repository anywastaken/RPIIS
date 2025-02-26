#include "mn.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

bool check(int input, int max) {
    return input >= 1 && input <= max;
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
void dobavM(int*& arr, int& size, char setName) {
    if (size > 0) {
        cout << "Множество " << setName << " уже добавлено." << endl;
        return;
    }

    do {
        cout << "Введите мощность множества " << setName << " от 1 до 10: ";
        while (!(cin >> size)) {
            cout << "Мощность множества " << setName << " должна быть числом, введите значение ещё раз: ";
            cin.clear();
            cin.ignore(123, '\n');
        }
        if (size < 1 || size > 10) {
            cout << "Значение мощности превышает лимит, введите значение ещё раз \n ";
        }
    } while (size < 1 || size > 10);

    arr = new int[size]();
    vvod(arr, size);
}
void createSets(int**& sets, int*& sizes, int& numSets) {
    cout << "Введите количество множеств (от 1 до 10): ";
    cin >> numSets;

   
    while (numSets < 1 || numSets > 10) {
        cout << "Количество множеств должно быть от 1 до 10. Введите значение ещё раз: ";
        cin >> numSets;
    }

    sets = new int* [numSets]; 
    sizes = new int[numSets](); 

    for (int i = 0; i < numSets; ++i) {
        char setName = 'A' + i;
        dobavM(sets[i], sizes[i], setName);
    }
}
int* symDifference(int** sets, int* sizes, int numSets, int& resultSize) {
    int maxSize = 0;
    for (int i = 0; i < numSets; ++i) {
        maxSize += sizes[i];
    }

    int* tempResult = new int[maxSize];
    resultSize = 0;


    for (int i = 0; i < numSets; ++i) {
        for (int j = 0; j < sizes[i]; ++j) {
            bool found = false;

           
            for (int k = 0; k < numSets; ++k) {
                if (k != i) { 
                    for (int l = 0; l < sizes[k]; ++l) {
                        if (sets[i][j] == sets[k][l]) {
                            found = true;
                            break;
                        }
                    }
                }
                if (found) break; 
            }

            
            if (!found) {
                tempResult[resultSize++] = sets[i][j];
            }
        }
    }

    
    int* result = new int[resultSize];
    for (int i = 0; i < resultSize; ++i) {
        result[i] = tempResult[i];
    }

    delete[] tempResult; 
    return result;
}
void vyvod(int** sets, int* sizes, int numSets) {
    for (int i = 0; i < numSets; ++i) {
        cout << "Множество " << char('A' + i) << ": ";
        for (int j = 0; j < sizes[i]; ++j) {
            cout << sets[i][j] << " ";
        }
        cout << endl;
    }
}
void save(int** sets, int* sizes, int numSets, const string& filename) {
    ofstream fout(filename);
    if (!fout.is_open()) {
        cout << "Ошибка открытия файла для записи\n";
        return;
    }

    
    fout << numSets << endl; 
    for (int i = 0; i < numSets; i++) {
        fout << sizes[i] << endl;  
        for (int j = 0; j < sizes[i]; j++) {
            fout << sets[i][j] << (j < sizes[i] - 1 ? " " : "");  
        }
        fout << endl; 
    }

    // Сохранение симметрической разности
    fout << "Симметрическая разность: { ";
    bool found = false;

    
    for (int i = 0; i < numSets; i++) {
        for (int j = 0; j < sizes[i]; j++) {
            bool isInOthers = false;

           
            for (int k = 0; k < numSets; k++) {
                if (k != i) { 
                    for (int l = 0; l < sizes[k]; l++) {
                        if (sets[i][j] == sets[k][l]) {
                            isInOthers = true;
                            break;
                        }
                    }
                }
                if (isInOthers) break; 
            }

            
            if (!isInOthers) {
                if (found) {
                    fout << ", ";
                }
                fout << sets[i][j];
                found = true;
            }
        }
    }

    if (!found) {
        fout << "Нет уникальных элементов"; 
    }

    fout << " }\n";

    fout.close();
    cout << "Данные сохранены в файл " << filename << endl;
}
void load(int**& sets, int*& sizes, int& numSets, const string& filename) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        cout << "Ошибка открытия файла: " << filename << endl;
        return;
    }

    
    fin >> numSets;
    sets = new int* [numSets];
    sizes = new int[numSets]; 

    for (int i = 0; i < numSets; i++) {
        fin >> sizes[i]; 
        sets[i] = new int[sizes[i]]; 
        for (int j = 0; j < sizes[i]; j++) {
            fin >> sets[i][j]; 
        }
    }

  
    string temp;
    getline(fin, temp); 

    fin.close();
    cout << "Данные загружены из файла " << filename << endl;
}
