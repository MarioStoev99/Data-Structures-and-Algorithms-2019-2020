#include <iostream>
#include <list>

using namespace std;
void init(list<int>& l)
{
	int size = 0;
	cout << "enter the number of elements : ";
	cin >> size;
	for (int i = 0; i < size; i++)
	{
		int temp;
		cin >> temp;
		l.push_back(temp);
	}
}
void print(list<int> l)
{
	for (list<int>::iterator it = l.begin(); it != l.end(); it++)
	{
		cout << *it << " ";
	}
}
list<int> append(list<int> l1, list<int> l2)
{
	list<int> l3;
	for (list<int>::iterator it = l1.begin(); it != l1.end(); it++)
		l3.push_back(*it);
	for (list<int>::iterator it = l2.begin(); it != l2.end(); it++)
		l3.push_back(*it);
	return l3;
}
int main()
{
	list<int> l1;
	init(l1);
	list<int> l2;
	init(l2);
	list<int> l3 = append(l1, l2);
	print(l3);
	return 0;
}