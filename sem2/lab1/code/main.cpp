#include <iostream>
#include "BTree.hpp"

#define WINDOWS
// #define LINUX

void clear_console();
void print_menu();
void run_tests();
void manual_input();

int main() {
    setlocale(LC_ALL, "RU");
    int choice;

    do {
        clear_console();
        print_menu();
        std::cin >> choice;

        switch (choice) {
        case 1:
            clear_console();
            run_tests();
            break;
        case 2:
            clear_console();
            manual_input();
            break;
        case 3:
            clear_console();
            std::cout << "Выход из программы.\n";
            break;
        default:
            std::cout << "Неверный ввод. Попробуйте снова.\n";
            break;
        }

        if (choice != 3) {
            std::cout << "Нажмите Enter, чтобы продолжить...";
            std::cin.ignore();
            std::cin.get();
        }
    } while (choice != 3);

    return 0;
}

void clear_console() {
#ifdef WINDOWS
    system("cls");
#endif
#ifdef LINUX
    system("clear");
#endif
}

void print_menu() {
    std::cout << "1. Запустить тесты\n";
    std::cout << "2. Ручной ввод\n";
    std::cout << "3. Выход\n";
    std::cout << "Выберите опцию: ";
}

void run_tests() {
    BTree Tree;
    int test_data[5][10] = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},          // Тест 1
        {22, 11, 9, 52, 162, -10, 12, 66, 21, 33}, // Тест 2
        {-11, -21, -31, 31, 21, 11, 155, 101, 47, 49}, // Тест 3
        {-5, 7, -8, 9, 11, 221, -331, 21, 46, -92}, // Тест 4
        {5, 2, -91, 132, 144, -55, 1, 3, 4, 6}                // Тест 5
    };

    for (int i = 0; i < 5; ++i) {
        std::cout << "Тест " << i + 1 << ":\n";
        for (int key : test_data[i]) {
            Tree.insert(key);
        }
        std::cout << "Обход дерева: ";
        Tree.traverse();
        std::cout << "\n";

        int key_to_delete;
        std::cout << "Введите ключ для удаления: ";
        std::cin >> key_to_delete;

        if (Tree.search(key_to_delete)) {
            std::cout << "Ключ " << key_to_delete << " найден!\n";
            std::cout << "Удалить? (1 - Да, 0 - Нет): ";
            int choice;
            std::cin >> choice;
            if (choice == 1) {
                Tree.remove(key_to_delete);
                std::cout << "Дерево после удаления: ";
                Tree.traverse();
                std::cout << "\n";
            }
            else {
                std::cout << "Удаление отменено.\n";
            }
        }
        else {
            std::cout << "Ключ " << key_to_delete << " не найден.\n";
        }

        std::cout << "*-*-*-*-*-*-*-*\n";
        Tree = BTree();
    }
}

void manual_input() {
    BTree Tree;
    int num_of_keys;
    std::cout << "Введите количество ключей для вставки в дерево: ";
    std::cin >> num_of_keys;

    for (int i = 0; i < num_of_keys; ++i) {
        int key;
        std::cout << "Введите " << i + 1 << " ключ: ";
        std::cin >> key;
        if (Tree.search(key) != nullptr) {
            std::cout << "Ключи не должны повторяться..." << std::endl;
            i--;
        }
        else {
            Tree.insert(key);
        }
    }

    std::cout << "Обход дерева: ";
    Tree.traverse();
    std::cout << "\n";

    int key_to_search;
    std::cout << "Введите ключ для поиска: ";
    std::cin >> key_to_search;

    if (Tree.search(key_to_search)) {
        std::cout << "Ключ " << key_to_search << " найден!\n";
        std::cout << "Удалить? (1 - Да, 0 - Нет): ";
        int choice;
        std::cin >> choice;
        if (choice == 1) {
            Tree.remove(key_to_search);
            std::cout << "Дерево после удаления: ";
            Tree.traverse();
            std::cout << "\n";
        }
        else {
            std::cout << "Удаление отменено.\n";
        }
    }
    else {
        std::cout << "Ключ " << key_to_search << " не найден.\n";
    }
}