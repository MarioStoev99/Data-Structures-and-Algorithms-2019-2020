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
	node* l10 = new node(3);
	node* l9 = new node(4);
	node* l8 = new node(4);
	node* l7 = new node(3);
	node* l6 = new node(0, nullptr,l10);
	node* l5 = new node(2, l9);
	node* l4 = new node(2, nullptr, l8);
	node* l3 = new node(0, l7);
	node* l2 = new node(1, l5, l6);
	node* l1 = new node(1,l3,l4);
	node* root = new node(3, l1, l2);
	return root;
}
void print(node* root)
{
	if (root == nullptr)
		return;
	cout << root->data << " ";
	print(root->left);
	print(root->right);
}
void deleteRoot(node* root)
{
	if (root == nullptr)
		return;
	deleteRoot(root->left);
	deleteRoot(root->right);
	delete root;
}
bool isSymetrical(node* lhs,node* rhs)
{
	if (lhs == nullptr && rhs == nullptr)
		return true;
	if (lhs != nullptr && rhs == nullptr)
		return false;
	if (lhs == nullptr && rhs != nullptr)
		return false;
	//cout << "result : " << lhs->data << " == " << rhs->data << endl;
	return lhs->data == rhs->data && isSymetrical(lhs->left, rhs->right) && isSymetrical(lhs->right, rhs->left);
}
int main()
{
	node* root = createTree();
	cout << isSymetrical(root,root);
	deleteRoot(root);
	return 0;
}