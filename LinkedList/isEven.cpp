#include <iostream>
#include <list>

using namespace std;
typedef bool (*Predicate)(int);
bool isEven(int x)
{
	return x % 2 == 0;
}
list<int> filter(list<int>& l,Predicate function)
{
	list<int> newList;
	list<int>::iterator it = l.begin();
	for (list<int>::iterator it = l.begin(); it != l.end(); it++)
	{
		if (function(*it))
			newList.push_back(*it);
	}
	return newList;
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
int main()
{
	list<int> l;
	init(l);
	list<int> newList = filter(l, isEven);
	print(newList);
	return 0;
}