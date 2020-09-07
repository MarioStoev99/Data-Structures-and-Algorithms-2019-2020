#include <iostream>

using namespace std;

template<typename T>
struct node
{
	T data;
	node* next;
	node(T _data,node* _next = nullptr) : data(_data),next(_next) {}
};
template<typename T = int>
node<T>* createList()
{
	node<T>* l1 = new node<T>(0);
	node<T>* l2 = new node<T>(1);
	node<T>* l3 = new node<T>(1);
	node<T>* l4 = new node<T>(2);
	node<T>* l5 = new node<T>(3);
	node<T>* l6 = new node<T>(5);
	node<T>* l7 = new node<T>(8);
	node<T>* l8 = new node<T>(13);
	node<T>* l9 = new node<T>(21);
	node<T>* l10 = new node<T>(34);
	node<T>* l11 = new node<T>(55);
	l1->next = l2;
	l2->next = l3;
	l3->next = l4;
	l4->next = l5;
	l5->next = l6;
	l6->next = l7;
	l7->next = l8;
	l8->next = l9;
	l9->next = l10;
	l10->next = l11;
	l11->next = nullptr;
	return l1;
}
template<typename T>
void reverseElements(node<T>* l, node<T>*& newList)
{
	if (l == nullptr)
		return;
	reverseElements(l->next, newList);
	newList = new node<T>(l->data);
	cout << l->data << " ";
	newList = newList->next;
}
template<typename T>
node<T>* reverseFib(node<T>* l)
{
	bool flag = true;
	node<T>* temp = l;
	node<T>* temp1 = temp->next;
	node<T>* temp2 = temp1->next;
	while (temp2 != nullptr)
	{
		if (temp->data + temp1->data != temp2->data)
		{
			flag = false;
			break;
		}
		temp2 = temp2->next;
		temp1 = temp1->next;
		temp = temp->next;
	}
	//cout << flag << endl;
	node<T>* newList = nullptr;
	if (flag)
	{
		reverseElements(l, newList);
		return newList;
	}
	else
		return newList;
}
template<typename T>
void print(node<T>* l)
{
	while (l != nullptr)
	{
		cout << l->data << " ";
		l = l->next;
	}
}
int main()
{
	node<int>* head = createList();
	node<int>* list = reverseFib(head);
	print(list);
	return 0;
}