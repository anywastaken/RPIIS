#include "D:\Code\Visual Studio\Projects\bor\include\bor.h"
Bor::Bor() {
	root = new BorNode;
}
Bor::~Bor() {
	delBor(root);
}
void Bor::insert(const std::string& word) {
	BorNode* node = root;
	for (char ch : word) {
		int index = Index(ch);
		if (!node->children[index]) {
			node->children[index] = new BorNode;
		}
		node = node->children[index];
	}
	node->WordEnd = true;
}
bool Bor::search(const std::string& word) const {
	BorNode* node = root;
	for (char ch : word) {
		int index = Index(ch);
		if (!node->children[index]) {
			return false;
		}
		node = node->children[index];
	}
	return node->WordEnd;
}
void Bor::delBor(BorNode* node) {
	for (BorNode* child : node->children) {
		if (child != NULL) {
			delBor(child);
		}
	}
	delete node;
}
bool Bor::removeHelper(BorNode* node, const std::string& word, int depth) {
	if (!node) return false;
	if (depth == word.size()) {
		if (!node->WordEnd) return false; 

		node->WordEnd = false;
		return node->children.empty(); 
	}

	int index = Index(word[depth]);
	if (index == -1 || !node->children[index]) return false;

	bool shouldDeleteChild = removeHelper(node->children[index], word, depth + 1);

	if (shouldDeleteChild) {
		delete node->children[index];
		node->children[index] = NULL;
		return node->children.empty() && !node->WordEnd;
	}

	return false;
}

void Bor::remove(const std::string& word) {
	removeHelper(root, word, 0);
}

int Bor::Index(char ch) const {
	if (ch >= 'a' && ch <= 'z') return ch - 'a';      
	if (ch >= 'A' && ch <= 'Z') return ch - 'A';       
	return -1; 
}

void menu() {
	Bor bor;
	int sel;
	std::string word;
	while (true) {
		std::cout << "Select option: " << std::endl;
		std::cout << "1. Add string" << std::endl;
		std::cout << "2. Search string" << std::endl;
		std::cout << "3. Remove string" << std::endl;
		std::cout << "4. Exit" << std::endl;
		std::cin >> sel;
		switch (sel)
		{
		case 1: {
			std::cout << "Enter string: ";
			std::cin >> word;
			bor.insert(word);
			break;
		}
		case 2: {
			std::cout << "Enter string: ";
			std::cin >> word;
			if (bor.search(word)) {
				std::cout << "The word is exists in the bor." << std::endl;
			}
			else {
				std::cout << "The word does not exist in the bor." << std::endl;
			}
			break;
		}
		case 3: {
			std::cout << "Enter string: ";
			std::cin >> word;
			bor.remove(word);
			std::cout << "Word removed.";
			break;
		}
		case 4: {
			return;
		}
		default:
			std::cout << "Incorrect option";
			break;
		}
	}
}