#include <iostream>
#include <stack>
#include <string>
using namespace std;

bool isCorrectExpression(string expressionFromParenthesis) {
	if (expressionFromParenthesis.empty())
		return true;
	stack<char> kindOfParenthesis;
	for (int i = 0;i < expressionFromParenthesis.size(); ++i) {
		if (expressionFromParenthesis[i] == '(' || expressionFromParenthesis[i] == '{' || expressionFromParenthesis[i] == '[') {
			kindOfParenthesis.push(expressionFromParenthesis[i]);
		}
		else {
			if (kindOfParenthesis.empty())
				return false;
			else if (expressionFromParenthesis[i] == ')') {
				if (kindOfParenthesis.top() != '(')
					return false;
				else
					kindOfParenthesis.pop();
			}
			else if (expressionFromParenthesis[i] == ']') {
				if (kindOfParenthesis.top() != '[')
					return false;
				else
					kindOfParenthesis.pop();
			}
			else {
				if (kindOfParenthesis.top() != '{')
					return false;
				else
					kindOfParenthesis.pop();
			}
		}
	}
	if (kindOfParenthesis.empty())
		return true;
	else
		return false;
}
int main()
{
	string expressionFromParenthesis;
	while (true) {
		cout << "enter an expression : ";
		getline(cin, expressionFromParenthesis);
		cout << "answer : ";
		cout << isCorrectExpression(expressionFromParenthesis) << endl;
	}
	return 0;
}