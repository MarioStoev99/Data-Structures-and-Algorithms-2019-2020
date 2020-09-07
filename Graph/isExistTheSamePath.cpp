#include <iostream>
#include <list>
using namespace std;

struct node
{
	char data;
	node* left;
	node* right;
	node(char _data,node* _left = nullptr,node* _right = nullptr) : 
		data(_data),left(_left),right(_right) { }
};
node* createTree()
{
	node* l7 = new node('h');
	node* l6 = new node('b');
	node* l5 = new node('c', l7);
	node* l4 = new node('e');
	node* l3 = new node('d', l6);
	node* l2 = new node('f', nullptr, l5);
	node* l1 = new node('d', l3, l4);
	node* root = new node('a',l1,l2);
	return root;
}
list<list<char>> createGraph()
{
	list<char> l1, l2, l3, l4, l5, l6, l7, l8;
	list<list<char>> graph;
	l1.push_back('g');
	l1.push_back('e');
	l1.push_back('b'); 
	l2.push_back('b');
	l2.push_back('h');
	l3.push_back('a');
	l3.push_back('f');
	l3.push_back('d');
	l4.push_back('d');
	l4.push_back('e');
	l5.push_back('f');
	l5.push_back('c');
	l5.push_back('h');
	l6.push_back('e');
	l6.push_back('h');
	l7.push_back('c');
	l8.push_back('h');
	l7.push_back('h');
	graph.push_back(l1);
	graph.push_back(l2);
	graph.push_back(l3);
	graph.push_back(l4);
	graph.push_back(l5);
	graph.push_back(l6);
	graph.push_back(l7);
	graph.push_back(l8);
	return graph;
}
list<char> getList(int x, list<list<char>>& graph)
{
	list<list<char>>::iterator it = graph.begin();
	list<char>::iterator j = (*it).begin();
	while (*j != x && it != graph.end())
	{
		it++;
		j = (*it).begin();
	}
	return *it;
}
bool isExistTheSamePathinGraph(list<list<char>>& graph,string& str,int rootValue,int index)
{
	if (index == str.size())
		return true;
	list<char> l = getList(rootValue, graph);
	list<char>::iterator it = l.begin();
	it++;
	while (it != l.end())
	{
		if (*it == str[index])
			if (isExistTheSamePathinGraph(graph, str, *it, index + 1))
				return true;
		it++;
	}
	return false;
}
void isExistPath(node* root,string& str,list<list<char>>& l,int rootValue)
{
	if (root == nullptr)
		return;
	else
	{
		str += root->data;
	}
	if (root->left == nullptr && root->right == nullptr)
	{
		if (isExistTheSamePathinGraph(l, str, rootValue, 1))
		{
			cout << str << endl;
			return;
		}
	}
	isExistPath(root->left, str ,l,rootValue);
	isExistPath(root->right, str,l,rootValue);
	str.pop_back();
}
int main()
{
	node* root = createTree();
	list<list<char>> l = createGraph();
	string str;
	isExistPath(root, str,l,root->data);
	return 0;
}