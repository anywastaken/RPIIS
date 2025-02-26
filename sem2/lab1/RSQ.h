#pragma once
#include <vector>
int min(int a, int b);
int max(int a, int b);
struct rsq {
	int left_border;
	int right_border;
	int sum;
	int add;
	rsq* left;
	rsq* right;
};
rsq* creatersq(int left_border, int right_border, std::vector<int> array);
int findsum(rsq* root, int left_border, int right_border, int sum);
void changeon(rsq* root, int left_border, int right_border, int changing);
void changeto(rsq* root, int left_border, int right_border, int neu);
rsq* delete_tree(rsq* root);