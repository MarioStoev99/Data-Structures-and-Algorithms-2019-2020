#include <iostream>

using namespace std;
struct node
{
	int data;
	node* left;
	node* right;
	node(int _data,node* _left = nullptr,node* _right = nullptr)
		: data(_data),left(_left),right(_right) {}
};
node* createTree1()
{
	node* l6 = new node(13);
	node* l5 = new node(10);
	node* l4 = new node(9);
	node* l3 = new node(8);
	node* l2 = new node(7,l5,l6);
	node* l1 = new node(6,l3,l4);
	node* root = new node(5,l1,l2);
	return root;
}
node* createTree2()
{
	node* l6 = new node(15);
	node* l5 = new node(20);
	node* l4 = new node(9);
	node* l3 = new node(11);
	node* l2 = new node(7, l5, l6);
	node* l1 = new node(6, l3, l4);
	node* root = new node(5, l1, l2);
	return root;
}
node* createInsection(node* root1, node* root2)
{
	if (root1 == nullptr || root2 == nullptr)
		return nullptr;
	node* newTree = nullptr;
	if (root1->data == root2->data)
	{
		newTree = new node(root1->data);
		newTree->left = createInsection(root1->left, root2->left);
		newTree->right = createInsection(root1->right, root2->right);
	}
	return newTree;
}
void print(node* root)
{
	if (root == nullptr)
		return;
	print(root->left);
	cout << root->data << " ";
	print(root->right);
}
int main()
{
	node* root1 = createTree1();
	node* root2 = createTree2();
	node* root3 = createInsection(root1, root2);
	print(root3);
	return 0;
}