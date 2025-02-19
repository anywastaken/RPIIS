#include <iostream>
#include "spis.hpp"
#include <locale>
using namespace std;

void TestInsertion() {
    cout << "����: ������� ��������� � ������" << endl;
    Spis* list = nullptr;

    list = InSpis(list, 10);
    list = InSpis(list, 20);
    list = InSpis(list, 30);

    cout << "��������� ���������: 30 20 10" << endl;
    cout << "����������� ���������: ";
    View(list);

    Del_All(&list);
    cout << "--------------------------" << endl;
}

void TestDeletion() {
    cout << "����: �������� �������� �� ������" << endl;
    Spis* list = nullptr;

    list = InSpis(list, 10);
    list = InSpis(list, 20);
    list = InSpis(list, 30);

    Del_Elem(&list, 20); // ������� ������� 20

    cout << "��������� ���������: 30 10" << endl;
    cout << "����������� ���������: ";
    View(list);

    Del_All(&list);
    cout << "--------------------------" << endl;
}

void TestSorting() {
    cout << "����: ���������� ������" << endl;
    Spis* list = nullptr;

    list = InSpis(list, 3);
    list = InSpis(list, 1);
    list = InSpis(list, 4);
    list = InSpis(list, 2);

    Sort_info(list);

    cout << "��������� ���������: 1 2 3 4" << endl;
    cout << "����������� ���������: ";
    View(list);

    Del_All(&list);
    cout << "--------------------------" << endl;
}

void TestSearch() {
    cout << "����: ����� ��������" << endl;
    Spis* list = nullptr;

    list = InSpis(list, 10);
    list = InSpis(list, 20);
    list = InSpis(list, 30);

    cout << "��������� ���������: ������" << endl;
    cout << "����������� ���������: ";
    Search(list, 20);

    cout << "��������� ���������: �� ������" << endl;
    cout << "����������� ���������: ";
    Search(list, 50);

    Del_All(&list);
    cout << "--------------------------" << endl;
}

void TestUnion() {
    cout << "����: ����������� �������" << endl;
    Spis* list1 = nullptr;
    Spis* list2 = nullptr;

    list1 = InSpis(list1, 1);
    list1 = InSpis(list1, 2);
    list1 = InSpis(list1, 3);

    list2 = InSpis(list2, 3);
    list2 = InSpis(list2, 4);
    list2 = InSpis(list2, 5);

    Union(list1, list2);

    Del_All(&list1);
    Del_All(&list2);
    cout << "--------------------------" << endl;
}

void TestIntersection() {
    cout << "����: ����������� �������" << endl;
    Spis* list1 = nullptr;
    Spis* list2 = nullptr;

    list1 = InSpis(list1, 1);
    list1 = InSpis(list1, 2);
    list1 = InSpis(list1, 3);

    list2 = InSpis(list2, 3);
    list2 = InSpis(list2, 4);
    list2 = InSpis(list2, 5);

    Intersection(list1, list2);

    Del_All(&list1);
    Del_All(&list2);
    cout << "--------------------------" << endl;
}
#ifdef TEST_MODE 
int main(){
    setlocale(LC_ALL, "ru");
    TestInsertion();
    TestDeletion();
    TestSorting();
    TestSearch();
    TestUnion();
    TestIntersection();
    return 0;
}
#endif