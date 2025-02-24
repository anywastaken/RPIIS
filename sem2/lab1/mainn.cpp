#include <iostream>
#include <string>
#include "Node.h"; 
#include "bor.h";
using namespace std;

void test1() {
	Node* root = new Node();
	root->back_ptr = new Node(root);

	add_string("hello", root);
	add_string("hoho", root);
	add_string("hi", root);


	cout << "Проверка наличия строк:" << endl;
	cout << "hello: " << (search_string("hello", root) == 0 ? "найдена" : "не найдена") << endl;
	cout << "hoho: " << (search_string("hoho", root) == 0 ? "найдена" : "не найдена") << endl;
	cout << "hi: " << (search_string("hi", root) == 0 ? "найдена" : "не найдена") << endl;
	cout << "test: " << (search_string("test", root) == 0 ? "найдена" : "не найдена") << endl; // Не добавляли

	delete_bor(root);
	cout << "Бор удален" << endl << endl;

}
void test2() {
	Node* root = new Node();
	root->back_ptr = new Node(root);

	add_string("pioivis", root);
	add_string("president", root);
	add_string("pinsk", root);

	cout << "Проверка наличия строк:" << endl;
	cout << "pioivis: " << (search_string("pioivis", root) == 0 ? "найдена" : "не найдена") << endl;
	cout << "president: " << (search_string("president", root) == 0 ? "найдена" : "не найдена") << endl;
	cout << "pinsk: " << (search_string("pinsk", root) == 0 ? "найдена" : "не найдена") << endl << endl;

	delete_string("president", root);

	cout << "Проверка наличия строк:" << endl;
	cout << "pioivis: " << (search_string("pioivis", root) == 0 ? "найдена" : "не найдена") << endl;
	cout << "president: " << (search_string("president", root) == 0 ? "найдена" : "не найдена") << endl;
	cout << "pinsk: " << (search_string("pinsk", root) == 0 ? "найдена" : "не найдена") << endl << endl;

	delete_bor(root);
	cout << "Бор удален" << endl << endl;
	
}


void test3() {
	Node* root = new Node();
	root->back_ptr = new Node(root);

	add_string("cambridge", root);
	add_string("carrot", root);

	cout << "Содержимое бора:" << endl;
	view_bor(root); 

	delete_bor(root);
	cout << "Бор удален" << endl << endl;
	
}

void test4() {
	Node* root = new Node();
	root->back_ptr = new Node(root);

	add_string("bus", root);
	add_string("soap", root);
	add_string("burn", root);

	cout << "Содержимое бора:" << endl;
	view_bor(root);

	delete_string("bus", root);

	cout << "Строка bus: " << (search_string("pioivis", root) == 0 ? "найдена" : "не найдена") << endl;

	cout << "Содержимое бора:" << endl;
	view_bor(root);


	delete_bor(root);
	cout << "Бор удален" << endl << endl;
}


int main(){
	setlocale(LC_ALL, "ru");

	test1();
	test2();
	test3();
	test4();

	return 0;
}