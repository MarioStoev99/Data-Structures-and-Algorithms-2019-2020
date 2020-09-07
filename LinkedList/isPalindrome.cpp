#include <iostream>
#include <list>

using namespace std;
bool isPalindrome(list<char> l)
{
	list<char>::iterator lbeg = l.begin();
	list<char>::reverse_iterator rbeg = l.rbegin();
	size_t len = 0;
	while (len != l.size() / 2)
	{
		if (*lbeg == *rbeg)
		{
			lbeg++;
			rbeg++;
			len++;
		}
		else return false;
	}
	return true;
}
int main()
{
	list<char> l;
	l.push_back('n');
	l.push_back('e');
	//l.push_back('r');
	l.push_back('v');
	l.push_back('e');
	l.push_back('n');
	cout << isPalindrome(l);
	return 0;
}