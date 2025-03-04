#pragma once
//прототип функции

struct Node {
	int number;
	int priority;
	Node* next;
};


Node* insert(Node* begin, int number, int priority);
void View(Node* begin);
Node* remove(Node* begin);