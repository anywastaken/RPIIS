#include "RSQ.h"
int min(int a, int b)
{
	return a < b ? a : b;
}
int max(int a, int b)
{
	return a > b ? a : b;
}
rsq* creatersq(int left_border, int right_border, std::vector<int> array)
{
	rsq* root = (rsq*) malloc(sizeof(rsq));
	root->left_border = left_border;
	root->right_border = right_border;
	root->add = 0;
	if (left_border < right_border)
	{
		root->left = creatersq(left_border, (left_border + right_border) / 2, array);
		root->right = creatersq((left_border + right_border) / 2 + 1, right_border, array);
	}
	else {
		root->left = NULL;
		root->right = NULL;
	}
	if (left_border == right_border)
		root->sum = array[right_border];
	else
		root->sum = root->left->sum + root->right->sum;
	return root;
}

int findsum(rsq* root, int left_border, int right_border, int sum) {
	if (root->left_border == left_border && root->right_border == right_border)
		sum += root->sum + root->add;
	else {
		sum += root->add / (root->right_border - root->left_border + 1);
		if (left_border <= root->left->right_border)
			sum = findsum(root->left, left_border, min(right_border, root->left->right_border), sum);
		if (right_border >= root->right->left_border)
			sum = findsum(root->right, max(left_border, root->right->left_border), right_border, sum);
	}
	return sum;
}

void changeon(rsq* root, int left_border, int right_border, int changing)
{
	if (root->left_border == left_border && root->right_border == right_border) 
		root->add += changing * (right_border - left_border + 1);
		
	else
	{
		if (left_border <= root->left->right_border)
			changeon(root->left, left_border, min(right_border, root->left->right_border), changing);

		if (right_border >= root->right->left_border)
			changeon(root->right, max(left_border,root->right->left_border), right_border, changing);

		root->sum = root->left->sum + root->left->add + root -> right->sum + root->right->add;
	}
}
void changeto(rsq* root, int left_border, int right_border, int neu)
{
	if (root->left_border == root->right_border) {
		root->add = neu - root->sum;
	}
	else
	{
		neu -= root->add / (root->right_border - root->left_border + 1);
		if (left_border <= root->left->right_border)
			changeto(root->left, left_border, min(right_border, root->left->right_border), neu);

		if (right_border >= root->right->left_border)
			changeto(root->right, max(left_border, root->right->left_border), right_border, neu);

			root->sum = root->left->sum + root->left->add + root->right->sum + root->right->add;
	}
}
rsq* delete_tree(rsq* root) {
	if (root != NULL) {
		delete_tree(root->left);
		delete_tree(root->right);
		free(root);
	}
	root = NULL;
	return root;
}