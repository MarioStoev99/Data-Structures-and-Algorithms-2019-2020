#include <iostream>
#include <stack>
using namespace std;
void initStack(stack<int>& s)
{
	cout << "enter the number of elements : ";
	size_t size;
	cin >> size;
	for (int i = 0; i < size; i++)
	{
		int temp;
		cin >> temp;
		s.push(temp);
	}
}
void mergeStacks(stack<int> s1, stack<int> s2, stack<int>& s3)
{
	while (!s1.empty() && !s2.empty())
	{
		if (s1.top() > s2.top())
		{
			s3.push(s1.top());
			s1.pop();
		}
		else
		{
			s3.push(s2.top());
			s2.pop();
		}
	}
	if (!s1.empty())
		s3.push(s1.top());
	else
		s3.push(s2.top());
}
void printElementsOfStack(stack<int> s3)
{
	while (!s3.empty())
	{
		cout << s3.top() << " ";
		s3.pop();
	}
}
int main()
{
	stack<int> s1;
	stack<int> s2;
	stack<int> s3;
	initStack(s1);
	initStack(s2);
	mergeStacks(s1, s2, s3);
	printElementsOfStack(s3);
	return 0;
}