#include <iostream>
#include <queue>
#include <vector>
using namespace std;
/*
condition
Нека имате двумерна матрица, която представя разположението на ябълки една до друга.Матрицата може да съдържа следните стойности :

0 - няма ябълка
1 - ябълката на тази позиция е прясна
2 - ябълката на тази позиция е гнила

Приемаме, че всяка една ябълка може да развали ябълките, които се намират от четирите й страни.Реализирайте алгоритъм, който:

а) проверява дали в даден момент всички ябълки ще се развалят

б) ако приемем за единица времето, необходимо на текущо загнилите ябълки да развалят непосредствените си съседите, то колко единици време ще са необходими на всички ябълки да бъдат развалени.

Пример: { {2, 1, 0, 2, 1},
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