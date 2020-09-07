#include <iostream>
#include <list>

using namespace std;
typedef void (*Predicate)(int&);
void isEven(int& x)
{
	x *= x;
}
void filter(list<int>& l, Predicate function)
{
	list<int>::iterator it = l.begin();
	for (list<int>::iterator it = l.begin(); it != l.end(); it++)
	{
		function(*it);
	}
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
	filter(l, isEven);
	print(l);
	return 0;
}