#include <iostream>
#include "RSQ.h"
using namespace std;

void Menu() {
	cout << "���� �������� � ������� ����������:\n";
	cout << "1. ������� ������ �� �������\n";
	cout << "2. ����� ����� �� �������\n";
	cout << "3. ���������� ���� ����� �� ������� �� ��������\n";
	cout << "4. ������ ���� ����� �� ������� �� ��������\n";
	cout << "5. �������� ������\n";
	cout << "6. �����\n";
	cout << "������� ��������: ";
}
int main() {
	setlocale(LC_ALL, "ru");
	rsq* root = NULL;
	int choice, variable_for_all, left_border = -1, right_border = -1, size;
	vector<int> array;
	while (true) {
		Menu();
		left_border = -1;
		right_border = -1;
		cin >> choice;
		switch (choice) {
		case 1:
			cout << "������� ���������� ���������: ";
			cin >> size;
			array.clear();
			array.resize(size);
			cout << "������� " << size << " ���������:\n";
			for (int i = 0; i < size; i++) {
				cout << "������� ������� " << i + 1 << ": ";
				cin >> array[i];
			}
			root = creatersq(0, size - 1, array);
			break;
		case 2:
			if (root != NULL){
				while (left_border < 0 || right_border < 0 || left_border > size || right_border > size || left_border > right_border) {
					cout << "������� ����� ������� �������: ";
					cin >> left_border;
					cout << "������� ������ ������� �������: ";
					cin >> right_border;
				}
				cout << findsum(root, left_border - 1, right_border - 1, 0) << endl;
			}
			else
				cout << "������ ��� �� ������ '_'\n";
			break;
		case 3:
			if (root != NULL) {
				cout << "�����, �� ������� �� �������� ������� ";
				cin >> variable_for_all;
				while (left_border < 0 || right_border < 0 || left_border > size || right_border > size || left_border > right_border) {
					cout << "������� ����� ������� �������: ";
					cin >> left_border;
					cout << "������� ������ ������� �������: ";
					cin >> right_border;
				}
				changeon(root, left_border - 1, right_border - 1, variable_for_all);
			}
			else
				cout << "������ ��� �� ������ '_'\n";
			break;
		case 4:
			if (root != NULL) {
				cout << "�����, �� ������� �� �������� ������� ";
				cin >> variable_for_all;
				while (left_border < 0 || right_border < 0 || left_border > size || right_border > size || left_border > right_border) {
					cout << "������� ����� ������� �������: ";
					cin >> left_border;
					cout << "������� ������ ������� �������: ";
					cin >> right_border;
				}
				changeto(root, left_border - 1, right_border - 1, variable_for_all);
			}
			else
				cout << "������ ��� �� ������ '_'\n";
			break;
		case 5:
			if (root != NULL)
				root = delete_tree(root);
			else
				cout << "������ ��� �� ������ '_'\n";
			break;
		case 6:
			if (root != NULL)
				root = delete_tree(root);
			return 0;
		default:
			cout << "��� ������� ����� ��������� � ��������� ����������!\n";
		}
		
	}
	return 0;
}