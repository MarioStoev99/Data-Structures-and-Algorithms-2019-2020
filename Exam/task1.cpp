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
node* createTree()
{
	     node* l1 = new node(1),
		* l3 = new   node(3),
		* l7 = new   node(7),
		* n4 = new   node(4, l3, nullptr),
		* n2 = new   node(2, l1, n4),
		* n8 = new   node(8, l7, nullptr),
		* root = new node(5, n2, n8);

	return root;
}
int findAdjacentVerteces(node* root, int a, int b)
{
	if (root == nullptr)
		return 0;
	int sum = 0;
	if (root->data >= a && root->data <= b)
		sum++;
	if(root->data > a)
		 sum += findAdjacentVerteces(root->left, a, b);
	if(root->data < b)
		sum += findAdjacentVerteces(root->right, a, b);
	return sum;
}
int multi(node* root,int a,int b)
{
	if (root == nullptr)
		return 1;
	int sum = 1;
	int numberOfLeftSumTree = findAdjacentVerteces(root->left, a, b);
	int numberOfRightSumTree = findAdjacentVerteces(root->right, a, b);
	if ((numberOfLeftSumTree + numberOfRightSumTree) % 2 == 0)
		sum *= root->data;
	sum *= multi(root->left, a, b);
	sum *= multi(root->right, a, b);
	return sum;
}
int main()
{
	node* root = createTree();
	cout << multi(root, 0, 5);
	return 0;
}