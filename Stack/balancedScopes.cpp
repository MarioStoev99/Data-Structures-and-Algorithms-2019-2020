#include <iostream>
#include <stack>
using namespace std;
const size_t MAX_SIZE = 1024;
void isproperlySkopes(stack<char> s,char* str)
{
	for (size_t i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == '(')
			s.push(str[i]);
		if (str[i] == ')')
		{
			if (!s.empty())
				s.pop();
			else
			{
				cout << "False";
				return;
			}
		}
	}
	if (s.empty())
	{
		cout << "True";
	}
	else
		cout << "False";
}
int main()
{
	stack<char> s;
	char str[MAX_SIZE];
	cin.getline(str, MAX_SIZE);
	isproperlySkopes(s, str);
	return 0;
}