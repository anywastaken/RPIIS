#include <iostream>
#include <string>
#include "queue.h"

using namespace std;

int main() {
    setlocale(0, "");
    Element* pervyi = nullptr;
    Element* posled = nullptr;

    int choice;
    string element;

    while (true) {
        cout << "����:" << endl;
        cout << "1) �������� �������" << endl;
        cout << "2) ���������� �������" << endl;
        cout << "3) ����� �������" << endl;
        cout << "4) ������� �������" << endl;
        cout << "5) ������� ���������" << endl;
        cout << "�������� ����� ����: ";
        cin >> choice;

        if (choice == 1) {
            cout << "������� ������� ��� ���������� (0 ��� �������� � ����): ";
            cin.ignore();
            getline(cin, element);
            while (element != "0") {
                dobavqueue(pervyi, posled, element);
                cout << "������� ��������� ������� (0 ��� �������� � ����): ";
                getline(cin, element);
            }
        }
        else if (choice == 2) {
            viewqueue(pervyi);
        }
        else if (choice == 3) {
            if (!isEmpty(pervyi)) {
                string value = vziatqueue(pervyi, posled);
                if (value != "") {
                    cout << "������ �������: " << value << endl;
                }
            }
            else {
                cout << "������� �����." << endl;
            }
        }
        else if (choice == 4) {
            clearqueue(pervyi, posled);
        }
        else if (choice == 5) {
            cout << "��������� �������." << endl;
            return 0;
        }
        else {
            cout << "������������ �����. ����������, �������� ������������ ����� ����." << endl;
        }
    }

    return 0;
}
