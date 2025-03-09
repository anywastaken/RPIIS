# Библиотека Хеш-таблицы

## 📚 Цель

Целью данной библиотеки является создание эффективной реализации хеш-таблицы для выполнения операций поиска, вставки и удаления элементов.

## 📋 Задачи

- Реализовать структуру данных для представления хеш-таблицы.
- Написать функцию по определения хеша для ключей.
- Разработать функции для вставки пары ключ-значение в таблицу.
- Разработать функции для поиска значения в таблице.
- Разработать функции для удаления значения из таблтцы.

## 🧠 Список используемых понятий

- **Хеш-табли́ца — структура данных, реализующая интерфейс ассоциативного массива, а именно, она позволяет хранить пары (ключ, значение) и выполнять три операции: операцию добавления новой пары, операцию удаления и операцию поиска пары по ключу. 
- **Хеширование — это преобразование информации с помощью особых математических формул. В результате возникает хеш (hash) — отображение данных в виде короткой строки, в идеале — уникальной для каждого набора информации. Размер строки может быть одинаковым для информации разного объема.

## 📖 Описание алгоритмов

- **Вставка (Insertion)**: Алгоритм вставки пары ключ-значение в табоицу. Сначала определяем хеш ключа, затем на основе этого хеша кладем нашу пару в определенный бакет.
- **Поиск (Search)**: Алгоритм поиска пары в таблице. Сначала определяем хеш ключа, затем на основе этого хеша идем в определенный бакет и ищем пару там.
- **Удаление (Deletion)**: Алгоритм удаления пары из таблицы. Сначала определяем хеш ключа, затем на основе этого хеша ищем элемент в определенном бакете, затем удаляем его от-туда.
- **Хеш-функция**:Начальное значения хеша для каждого ключа равно 0. Затем к хешу добавляется код каждого символа в ключе и узнается остаток от деления этого числа на 10(Так как всего 10 бакетов).
  
![image](https://github.com/user-attachments/assets/a4668cbc-a022-4e83-9611-9323adb7ffcc)

## 📂 Файлы проекта

- [main.cpp](./main.cpp) - Основной файл с консольным приложением.
- [HashTable.h](./HashTable.h) - Заголовочный файл со структурой хеш-таблицы.
- [HashTable.cpp](./HashTable.cpp) - Файл с реализацией функционала хеш-таблицы.

## 🛠️ Тестирование
Небольшая программа с реализацией моей библиотеки:
```cpp
#include "HashTable.h"

void initHashTable(HashTable& ht, int size) {
    ht.tableSize = size;
    ht.table.resize(size);
}

int hashFunction(const string& key, int tableSize) {
    int hash = 0;
    for (char ch : key) {
        hash = (hash * 31 + ch) % tableSize;
    }
    return hash;
}

void insert(HashTable& ht, const string& key, const string& value) {
    int index = hashFunction(key, ht.tableSize);
    for (auto& item : ht.table[index]) {
        if (item.first == key) {
            item.second = value;
            return;
        }
    }
    ht.table[index].emplace_back(key, value);
}

bool search(const HashTable& ht, const string& key, string& value) {
    int index = hashFunction(key, ht.tableSize);
    for (const auto& item : ht.table[index]) {
        if (item.first == key) {
            value = item.second;
            return true;
        }
    }
    return false;
}

void remove(HashTable& ht, const string& key) {
    int index = hashFunction(key, ht.tableSize);
    auto& bucket = ht.table[index];
    for (auto it = bucket.begin(); it != bucket.end(); it++) {
        if (it->first == key) {
            bucket.erase(it);
            return;
        }
    }
}

void display(const HashTable& ht) {
    for (size_t i = 0; i < ht.tableSize; ++i) {
        cout << "Index " << i << ": ";
        for (const auto& item : ht.table[i]) {
            cout << "(" << item.first << ", " << item.second << ") -> ";
        }
        cout << "nullptr" << endl;
    }
}

```
## Инициализация Хеш-таблицы

## Заключение


## Использованные источники:

### Свободная энциклопедия "Википедия"
- https://ru.m.wikipedia.org/wiki/

