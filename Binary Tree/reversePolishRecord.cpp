#include <iostream>
#include <string>
#include <stack>
using namespace std;
struct node
{
	string data;
	node* left;
	node* right;
	node(string _data, node* _left = nullptr, node* _right = nullptr)
		: data(_data), left(_left), right(_right) {}
};
string getOperationOrDigit(string& polishRecord, int& index)
{
	string temp = "";
	while (polishRecord[index] != ' ' && index != polishRecord.size())
	{
		temp += polishRecord[index++];
	}
	if (index != polishRecord.size())
		index++;
	return temp;
}
void createTree(node*& root,string polishRecord,int& index,string temp)
{
	if (temp[0] >= '0' && temp[0] <= '9')
	{
		return;
	}
	temp = getOperationOrDigit(polishRecord, index);
	root = new node(temp);
	createTree(root->left, polishRecord, index,  temp);
	createTree(root->right, polishRecord, index, temp);
}
void del(node*& root)
{
	if (root == nullptr)
	{
		return;
	}
	del(root->left);
	del(root->right);
	delete root;
}
bool isOperation(string c)
{
	return c[0] == '*' || c[0] == '/' || c[0] == '-' || c[0] == '+';
}
bool isDigit(string c)
{
	return c[0] >= '0' && c[0] <= '9';
}
void printWithBrackets(node* root)
{
	if (root == nullptr)
		return;
	if (isOperation(root->data))
		cout << "(";
	printWithBrackets(root->left);
	cout << root->data;
	printWithBrackets(root->right);
	if (isOperation(root->data))
		cout << ")";
}
void print(node* root)
{
	if (root == nullptr)
		return;
	print(root->left);
	print(root->right);
	cout << root->data << " ";
}
void collectElementsInStacks(node* root, stack<string>& digits, stack<string>& operations)
{
	if (root == nullptr)
		return;
	if (isOperation(root->data))
		operations.push(root->data);
	if (isDigit(root->data))
		digits.push(root->data);
	collectElementsInStacks(root->left, digits, operations);
	collectElementsInStacks(root->right, digits, operations);
}
void sum(stack<string> digits, stack<string> operations)
{
	
}
int main()
{
	//string polishRecord = "* - 51 24 3";
	//string polishRecord = "- * + 51 24 3 * 48 79";
	string polishRecord = "- 51 * 24 3";
	string temp = "";
	int index = 0;
	node* root = nullptr;
	createTree(root, polishRecord, index, temp);
	//printWithBrackets(root);
	stack<string> digits;
	stack<string> operations;
	collectElementsInStacks(root, digits, operations);
	del(root);
	return 0;
}