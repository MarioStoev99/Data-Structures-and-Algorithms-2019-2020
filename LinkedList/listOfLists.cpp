#include <iostream>
#include <list>
#include <fstream>
#include <string>
using namespace std;
/*
conditon
����� ������� ������ L �� �������� ������� �� �������� � ������� �� ���������� �������� ������
�������, ����� � ������� ����, � ����� � �������� ���������.�� �� ������������ ������ �������, ����� ������ ����
����� ������ � ��������� ���� ����������� �� ����� ���� �� �� ������� � ������� �� L, ���� ������� ���� ��
����������� ������ �� ���� �� �� ������� � ������� �� ������ �������� ������, ������� ���� �� ����������� ���
������ �������� ������ � �.�.������ �� � ���������� ������� �� 20 �������.
���������:
1. ��������, �� ���� ���� ���� �� �� ������� � ������� �� ���� �������� ������, ��� ������� �� ������ ��
������� � �������������� �������� �� ��������� ������.��������, ��� � ������� ����� ��������������
��������� �c�, �h�, �a� � �r�, �� ���� ����, ����� ���� �� �� ������� � ���� � �arch�.
2. � ������� �� ��������� ���� ����������� ���� �� ��� �������� ������������ ����� - �.�(�����) �, �(�������),
� : �(��� �����), �; �(����� � �������), � ? � � �!�.������� �� �������� ��� ���������� � ������� �� ����������
�������.
*/
void init(list<list<char>>& l)
{
	int listsNumber;
	cout << "enter the number of lists : ";
	do
	{
		cin >> listsNumber;
	} while (listsNumber <= 0);
	for (int i = 0; i < listsNumber; i++)
	{
		list<char> temp;
		for (int j = 0; j < 10; j++)
		{
			char c;
			cin >> c;
			temp.push_back(c);
		}
		l.push_back(temp);
		temp.clear();
	}
}
//K M D J E W Q I S K
//k k d s a l o v e a
//i n g k j h p l a y
//f o o t b a l k b v
void print(list<list<char>> l)
{
	for (list<list<char>>::iterator it = l.begin(); it != l.end(); it++)
	{
		for (list<char>::iterator j = (*it).begin(); j != (*it).end(); j++)
		{
			cout << *j << " ";
		}
		cout << endl;
	}
}
void readSentence(list<string>& words)
{
	ifstream file("file.txt");
	while (!file.eof())
	{
		string temp;
		getline(file, temp,' ');
		words.push_back(temp);
	}
}
void printWords(list<string>& words)
{
	for (list<string>::iterator it = words.begin(); it != words.end(); it++)
	{
		cout << *it << ",";
	}
}
bool necessarySymbols(char c)
{
	return c != '.' && c != ':' && c != ',' && c != ';' && c != '?' && c != '!';
}
bool findWord(list<char> l,string word)
{
	for (list<char>::iterator it = l.begin(); it != l.end(); it++)
	{
		list<char>::iterator cloning = it;
		bool exist = true;
		for (int i = 0; i < word.size(); i++)
		{
			if (cloning == l.end())
				cloning = l.begin();
			if (!necessarySymbols(*cloning))
			{
				cloning++;
				continue;
			}
			if (*cloning != word[i])
			{
				exist = false;
				break;
			}
			else cloning++;
		}
		if (exist)
			return true;
	}
	return false;
}
bool isExistSuchString(list<list<char>> l, list<string> words)
{
	for (list<list<char>>::iterator i = l.begin(); i != l.end(); i++)
	{
		string temp = words.front();
		words.pop_front();
		if (!findWord(*i, temp))
		{
			return false;
		}
	}
	return true;
}
int main()
{
	list<list<char>> l;
	list<string> words;
	init(l);
	//print(l);
	readSentence(words);
	//printWords(words);
	cout << isExistSuchString(l, words);
	return 0;
}