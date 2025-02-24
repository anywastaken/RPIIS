#include <iostream>
#include "Node.h";
#include "bor.h";
using namespace std;

void add_string(string s, Node* root) {
	Node* current = root; //указатель на текущий узел, начинаем с корня бора
	Node* ptr; //указатель для перебора дочерних узлов
	bool find; //переменная, показывающая, найден ли узел с соответствующим символом
	for (int i = 0; i < s.size(); i++) { //обходим строку
		find = false;
		for (int j = 0; j < current->front_ptrs.size(); j++) { //обходим указатели текущего узла
			ptr = current->front_ptrs[j]; // указывает на текущий дочерний узел
			if (ptr != nullptr) {
				if (s[i] == ptr->c) { //если среди потомков найден узел, содержащий текущий символ строки, просто переходим на него 
					current = current->front_ptrs[j]; //обновляем указатель current на найденный узел
					find = true;
					break;
				}
			}
		}
		if (find == false) { //если не найден, создаём новый узел
			if (current->front_ptrs[0] == nullptr) //если нет дочерних узлов
				current->front_ptrs[current->num] = new Node(s[i]); //создаем новый узел с символом s[i] и помещаем его в front_ptrs по индексу current->num
			else
				current->front_ptrs.push_back(new Node(s[i])); //добавляем новый узел в конец front_ptrs
			current->num++; //увеличиваем количество дочерних узлов
			ptr = current->front_ptrs[current->num - 1];//указатель ptr указывает на добавленный узел
			ptr->back_ptr = current;
			current = current->front_ptrs[current->num - 1];
		}
		if (i == s.size() - 1)
			current->terminal = true;
	}
}

int delete_string(string s, Node* root) {
	Node* current = root;
	Node* ptr; //указатель для перебора дочерних узлов
	bool find = false; //переменная, показывающая, найден ли узел с соответствующим символом
	for (int i = 0; i < s.size(); i++) { //обходим строку
		for (int j = 0; j < current->front_ptrs.size(); j++) { //обходим указатели текущего узла
			ptr = current->front_ptrs[j]; //устанавливаем указатель ptr на текущий дочерний узел
			if (ptr == nullptr) {
				cout << "Строка не найдена" << endl << endl;
				return 1;
			}
			if (s[i] == ptr->c) { //если символ совпадает с символом текущего узла
				current = current->front_ptrs[j]; //перемещаем указатель current на дочерний узел, соответствующий найденному символу.
				find = true;
				break;
			}
		}
		if (find == false) {
			cout << "Строка не найдена" << endl << endl;
			return 1;
		}
	}
	if (current->terminal != true) { //если узел с последним символом строки не помечен как конец слова, пишем, что строки в боре нет, завершаем функцию
		cout << "Строка не найдена" << endl << endl;
		return 1;
	}
	for (int i = s.size() - 1; i >= 0; i--) { //обходим строку с конца
		if ((current->num < 1 && current->terminal == false) || (i == s.size() - 1 && current->num < 1)) { //если текущий узел не имеет потомков кроме раннее удалённого и не является концом другого слова или если это последний символ строки и не имеет больше потомков, то удаляем его
			current = current->back_ptr; //переходим на родительский узел
			for (int j = 0; j < current->front_ptrs.size(); j++) { //ищем среди потомков узел, интересующий нас, удаляем его и указатель, указывавший на него из вектора
				ptr = current->front_ptrs[j];
				if (s[i] == ptr->c) {
					delete current->front_ptrs[j];
					current->front_ptrs.erase(current->front_ptrs.begin() + j);//удаляем указатель на этот узел из контейнера front_ptrs предка
					break;
				}
			}
			current->num--; //Уменьшаем счетчик дочерних узлов на 1, т.к. один мы удалили
		}
		else { //иначе, если символ, не подходящий под условия, является последним в строке, убираем его статус последнего символа в строке и завершаем функцию
			if (i == s.size() - 1)
				current->terminal = false;
			break;
		}
	}
	
	return 0;
}

void recursive(Node* current, string word) {
	for (int i = 0; i < current->front_ptrs.size(); i++) { //обходим всех потомков текущего узла
		if (current->front_ptrs[i] != nullptr) { //если i-тый потомок не равен nullptr
			current = current->front_ptrs[i]; //переходим на него и если это не корень, записываем его символ в слово word, а если он терминальный, выводим  word
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
	Node* current = root->back_ptr; //переходим на узел перед корнем
	string word;
	recursive(current, word); //передаём этот узел в рекурсивную функцию
	cout << endl;
}

int search_string(string s, Node* root) {
	Node* current = root;
	Node* ptr;
	bool find = false;
	for (int i = 0; i < s.size(); i++) {
		for (int j = 0; j < current->front_ptrs.size(); j++) { //обходим дочерние узлы (указатели) текущего узла
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
	if (current->terminal == true) { //когда мы прошли по всему слову и дошли до последнего символа, если он терминальный то строка найдена
		return 0;
	}
	else {
		
		return 1;
	}
}

void delete_bor(Node* root) {
	if (root != nullptr)
		for (int i = 0; i < root->front_ptrs.size(); i++) {
			if (root->front_ptrs[i]) { //если потомок существует, рекурсивно снова запускаем для функцию
				delete_bor(root->front_ptrs[i]);
			}
		}
	delete root; //освобождаем память для корневого узла после удаления всех остальных
	
}

