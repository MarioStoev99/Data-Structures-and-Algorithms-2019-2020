#include <iostream>
#include <cmath>
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
	node* l6 = new node(6);
	node* l5 = new node(5);
	node* l4 = new node(4, nullptr,l5);
	node* l3 = new node(3,l6);
	node* l2 = new node(2, l4);
	node* l1 = new node(1, l2, l3);
	return l1;
}
void del(node* root)
{
	if (root == nullptr)
		return;
	del(root->left);
	del(root->right);
	delete root;
}
int getChildren(node* child)
{
	int sum = 0;
	if (child == nullptr)
		return 0;
	else
		sum++;
	sum += getChildren(child->left) + getChildren(child->right);
}
bool isPerfectlyBalancedTree(node* root)
{
	if (root == nullptr)
		return true;
	int LeftRoot =  getChildren(root->left);
	int RightRoot = getChildren(root->right);
	if (abs(LeftRoot - RightRoot) > 1)
	{
		cout << root->data << endl;
		return false;
	}
	return isPerfectlyBalancedTree(root->left) && isPerfectlyBalancedTree(root->right);
}
int main()
{
	node* root = createTree();
	cout << isPerfectlyBalancedTree(root);
	return 0;
}