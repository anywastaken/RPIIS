#include <iostream>
#include "Node.h";
#include "bor.h";
using namespace std;

void add_string(string s, Node* root) {
	Node* current = root; //��������� �� ������� ����, �������� � ����� ����
	Node* ptr; //��������� ��� �������� �������� �����
	bool find; //����������, ������������, ������ �� ���� � ��������������� ��������
	for (int i = 0; i < s.size(); i++) { //������� ������
		find = false;
		for (int j = 0; j < current->front_ptrs.size(); j++) { //������� ��������� �������� ����
			ptr = current->front_ptrs[j]; // ��������� �� ������� �������� ����
			if (ptr != nullptr) {
				if (s[i] == ptr->c) { //���� ����� �������� ������ ����, ���������� ������� ������ ������, ������ ��������� �� ���� 
					current = current->front_ptrs[j]; //��������� ��������� current �� ��������� ����
					find = true;
					break;
				}
			}
		}
		if (find == false) { //���� �� ������, ������ ����� ����
			if (current->front_ptrs[0] == nullptr) //���� ��� �������� �����
				current->front_ptrs[current->num] = new Node(s[i]); //������� ����� ���� � �������� s[i] � �������� ��� � front_ptrs �� ������� current->num
			else
				current->front_ptrs.push_back(new Node(s[i])); //��������� ����� ���� � ����� front_ptrs
			current->num++; //����������� ���������� �������� �����
			ptr = current->front_ptrs[current->num - 1];//��������� ptr ��������� �� ����������� ����
			ptr->back_ptr = current;
			current = current->front_ptrs[current->num - 1];
		}
		if (i == s.size() - 1)
			current->terminal = true;
	}
}

int delete_string(string s, Node* root) {
	Node* current = root;
	Node* ptr; //��������� ��� �������� �������� �����
	bool find = false; //����������, ������������, ������ �� ���� � ��������������� ��������
	for (int i = 0; i < s.size(); i++) { //������� ������
		for (int j = 0; j < current->front_ptrs.size(); j++) { //������� ��������� �������� ����
			ptr = current->front_ptrs[j]; //������������� ��������� ptr �� ������� �������� ����
			if (ptr == nullptr) {
				cout << "������ �� �������" << endl << endl;
				return 1;
			}
			if (s[i] == ptr->c) { //���� ������ ��������� � �������� �������� ����
				current = current->front_ptrs[j]; //���������� ��������� current �� �������� ����, ��������������� ���������� �������.
				find = true;
				break;
			}
		}
		if (find == false) {
			cout << "������ �� �������" << endl << endl;
			return 1;
		}
	}
	if (current->terminal != true) { //���� ���� � ��������� �������� ������ �� ������� ��� ����� �����, �����, ��� ������ � ���� ���, ��������� �������
		cout << "������ �� �������" << endl << endl;
		return 1;
	}
	for (int i = s.size() - 1; i >= 0; i--) { //������� ������ � �����
		if ((current->num < 1 && current->terminal == false) || (i == s.size() - 1 && current->num < 1)) { //���� ������� ���� �� ����� �������� ����� ������ ��������� � �� �������� ������ ������� ����� ��� ���� ��� ��������� ������ ������ � �� ����� ������ ��������, �� ������� ���
			current = current->back_ptr; //��������� �� ������������ ����
			for (int j = 0; j < current->front_ptrs.size(); j++) { //���� ����� �������� ����, ������������ ���, ������� ��� � ���������, ����������� �� ���� �� �������
				ptr = current->front_ptrs[j];
				if (s[i] == ptr->c) {
					delete current->front_ptrs[j];
					current->front_ptrs.erase(current->front_ptrs.begin() + j);//������� ��������� �� ���� ���� �� ���������� front_ptrs ������
					break;
				}
			}
			current->num--; //��������� ������� �������� ����� �� 1, �.�. ���� �� �������
		}
		else { //�����, ���� ������, �� ���������� ��� �������, �������� ��������� � ������, ������� ��� ������ ���������� ������� � ������ � ��������� �������
			if (i == s.size() - 1)
				current->terminal = false;
			break;
		}
	}
	
	return 0;
}

void recursive(Node* current, string word) {
	for (int i = 0; i < current->front_ptrs.size(); i++) { //������� ���� �������� �������� ����
		if (current->front_ptrs[i] != nullptr) { //���� i-��� ������� �� ����� nullptr
			current = current->front_ptrs[i]; //��������� �� ���� � ���� ��� �� ������, ���������� ��� ������ � ����� word, � ���� �� ������������, �������  word
			if (current->is_root == false) {
				word.push_back(current->c);
				if (current->terminal == true) {
					cout << word << endl;
				}
			}
			recursive(current, word);
		}
	}
}

void view_bor(Node* root){
	Node* current = root->back_ptr; //��������� �� ���� ����� ������
	string word;
	recursive(current, word); //������� ���� ���� � ����������� �������
	cout << endl;
}

int search_string(string s, Node* root) {
	Node* current = root;
	Node* ptr;
	bool find = false;
	for (int i = 0; i < s.size(); i++) {
		for (int j = 0; j < current->front_ptrs.size(); j++) { //������� �������� ���� (���������) �������� ����
			ptr = current->front_ptrs[j];
			if (ptr == nullptr) {
		
				return 1;
			}
			if (s[i] == ptr->c) {
				current = current->front_ptrs[j];
				find = true;
				break;
			}
		}
		if (find == false) {
			
			return 1;
		}
	}
	if (current->terminal == true) { //����� �� ������ �� ����� ����� � ����� �� ���������� �������, ���� �� ������������ �� ������ �������
		return 0;
	}
	else {
		
		return 1;
	}
}

void delete_bor(Node* root) {
	if (root != nullptr)
		for (int i = 0; i < root->front_ptrs.size(); i++) {
			if (root->front_ptrs[i]) { //���� ������� ����������, ���������� ����� ��������� ��� �������
				delete_bor(root->front_ptrs[i]);
			}
		}
	delete root; //����������� ������ ��� ��������� ���� ����� �������� ���� ���������
	
}

