#include <iostream>
#include "spis.hpp"
#include <locale>
using namespace std;
void menu() {
	cout << "�������� ������� � ������-1" << endl;
	cout << "������� ������� �� �������-2" << endl;
	cout << "������������� ������-3" << endl;
	cout << "����� ������� � ������-4" << endl;
	cout << "����������� �������-5" << endl;
	cout << "����������� �������-6" << endl;
	cout << "�������� ������-7" << endl;
	cout << "������� ������-8" << endl;
	cout << "�����-0" << endl;
	cout << "�������� �����: " << endl;
}
int main()
{
	setlocale(LC_ALL, "ru");
	int elem1, n1, elem2, n2, elem, choice, elem3;
	Spis* Spis1 = NULL;
	Spis* Spis2 = NULL;
	cout << "������� ���������� ��������� ������� ������:";
	cin >> n1;
	cout << "������� �������� ������� ������:" << endl;;
	for (int i = 0; i < n1; i++) {
		cin >> elem1;
		Spis1 = InSpis(Spis1, elem1);
	}
	cout << "������� ���������� ��������� ������� ������:";
	cin >> n2;
	cout << "������� �������� ������� ������:" << endl;;
	for (int i = 0; i < n2; i++) {
		cin >> elem2;
		Spis2 = InSpis(Spis2, elem2);
	}
	menu();
	do {
		cin >> choice;
		switch (choice) {
		case 1:
			cout << "����� ������� ������ �������� � ������?" << endl;
			cin >> elem;
			int N_Spis;
			cout << "� ����� ������ �������� �������?� ������-1,�� ������-2" << endl;
			cin >> N_Spis;
			switch (N_Spis) {
			case 1:
				Spis1 = InSpis(Spis1, elem);
				View(Spis1);
				break;
			case 2:
				Spis2 = InSpis(Spis2, elem);
				View(Spis2);
				break;
			}
			break;
		case 2:
			cout << "����� ������� ������ ������� �� ������?" << endl;
			cin >> elem3;
			int N_Spis2;
			cout << "� ����� ������� ������� �������?� ������-1,�� ������-2" << endl;
			cin >> N_Spis2;
			switch (N_Spis2) {
			case 1:
				Del_Elem(&Spis1, elem3);
				break;
			case 2:
				Del_Elem(&Spis2, elem3);
				break;
			}
			break;
		case 3:
			cout << "����� ������ ������ �������������?������-1,������-2" << endl;
			int N_Spis3;
			cin >> N_Spis3;
			switch (N_Spis3) {
			case 1:
				Sort_info(Spis1);
				break;
			case 2:
				Sort_info(Spis2);
				break;
			}
			break;
		case 4:
			cout << "����� ������� ������ ����� � ������?" << endl;
			int elem4;
			cin >> elem4;
			cout << "� ����� ������ ������?� ������-1,�� ������-2" << endl;
			int N_Spis4;
			cin >> N_Spis4;
			switch (N_Spis4) {
			case 1:
				Search(Spis1, elem4);
				break;
			case 2:
				Search(Spis2, elem4);
				break;
			}
			break;
		case 5:
			Union(Spis1, Spis2);
			break;
		case 6:
			Intersection(Spis1, Spis2);
			break;
		case 7:
			Del_All(&Spis1);
			Del_All(&Spis2);
			break;
		case 8:
			cout << "������ ������: ";
			View(Spis1);
			cout << "������ ������: ";
			View(Spis2);
			break;
		}
	} while (choice != 0);
	Del_All(&Spis1);
	Del_All(&Spis2);
	return 0;
}