#include "BTree.hpp"
#include <iostream>

int main() {
    BTree tree;
    int choice;

    do {
        std::cout << "1. Вставить ключ\n";
        std::cout << "2. Поиск ключа\n";
        std::cout << "3. Удалить ключ\n";
        std::cout << "4. Вывести дерево\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите действие: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                int key1, key2;
                std::cout << "Введите ключи (key1 key2): ";
                std::cin >> key1 >> key2;
                tree.insert(key1, key2);
                break;
            }
            case 2: {
                int key1, key2;
                std::cout << "Введите ключи для поиска (key1 key2): ";
                std::cin >> key1 >> key2;
                if (tree.search(key1, key2)) {
                    std::cout << "Ключ найден.\n";
                } else {
                    std::cout << "Ключ не найден.\n";
                }
                break;
            }
            case 3: {
                int key1, key2;
                std::cout << "Введите ключи для удаления (key1 key2): ";
                std::cin >> key1 >> key2;
                tree.remove(key1, key2);
                break;
            }
            case 4: {
                std::cout << "Структура дерева:\n";
                tree.print();
                break;
            }
            case 0: {
                std::cout << "Выход.\n";
                break;
            }
            default: {
                std::cout << "Неверный выбор.\n";
                break;
            }
        }
    } while (choice != 0);

    return 0;
}
