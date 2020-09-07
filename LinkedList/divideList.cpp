#include <iostream>
#include <list>

using namespace std;

bool isEven(int x)
{
	return x % 2 == 0;
}
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
list<int> divideList(list<int>& l)
{
	list<int> l2;
	for (list<int>::iterator it = l.begin(); it != l.end(); it++)
	{
		if(isEven(*it))
		l2.push_back(*it);
	}
	for (list<int>::iterator it = l.begin(); it != l.end(); it++)
	{
		if (!isEven(*it))
			l2.push_back(*it);
	}
	return l2;
}
int main()
{
	list<int> l;
	init(l);
	list<int> l2 = divideList(l);
	print(l2);
	return 0;
}