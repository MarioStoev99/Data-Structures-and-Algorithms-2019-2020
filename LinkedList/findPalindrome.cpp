#include <iostream>
#include <list>
#include <string>
using namespace std;
void transferSymbolsToList(string& temp, list<char>& l)
{
	for (int i = 0; i < temp.size(); i++)
	{
		l.push_back(temp[i]);
	}
}
void print(list<char> l)
{
	for (list<char>::iterator it = l.begin(); it != l.end(); it++)
	{
		cout << *it;
	}
}
void moveIterators(list<char>::iterator& i, list<char>::iterator& j,list<char>& l)
{
	if (i == l.begin())
	{
		i = l.end();
	}
	i--;
	j++;
	if (j == l.end())
	{
		j = l.begin();
	}
}
void moveStartIterators(list<char>::iterator& tempI, list<char>::iterator& tempJ,list<char>& l)
{
	tempI++;
	tempJ++;
	if (tempJ == l.end())
		tempJ = l.begin();
}
string findPalindrome(list<char>& l)
{
	string palindrome = "";
	int index = 0;
	list<char>::iterator tempI = l.begin();
	list<char>::iterator tempJ = ++l.begin();
	list<char>::iterator i = l.begin();
	list<char>::iterator j = ++l.begin();
	while (index != l.size())
	{
		bool havePalindrome = true;
		for (int k = 0; k < l.size(); k++)
		{
			if (*i == *j)
			{	
				palindrome += *i;
				moveIterators(i, j, l);
			}
			else 
			{
				havePalindrome = false;
				break;
			}
		}
		if (havePalindrome)
			return palindrome;
		index++;
		moveStartIterators(tempI, tempJ, l);
		i = tempI;
		j = tempJ;
		palindrome = "";
	}
	return "";
}
int main()
{
	string temp;
	list<char> l;
	getline(cin, temp);
	transferSymbolsToList(temp, l);
	cout << findPalindrome(l);
	return 0;
}