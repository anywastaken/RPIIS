#include "mn.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
void createMN(string**& mn, int*& sizes, int& nummn) {
    cout << "Введите количество множеств (от 1 до 10): ";
    cin >> nummn;

    while (nummn < 0 || nummn > 10) {
        cout << "Количество множеств должно быть от 1 до 10. Введите значение ещё раз: ";
        cin >> nummn;
    }

    mn = new string * [nummn]; 
    sizes = new int[nummn](); 

    for (int i = 0; i < nummn; ++i) {
        char Name = 'A' + i;
        dobavMn(mn[i], sizes[i], Name);
    }
}

void dobavMn(string*& mn, int& size, char Name) {
    if (size > 0) {
        cout << "Множество " << Name << " уже добавлено." << endl;
        return;
    }

    cout << "Введите мощность множества " << Name << " от 0 до 10: ";
    while (!(cin >> size) || size < 0 || size > 10) {
        cout << "Мощность множества " << Name << " должна быть числом от 0 до 10, введите значение ещё раз: ";
        cin.clear();
        cin.ignore(123, '\n');
    }

    mn = new string[size];
    vvod(mn, size);
}
bool povtor(string* mn, int size, const string& elem) {
    for (int i = 0; i < size; ++i) {
        if (mn[i] == elem) {
            return true;
        }
    }
    return false;
}

void vvod(string* mn, int size) {
    cin.ignore(); 
    for (int i = 0; i < size; ++i) {
        string elem;
        cout << "Введите " << i + 1 << "-й элемент: ";
        getline(cin, elem);

        elem = checkGroupElements(elem);

        while (povtor(mn, i, elem)) {
            cout << "Элемент " << elem << " уже существует. Введите " << i + 1 << "-й элемент ещё раз: ";
            getline(cin, elem);
            elem = checkGroupElements(elem);
        }
        mn[i] = elem;
    }
}

string checkGroupElements(const string& elem) {
    if (elem.find('<') == 0 && elem.find('>') == elem.length() - 1) {
        return elem;
    }
    if (elem.find(',') != string::npos) {
        return "{" + elem + "}"; 
    }
    return elem; 
}
void printMN(string** mn, int* sizes, int nummn) {
    for (int i = 0; i < nummn; ++i) {
        char Name = 'A' + i;
        cout << "Множество " << Name << " = {";
        for (int j = 0; j < sizes[i]; ++j) {
            cout << mn[i][j];
            if (j < sizes[i] - 1) {
                cout << ", ";
            }
        }
        cout << "}" << endl;
    }
}
void symmetricDifference(string** mn, int* sizes, int nummn) {
    if (nummn < 2) {
        cout << "Для вычисления симметрической разности необходимо как минимум два множества.\n";
        return;
    }

  
    string result[100]; 
    int resultSize = 0;

    auto elementInResult = [&](const string& elem) {
        for (int i = 0; i < resultSize; ++i) {
            if (result[i] == elem) return true;
        }
        return false;
    };


    for (int i = 0; i < nummn; ++i) {
        for (int j = 0; j < sizes[i]; ++j) {
            
            if (!elementInResult(mn[i][j])) {
                
                int count = 0;
                for (int k = 0; k < nummn; ++k) {
                    if (k != i) {
                        for (int l = 0; l < sizes[k]; ++l) {
                            if (mn[i][j] == mn[k][l]) {
                                count++;
                            }
                        }
                    }
                }
                
                if (count == 0) {
                    result[resultSize++] = mn[i][j];
                }
            }
        }
    }

    cout << "Симметрическая разность = {";
    for (int i = 0; i < resultSize; ++i) {
        cout << result[i];
        if (i < resultSize - 1) {
            cout << ", ";
        }
    }
    cout << "}" << endl;
}

void save(string**& mn, int*& sizes, int& nummn, const string& filename) {
    ofstream fout(filename);
    if (!fout.is_open()) {
        cout << "Ошибка открытия файла для записи\n";
        return;
    }

    fout << "Количество множеств: " << nummn << endl;
    for (int i = 0; i < nummn; i++) {
        char Name = 'A' + i; 
        fout << "Множество " << Name << " = {";
        for (int j = 0; j < sizes[i]; j++) {
            fout << mn[i][j];
            if (j < sizes[i] - 1) {
                fout << ", ";
            }
        }
        fout << "}" << endl;
    }

    fout << "Симметрическая разность = { ";
    bool found = false;


    for (int i = 0; i < nummn; i++) {
        for (int j = 0; j < sizes[i]; j++) {
            bool isInOthers = false;


            for (int k = 0; k < nummn; k++) {
                if (k != i) {
                    for (int l = 0; l < sizes[k]; l++) {
                        if (mn[i][j] == mn[k][l]) {
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
                fout << mn[i][j];
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

void load(string**& mn, int*& sizes, int& nummn, const string& filename) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        cout << "Ошибка открытия файла: " << filename << endl;
        return;
    }

    string line;
    nummn = 0;

   
    while (getline(fin, line)) {
        if (line.find("Множество") != string::npos) {
            nummn++;
        }
    }

    mn = new string*[nummn];
    sizes = new int[nummn];

    fin.clear();
    fin.seekg(0);

    int currentSet = 0;
    while (getline(fin, line)) {
        if (line.find("Множество") != string::npos) {
            size_t start = line.find('{');
            if (start != string::npos) {
                size_t end = start;
                int braceCount = 1;

                while (braceCount > 0 && end < line.length()) {
                    end++;
                    if (line[end] == '{') {
                        braceCount++;
                    } else if (line[end] == '}') {
                        braceCount--;
                    }
                }

                if (braceCount == 0) {
                    string elements = line.substr(start + 1, end - start - 1);
                    sizes[currentSet] = 0;

                    for (size_t i = 0; i < elements.length(); i++) {
                        if (elements[i] == ',') {
                            sizes[currentSet]++;
                        }
                    }
                    sizes[currentSet]++;

                    mn[currentSet] = new string[sizes[currentSet]];

                    int index = 0;
                    string currentElement;
                    for (size_t i = 0; i < elements.length(); i++) {
                        if (elements[i] == ',') {
                            mn[currentSet][index++] = currentElement;
                            currentElement.clear();
                        } else {
                            currentElement += elements[i];
                        }
                    }
                    if (!currentElement.empty()) {
                        mn[currentSet][index++] = currentElement;
                    }
                    currentSet++;
                }
            }
        }
    }

    fin.close();
    cout << "Данные загружены из файла " << filename << endl;
}
