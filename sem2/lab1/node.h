#pragma once
#include <iostream>
#include <vector>
using namespace std;
class Node//����� ��� �������� �������� � ���������� �� ������ ����
{
public:
	vector<Node*> front_ptrs = { nullptr };// ������ ���������� �� �������� ����
	Node* back_ptr;//��������� �� ������������ ����
	char c;//������ � ����
	int num = 0;
	bool is_root = false;//�������� ���� �� ������
	bool terminal = false;

	Node();
	Node(char c);
	Node(Node* p);
};