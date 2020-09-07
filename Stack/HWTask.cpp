#include <iostream>
#include <stack>
#include <fstream>

/*
Нека е дадена следната дефиниция на израз :
израз = неотрицателно цяло число | f(израз) | g(израз) | m(израз, израз), където :
	● f(x) = (x * x) mod 100, където mod 100 връща остатъка при деление на 100
	● g(x) = (x mod 5) !, т.е.факториелът на остатъка на деленето на х на 5
	● m(x, y) = min(x, y)
	Например, f(m(25, g(14))) е валиден израз от горния тип и се оценява до 76, защото :
	f(m(25, g(14))) =
	f(min(25, (14 mod 5)!) =
		f(min(25, 24)) =
		(24 * 24) mod 100 = 76
		Даден е текстови файл с последователен достъп, в който са записани на отделен ред цяло
		положително число N и след него пак на отделни редове N на брой изрази от горния вид.
		Съдържанието на един примерен файл би бил :
3
f(15)
m(f(15), 24)
f(m(25, g(14)))
Да се напише програма, която прочита информацията от един такъв файл и извежда на
стандартния изход на отделен ред всеки израз от файла и съответната му крайна оценка(без
	междинни стъпки).
	Забележка:
-Програмата трябва да работи за произволен израз от горния вид.
- При реализацията можете да използвате избрана от вас работеща реализация на
структурата или структурите, които ще използвате, включително и тези предоставяни от STL.
Реализациите няма да се оценяват, а само тяхното използване при решаването на задачата.
*/

using namespace std;

stack<char> functions;
stack<int> digits;

int factoriel(int num)
{
	int count = num;
	while (count != 1)
	{
		count--;
		num *= count;
	}
	return num;
}
int minNumber()
{
	int x = digits.top();
	digits.pop();
	int y = digits.top();
	digits.pop();
	if (x > y)
		return y;
	else
		return x;
}
int multi()
{
	int number = digits.top();
	digits.pop();
	number *= number;
	int remainder = number % 100;
	return remainder;
}
int numbers(string& a, int& index)
{
	int number = 0;
	while (a[index] >= '0' && a[index] <= '9')
	{
		number = number * 10 + a[index] - '0';
		index++;
	}
	index--;
	return number;
}
int main()
{
	unsigned N;
	ifstream file("file.txt");
	file >> N;
	if(N == 0)
    {
        cout << "Invalid number";
        return 0;
    }
	for (int i = 0; i < N; i++)
	{
	    string a;
		file >> a;
		for (int i = 0; i < a.size(); i++)
		{
			char c = a[i];
			if (c == 'f' || c == 'g' || c == 'm')
			{
				functions.push(c);
			}
			else if (c >= '0' && c <= '9')
			{
				digits.push(numbers(a, i));
			}
			else if (c == ')')
			{
				if (functions.top() == 'g')
				{
					unsigned number = digits.top();
					digits.pop();
					int remainder = number % 5;
					digits.push(factoriel(remainder));
				}
				else if (functions.top() == 'm')
				{
					int min = minNumber();
					digits.push(min);
				}
				else
				{
					int number = multi();
					digits.push(number);
				}
				functions.pop();
			}
		}
		while (!digits.empty())
		{
			cout << a << " : " << digits.top() << endl;
			digits.pop();
		}
	}
	return 0;
}
