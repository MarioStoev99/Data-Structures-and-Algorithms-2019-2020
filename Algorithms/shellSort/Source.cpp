#include <iostream>

using namespace std;

void CocktailSort(int a[], int n)
{
	bool swapped = true;
	int start = 0;
	int end = n - 1;

	while (swapped) 
	{
		swapped = false;
		for (int i = start; i < end; ++i)
		{
			if (a[i] > a[i + 1]) 
			{
				swap(a[i], a[i + 1]);
				swapped = true;
			}
		}
		if (!swapped)
			break;
		swapped = false;
		--end;
		for (int i = end - 1; i >= start; --i) {
			if (a[i] > a[i + 1]) {
				swap(a[i], a[i + 1]);
				swapped = true;
			}
		}
		++start;
	}
}
int main()
{
	int arr[] = { 8,2,5,3,4,1 };
	CocktailSort(arr, 6);
	for (int i = 0; i < 6; i++)
		cout << arr[i] << " ";
	return 0;
}