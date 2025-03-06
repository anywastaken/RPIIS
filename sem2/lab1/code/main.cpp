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
            std::cout << "����� �� ���������.\n";
            break;
        default:
            std::cout << "�������� ����. ���������� �����.\n";
            break;
        }

        if (choice != 3) {
            std::cout << "������� Enter, ����� ����������...";
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
    std::cout << "1. ��������� �����\n";
    std::cout << "2. ������ ����\n";
    std::cout << "3. �����\n";
    std::cout << "�������� �����: ";
}

void run_tests() {
    BTree Tree;
    int test_data[5][10] = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},          // ���� 1
        {22, 11, 9, 52, 162, -10, 12, 66, 21, 33}, // ���� 2
        {-11, -21, -31, 31, 21, 11, 155, 101, 47, 49}, // ���� 3
        {-5, 7, -8, 9, 11, 221, -331, 21, 46, -92}, // ���� 4
        {5, 2, -91, 132, 144, -55, 1, 3, 4, 6}                // ���� 5
    };

    for (int i = 0; i < 5; ++i) {
        std::cout << "���� " << i + 1 << ":\n";
        for (int key : test_data[i]) {
            Tree.insert(key);
        }
        std::cout << "����� ������: ";
        Tree.traverse();
        std::cout << "\n";

        int key_to_delete;
        std::cout << "������� ���� ��� ��������: ";
        std::cin >> key_to_delete;

        if (Tree.search(key_to_delete)) {
            std::cout << "���� " << key_to_delete << " ������!\n";
            std::cout << "�������? (1 - ��, 0 - ���): ";
            int choice;
            std::cin >> choice;
            if (choice == 1) {
                Tree.remove(key_to_delete);
                std::cout << "������ ����� ��������: ";
                Tree.traverse();
                std::cout << "\n";
            }
            else {
                std::cout << "�������� ��������.\n";
            }
        }
        else {
            std::cout << "���� " << key_to_delete << " �� ������.\n";
        }

        std::cout << "*-*-*-*-*-*-*-*\n";
        Tree = BTree();
    }
}

void manual_input() {
    BTree Tree;
    int num_of_keys;
    std::cout << "������� ���������� ������ ��� ������� � ������: ";
    std::cin >> num_of_keys;

    for (int i = 0; i < num_of_keys; ++i) {
        int key;
        std::cout << "������� " << i + 1 << " ����: ";
        std::cin >> key;
        if (Tree.search(key) != nullptr) {
            std::cout << "����� �� ������ �����������..." << std::endl;
            i--;
        }
        else {
            Tree.insert(key);
        }
    }

    std::cout << "����� ������: ";
    Tree.traverse();
    std::cout << "\n";

    int key_to_search;
    std::cout << "������� ���� ��� ������: ";
    std::cin >> key_to_search;

    if (Tree.search(key_to_search)) {
        std::cout << "���� " << key_to_search << " ������!\n";
        std::cout << "�������? (1 - ��, 0 - ���): ";
        int choice;
        std::cin >> choice;
        if (choice == 1) {
            Tree.remove(key_to_search);
            std::cout << "������ ����� ��������: ";
            Tree.traverse();
            std::cout << "\n";
        }
        else {
            std::cout << "�������� ��������.\n";
        }
    }
    else {
        std::cout << "���� " << key_to_search << " �� ������.\n";
    }
}