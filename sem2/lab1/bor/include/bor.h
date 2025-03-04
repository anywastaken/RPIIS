#pragma once

#include <iostream>
#include <vector>


class Bor {
private:
	struct BorNode {
		std::vector<BorNode*> children;
		bool WordEnd;
		BorNode() : children(26, NULL), WordEnd(false){} 
	};
	BorNode* root;
	void delBor(BorNode* node);
	int Index(char ch) const;
	bool removeHelper(BorNode* root, const std::string& word, int depth);
public:
	Bor();
	~Bor();

	void insert(const std::string& word);
	bool search(const std::string& word) const;
	void remove(const std::string& word);
};
void menu();