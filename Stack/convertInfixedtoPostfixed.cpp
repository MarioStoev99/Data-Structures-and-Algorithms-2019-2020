#include <iostream>
#include <string>
#include <stack>
using namespace std;
bool isLetter(char c)
{
	return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z';
}
bool isOper(char c)
{
	return c == '+' || c == '-' || c == '/' || c == '*';
}
string convertFromInfixedToPostFixed(string infixedExpression) {
	if (infixedExpression.empty())
		return infixedExpression;
	string postfixedExpression;
	stack<char> operations;
	for (int i = 0; i < infixedExpression.length(); i++) {
		if (infixedExpression[i] == '(')
			operations.push(infixedExpression[i]);
		else if (infixedExpression[i] == ')') {
			postfixedExpression += operations.top();
			operations.pop();
			operations.pop();
		}
		else if (isLetter(infixedExpression[i]))
			postfixedExpression += infixedExpression[i];
		else if (isOper(infixedExpression[i])) {
			if (operations.empty())
				operations.push(infixedExpression[i]);
			else if (operations.top() == '+' || operations.top() == '-') {
				if (infixedExpression[i] == '+' || infixedExpression[i] == '-') {
					postfixedExpression += operations.top();
					operations.pop();
					operations.push(infixedExpression[i]);
				}
				else
					operations.push(infixedExpression[i]);
			}
			else if (operations.top() == '(')
				operations.push(infixedExpression[i]);
			else {
				while (!operations.empty()) {
					postfixedExpression += operations.top();
					operations.pop();
				}
				operations.push(infixedExpression[i]);
			}
		}
		else {
			cout << "this expression has invalid symbol";
			return "";
		}
	}
	while (!operations.empty()) {
		postfixedExpression += operations.top();
		operations.pop();
	}
	return postfixedExpression;
}
// (a*b)+(c*d)-e
// a+b*c
int main()
{
	string expression;
	while (true) {
		cout << "enter an infixed expression : ";
		getline(cin, expression);
		cout << "your postfixed expression is : ";
		cout << convertFromInfixedToPostFixed(expression) << endl;
	}
	return 0;
}