#include <iostream>
#include <list>
using namespace std;

/*
Нека имаме едносвързан списък от цели числа представен чрез поредица от свързани
елементи от типа:
struct ListNode
{
int data;
ListNode *next;
}
Да се реализира функцията bool containsCycle(ListNode *start), на която се подава
указател към елемент наречен start, който се приема за начало на списъка. Функцията
containsCycle проверява дали елементите на списъка са свързани по такъв начин, че да
се формира цикъл.
*/
struct node
{
	int data;
	node* next;
};
node* createList()
{
	node* head = new node;
	node* l1 =   new node;
	node* l2 =   new node;
	node* l3 =   new node;
	head->data = 1;
	l1->data = 2;
	l2->data = 3;
	l3->data = 4;
	head->next = l1;
	l1->next = l2;
	l2->next = l3;
	//l3->next = nullptr;
	l3->next = head;
	return head;
}
node* secondList()
{
	node* head = new node;
	node* l1 = new node;
	node* l2 = new node;
	node* l3 = new node;
	head->data = 1;
	l1->data = 2;
	l2->data = 3;
	l3->data = 4;
	head->next = l1;
	l1->next = l2;
	l2->next = l3;
	l3->next = l2;
	return head;
}
bool member(list<node*>& l, node* current)
{
	for (list<node*>::iterator it = l.begin(); it != l.end(); it++)
	{
		if (*it == current)
		{
			//cout << (*it)->data << " " << current->data << endl;
			return true;
		}
	}
	return false;
}
bool containCycle(node* linkedList)
{
	if (linkedList == nullptr)
		return false;
	list<node*> l;
	node* start = linkedList;
	while (start != nullptr)
	{
		if (member(l, start))
		{
			return true;
		}
		l.push_back(start);
		start = start->next;
	}
	return false;
}
int main()
{
	node* list = secondList();
	cout << containCycle(list);
	return 0;
}