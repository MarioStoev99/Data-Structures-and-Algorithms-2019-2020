#include <iostream>
#include <list>
#include <string>
using namespace std;
void init(unsigned& n, unsigned& m)
{
	do
	{
		cin >> n;
	} while (n <= 0);
	do
	{
		cin >> m;
	} while (m <= 0);
	char c;
	cin.get(c);
}
void initLinkedList(list<string>& l,unsigned n)
{
	for (int i = 0; i < n; i++)
	{
		string temp;
		getline(cin, temp);
		l.push_back(temp);
	}
}
void erasePeople(list<string>& l,unsigned m)
{
	list<string>::iterator it = l.begin();
	while (l.size() != 1)
	{
		for (int k = 0; k < m; k++)
		{
			it++;
			if (it == l.end())
				it = l.begin();
		}
		it = l.erase(it);
		if (it == l.begin())
			it = l.end();
		it--;
	}
	cout << "The winner is : "<< *it;
}
int main()
{
	list<string> l;
	unsigned n, m;
	init(n, m);
	initLinkedList(l, n);
	erasePeople(l, m);
	return 0;
}