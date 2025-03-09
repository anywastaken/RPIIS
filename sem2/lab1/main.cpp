
#include <iostream>
#include "HashTable.h"

int main() {
    HashTable ht;
    initHashTable(ht, 10);

    int choice;
    string key, value;


    do {
        cout << "1. Добавить элемент (ключ-значение)\n";
        cout << "2. Найти элемент по ключу\n";
        cout << "3. Удалить элемент по ключу\n";
        cout << "4. Показать хеш-таблицу\n";
        cout << "0. Выход\n";
        cout << "Выберите действие: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Введите ключ: ";
                cin >> key;
                cout << "Введите значение: ";
                cin >> value;
                insert(ht, key, value);
                break;
            case 2:
                cout << "Введите ключ для поиска: ";
                cin >> key;
                if (search(ht, key, value)) {
                    cout << "Найдено значение: " << value << endl;
                } else {
                    cout << "Ключ не найден.\n";
                }
                break;
            case 3:
                cout << "Введите ключ для удаления: ";
                cin >> key;
                remove(ht, key);
                cout << "Ключ удален, если он существовал.\n";
                break;
            case 4:
                display(ht);
                break;
            case 0:
                cout << "Выход из программы.\n";
                break;
            default:
                cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);

    return 0;
}
