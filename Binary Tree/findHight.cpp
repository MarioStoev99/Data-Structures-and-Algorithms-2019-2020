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
	//node* l5 = new node(5);
	node* l4 = new node(4, nullptr);
	node* l3 = new node(3);
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
int findHight(node* root)
{
	if (root == nullptr)
		return 0;
	int hight = 0;
	node* temp = new node(-1);
	queue<node*> q;
	q.push(root);
	q.push(temp);
	while (true)
	{
		node* temp = q.front();
		q.pop();
		cout << temp->data << " ";
		if (temp->data == -1)
		{
			hight++;
			if (q.empty())
				return hight;
			q.push(temp);
		}
		if (temp->left != nullptr)
			q.push(temp->left);
		if (temp->right != nullptr)
			q.push(temp->right);
	}
}
int main()
{
	node* root = createTree();
	cout << findHight(root);
	return 0;
}