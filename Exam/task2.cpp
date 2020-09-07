#include <iostream>

using namespace std;

struct linkedList
{
	int data;
	linkedList* prev;
	linkedList* next;
};
linkedList* createList()
{
	linkedList* head = new linkedList;
	linkedList* l1 = new linkedList;
	linkedList* l2 = new linkedList;
	linkedList* l3 = new linkedList;
	linkedList* l4 = new linkedList;
	linkedList* l5 = new linkedList;
	head->data = 1; 
	l1->data = 2;   
	l2->data = 1;	
	l3->data = 2;	
	l4->data = 1;	
	l5->data = 2;	
	head->next = l1;
	head->prev = l5;
	l1->next = l2;
	l1->prev = head;
	l2->next = l3;
	l2->prev = l1;
	l3->next = l4;
	l3->prev = l2;
	l4->next = l5;
	l4->prev = l3;
	l5->next = head;
	l5->prev = l4;
	return head;
}
void print(linkedList* head)
{
	if (head == nullptr)
		return;
	linkedList* ptr = head;
	cout << ptr->data << " ";
	ptr = ptr->next;
	while (ptr != head)
	{
		cout << ptr->data << " ";
		ptr = ptr->next;
	}
}
int cntElements(linkedList* head)
{
	int cnt = 1;
	linkedList* temp = head;
	temp = temp->next;
	while (temp != head)
	{
		cnt++;
		temp = temp->next;
	}
	return cnt;
}
void eraseUnnecessary(linkedList*& head,int cnt)
{
	int cloningCnt = cnt;
	linkedList* temp = head;
	while (cnt > 0)
	{
		if (head->data == head->next->data + head->prev->data)
		{
			temp = head;
			head = head->next;
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			delete temp;
			cloningCnt--;
			cnt = cloningCnt;
		}
		else
		{
			head = head->next;
			cnt--;
		}
	}
}
int main()
{
	linkedList* head = createList();
	int cnt = cntElements(head);
	eraseUnnecessary(head,cnt);
	print(head);
	return 0;
}