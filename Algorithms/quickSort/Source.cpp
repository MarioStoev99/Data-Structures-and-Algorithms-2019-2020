#include <iostream>

using namespace std;

void quickSort(int* arr, int len)
{
	int l = 0;
	int r = len - 1;
	int pivot = arr[len / 2];
	do
	{
		while (arr[l] < pivot) l++;
		while (pivot < arr[r]) r--;
		if (l < r)
		{
			swap(arr[l], arr[r]);
			l++;
			r--;
		}
		else if (l == r)
		{
			l++;
			r--;
		}
	} while (l <= r);
	if (r > 0) quickSort(arr, r + 1);
	if (l < len - 1) quickSort(arr + l, len - l);
}
int main()
{
	int arr[] = { 2,6,5,3,8,7,1,0 };
	quickSort(arr, 8);
	for (int i = 0; i < 8; i++)
		cout << arr[i] << " ";
	return 0;
}