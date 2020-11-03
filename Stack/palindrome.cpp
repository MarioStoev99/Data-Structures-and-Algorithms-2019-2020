#include <iostream>
#include <string>
#include <stack>

using namespace std;
bool isPalindrome(string expression) {
	if (expression.empty())
		return true;
	stack<char> letters;
	for (int i = 0; i < expression.size() / 2; ++i) {
		letters.push(expression[i]);
	}
	unsigned len = 0;
	if (expression.size() % 2 == 0) len = expression.size() / 2;
	else len = expression.size() / 2 + 1;
	for (int i = len; i < expression.size(); i++) {
		if (letters.top() != expression[i]) return false;
		else letters.pop();
	}
	return true;
}
int main()
{
	string expression;
	while (true) {
		cout << "enter an expression : ";
		getline(cin,expression);
		cout << "isPalindrome : ";
		cout << isPalindrome(expression) << endl;
	}
	return 0;
}