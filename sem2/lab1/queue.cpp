//���������� �������
#include "queue.h"
#include<iostream>
using namespace std;

//������� ����������

Node* insert(Node* begin, int number, int priority) {
	Node* newNode = new Node; //��������� �������� ������
	newNode->number = number;  // �������������� ����
	newNode->priority = priority;
	if (begin == NULL || begin->priority < priority) { //������ ������� ������
		newNode->next = begin;//������ ���������
		return newNode;// ����� ������� ������ � ����� ������� �����������
	}
	else { //������ ��������� � ������
		Node* t = begin; //��������� ��������� �� ������� ������
		//���� ������� ��� ������ ����
		while (t->next != NULL && t->next->priority >= priority) {
			t = t->next;
		}
		newNode->next = t->next;
		t->next = newNode;
	}
	return begin;
}

//������� ��������� �������
void View(Node* begin) {
	Node* t = begin;
	while (t != NULL) {
		cout << "������� (��� ���������) : " << t->number << " (" << t->priority << ") " << endl;
		t = t->next;
	}
}

// ������� �������� �������� � ��������� �����������
Node* remove(Node* begin) {
	if (begin == NULL) {
		cout << "������� �����!" << endl;
		return NULL;
	}
	Node* temp = begin;
	begin = begin->next;//���������� ��������� �� ��������� �������
	int number = temp->number;
	int priority = temp->priority;
	delete temp;
	cout << "��������� ������� (��� ���������) : " << number << " (" << priority << ") " << endl;
	return begin;
}