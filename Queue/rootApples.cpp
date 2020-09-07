#include <iostream>
#include <queue>
#include <vector>
using namespace std;
/*
condition
���� ����� �������� �������, ����� ��������� �������������� �� ������ ���� �� �����.��������� ���� �� ������� �������� ��������� :

0 - ���� ������
1 - �������� �� ���� ������� � ������
2 - �������� �� ���� ������� � �����

��������, �� ����� ���� ������ ���� �� ������� ��������, ����� �� ������� �� �������� � ������.������������ ���������, �����:

�) ��������� ���� � ����� ������ ������ ������ �� �� ��������

�) ��� ������� �� ������� �������, ���������� �� ������ ��������� ������ �� �������� ���������������� �� ��������, �� ����� ������� ����� �� �� ���������� �� ������ ������ �� ����� ���������.

������: { {2, 1, 0, 2, 1},
{ 1, 0, 1, 2, 1 },
{ 1, 0, 0, 2, 1 }}
*/
int allRotApples(vector<vector<int>>& matrix, int& count)
{
	int rows = matrix.size();
	int cows = matrix[0].size();
	if (rows == 0)
	{
		cout << "invalid size";
		return 0;
	}
	queue<pair<int, int>> q;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cows;j++)
		{
			unsigned currentElement = matrix[i][j];
			if(currentElement == 2)
			{
				q.push(pair<int, int>(i, j));
			}
			else if (currentElement == 1)
			{
				count++;
			}
		}
	}
		while(!q.empty())
		{
			pair<int, int> current = q.front();
			q.pop();
			if (current.second + 1  < cows && matrix[current.first][current.second + 1] == 1)
			{
				matrix[current.first][current.second + 1] = 2;
				count--;
				cout << "(" << current.first << "," << current.second + 1 << ")" << endl;
			}
			if (current.second - 1 >= 0 && matrix[current.first][current.second - 1] == 1)
			{
				matrix[current.first][current.second - 1] = 2;
				count--;
				cout << "(" << current.first << "," << current.second - 1 << ")" << endl;
			}
			if (current.first + 1 < rows && matrix[current.first + 1][current.second] == 1)
			{
				matrix[current.first + 1][current.second] = 2;
				count--;
				cout << "(" << current.first + 1 << "," << current.second << ")" << endl;
			}
			if (current.first >= rows && matrix[current.first - 1][current.second] == 1)
			{
				matrix[current.first - 1][current.second] = 2;
				count--;
				cout << "(" << current.first - 1 << "," << current.second << ")" << endl;
			}
		}
	return count;
}
int main()
{
	vector<vector<int>> matrix = {{2,1,0,2,1},
								  {1,0,1,2,1},
						          {1,0,0,2,1}};
	int countoffreshApples = 0;
	cout << allRotApples(matrix, countoffreshApples);
	return 0;
}