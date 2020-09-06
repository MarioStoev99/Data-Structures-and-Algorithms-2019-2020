#include <iostream>
#include <queue>
using namespace std;

struct node
{
	int data;
	node* left;
	node* right;
	node(int _data, node* _left = nullptr, node* _right = nullptr)
		: data(_data), left(_left), right(_right) {}
};
node* createTree()
{
	node* l6 = new node(1);
	node* l5 = new node(6);
	node* l4 = new node(7);
	node* l3 = new node(4);
	node* l2 = new node(8, l5, l6);
	node* l1 = new node(3, l3, l4);
	node* root = new node(5, l1, l2);
	return root;
}
int findMaxLeafValue(node* root)
{
	int maxLeafValue = -999;
	if (root == nullptr)
		return 0;
	if (root->left == nullptr && root->right == nullptr)
	{
		if (maxLeafValue < root->data)
			return root->data;
		else return maxLeafValue;
	}
	maxLeafValue = maxLeafValue > findMaxLeafValue(root->left) ? maxLeafValue : findMaxLeafValue(root->left);
	maxLeafValue = maxLeafValue > findMaxLeafValue(root->right) ? maxLeafValue : findMaxLeafValue(root->right);
	return maxLeafValue;
}
int main()
{
	node* root = createTree();
	cout << "max leaf value : " << findMaxLeafValue(root) << endl;
	return 0;
}