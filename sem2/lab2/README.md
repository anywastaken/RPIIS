# Лабораторная работа №2
**Вариант №3** 
## Цели лабораторной работы:
Изучить основы теории множеств.
## Задачи лабораторной работы
Реализовать программу, формирующую множество равное симметрической разности исходных множеств (без учёта кратных вхождений элементов).

Изучить основы теории множеств.
## Список ключевых понятий:
**Множество** – это структурированный тип данных, представляющий собой набор взаимосвязанных по какому-либо признаку или группе признаков неповторяющихся объектов, которые можно рассматривать как единое целое.

**Симметрическая разность** – это набор элементов, которые принадлежат либо первому, либо второму множеству, но не их пересечению. Иными словами, симметрическая разность содержит все элементы обоих множеств, кроме общих.

## Описание используемых алгоритмов:
*Библиотека fstream*: содержит инструменты для работы с файлами.

1. **Создание и ввод множеств**
 
  1.1 С помощью функции *void createMN* реализуется ввод количества множеств
  
```cpp
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
```

 1.2 С помощью функции *void dobavMn* реализуется ввод мощности множества

```cpp
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
```

 1.3 С помощью функции *void vvod* реализуется ввод элементов множества; *bool povtor* - проверка на повторяющиеся элементы


```cpp
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

bool povtor(string* mn, int size, const string& elem) {
    for (int i = 0; i < size; ++i) {
        if (mn[i] == elem) {
            return true;
        }
    }
    return false;
}


```

2.  С помощью функции *string checkGroupElements* реализуется подстановка элементов в фигурные скобки

  
```cpp
string checkGroupElements(const string& elem) {
    if (elem.find('<') == 0 && elem.find('>') == elem.length() - 1) {
        return elem; // Если элемент уже в <>
    }
    if (elem.find(',') != string::npos) {
        return "{" + elem + "}"; // Если элемент содержит запятую, но не в <>
    }
    return elem; 
}
```


3. С помощью функции *void symmetricDifference* реализуется вычисление симметрической разности
   
   
```cpp
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
            // Если элемент не в результирующем множестве, добавляем его
            if (!elementInResult(mn[i][j])) {
                // Проверяем, сколько раз элемент встречается в остальных множествах
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
                // Если элемент встречается только в одном множестве, добавляем его в результат
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
```


4. С помощью функции *void save* реализуется сохрание множеств и их элементов в текстовый файл
   
 
```cpp
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

```

5. С помощью функции *void load* данные множеств и их элементов выгружаются из текстового файла

```cpp



```
## Тесты:


## Вывод:

В результате выполнения данной работы были получены следующие практические навыки:
Изучение теории множеств и выполнения операций над ними;
Работа header-файлами.





## Используемые источники:
1) **Создание библиотеки** :(https://www.youtube.com/watch?v=pAxEfF2yVlM&t=1s)
