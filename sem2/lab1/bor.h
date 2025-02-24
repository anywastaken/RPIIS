#pragma once
#include "Node.h"
#include <string>
using namespace std;

void add_string(string, Node*);

int delete_string(string s, Node* root);

void recursive(Node* current, string word);

void view_bor(Node* root);

int search_string(string s, Node* root);

void delete_bor(Node*);
