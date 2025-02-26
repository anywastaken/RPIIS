#include <iostream>
#include "RSQ.h"
using namespace std;

void Menu() {
	cout << "Меню операций с деревом максимумов:\n";
	cout << "1. Создать дерево из массива\n";
	cout << "2. Поиск суммы на отрезке\n";
	cout << "3. Увелечение всех чисел на отрезке на значение\n";
	cout << "4. Замена всех чисел на отрезке на значение\n";
	cout << "5. Очистить дерево\n";
	cout << "6. Выход\n";
	cout << "Введите операцию: ";
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
			cout << "Введите количество элементов: ";
			cin >> size;
			array.clear();
			array.resize(size);
			cout << "Введите " << size << " элементов:\n";
			for (int i = 0; i < size; i++) {
				cout << "Введите элемент " << i + 1 << ": ";
				cin >> array[i];
			}
			root = creatersq(0, size - 1, array);
			break;
		case 2:
			if (root != NULL){
				while (left_border < 0 || right_border < 0 || left_border > size || right_border > size || left_border > right_border) {
					cout << "Введите левую границу отрезка: ";
					cin >> left_border;
					cout << "Введите правую границу отрезка: ";
					cin >> right_border;
				}
				cout << findsum(root, left_border - 1, right_border - 1, 0) << endl;
			}
			else
				cout << "Дерево ещё не создно '_'\n";
			break;
		case 3:
			if (root != NULL) {
				cout << "Число, на которое мы увеличим отрезок ";
				cin >> variable_for_all;
				while (left_border < 0 || right_border < 0 || left_border > size || right_border > size || left_border > right_border) {
					cout << "Введите левую границу отрезка: ";
					cin >> left_border;
					cout << "Введите правую границу отрезка: ";
					cin >> right_border;
				}
				changeon(root, left_border - 1, right_border - 1, variable_for_all);
			}
			else
				cout << "Дерево ещё не создно '_'\n";
			break;
		case 4:
			if (root != NULL) {
				cout << "Число, на которое мы заменяем отрезок ";
				cin >> variable_for_all;
				while (left_border < 0 || right_border < 0 || left_border > size || right_border > size || left_border > right_border) {
					cout << "Введите левую границу отрезка: ";
					cin >> left_border;
					cout << "Введите правую границу отрезка: ";
					cin >> right_border;
				}
				changeto(root, left_border - 1, right_border - 1, variable_for_all);
			}
			else
				cout << "Дерево ещё не создно '_'\n";
			break;
		case 5:
			if (root != NULL)
				root = delete_tree(root);
			else
				cout << "Дерево ещё не создно '_'\n";
			break;
		case 6:
			if (root != NULL)
				root = delete_tree(root);
			return 0;
		default:
			cout << "Эта функция будет добавлена в следующем обновлении!\n";
		}
		
	}
	return 0;
}