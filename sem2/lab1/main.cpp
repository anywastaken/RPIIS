#include <iostream>
#include "queue.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "ru");
	Node* begin = NULL; //инициализация 
	int elements, number, priority;
	cout << "Введите кол-во элементов для добавления в очередь: ";
	cin >> elements;
	for (int i = 0; i < elements; i++) {
		cout << "Введите число и приоритет этого числа через пробел: ";
		cin >> number >> priority;
		begin = insert(begin, number, priority);
	}
	if (begin != NULL) {
		cout << "Очередь: " << endl;
		View(begin);
	}
	// Удаление элементов и вывод их значений
	cout << "Удаленные элементы:" << endl;
	while (begin != NULL) {
		begin = remove(begin);
	}
	if (begin == NULL) {
		cout << "Очередь пуста." << endl;
	}
	return 0;
}

