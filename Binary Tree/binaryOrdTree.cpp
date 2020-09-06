#include <iostream>

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
	node* l6 = new node(9);
	node* l5 = new node(6);
	node* l4 = new node(4);
	node* l3 = new node(1);
	node* l2 = new node(8, l5, l6);
	node* l1 = new node(3, l3, l4);
	node* root = new node(5, l1, l2);
	return root;
}
void BinOrdPrint(node* root, int a, int b)
{
	if (root == nullptr)
		return;
	if (root->data >= a && root->data <= b)
		cout << root->data << " ";
	cout << root->data << " ";
	if (root->data > a)
		BinOrdPrint(root->left, a, b);
	if (root->data < b)
		BinOrdPrint(root->right, a, b);
}
int main()
{
	node* root = createTree();
	BinOrdPrint(root, 3, 6);
	return 0;
}