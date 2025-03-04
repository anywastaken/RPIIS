//реализация функции
#include "queue.h"
#include<iostream>
using namespace std;

//Функция добавления

Node* insert(Node* begin, int number, int priority) {
	Node* newNode = new Node; //правильно выделяем память
	newNode->number = number;  // инициализируем поля
	newNode->priority = priority;
	if (begin == NULL || begin->priority < priority) { //меняем вершину списка
		newNode->next = begin;//меняем указатель
		return newNode;// новая вершина списка с более высоким приоритетом
	}
	else { //просто вставляем в список
		Node* t = begin; //временный указатель на вершину списка
		//Ищем позицию для нового узла
		while (t->next != NULL && t->next->priority >= priority) {
			t = t->next;
		}
		newNode->next = t->next;
		t->next = newNode;
	}
	return begin;
}

//Функция просмотра очереди
void View(Node* begin) {
	Node* t = begin;
	while (t != NULL) {
		cout << "Элемент (его приоритет) : " << t->number << " (" << t->priority << ") " << endl;
		t = t->next;
	}
}

// Функция Удаление элемента с наивысшим приоритетом
Node* remove(Node* begin) {
	if (begin == NULL) {
		cout << "Очередь пуста!" << endl;
		return NULL;
	}
	Node* temp = begin;
	begin = begin->next;//перемещаем указатель на следующий элемент
	int number = temp->number;
	int priority = temp->priority;
	delete temp;
	cout << "Удаленный элемент (его приоритет) : " << number << " (" << priority << ") " << endl;
	return begin;
}