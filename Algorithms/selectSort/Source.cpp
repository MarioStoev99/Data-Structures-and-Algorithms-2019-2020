#include <iostream>
using namespace std;

void selectionSort(int arr[], int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		int min_idx = i;
		for (int j = i + 1; j < n; j++)
		{
			if (arr[j] < arr[min_idx])
				min_idx = j;
		}
		swap(arr[min_idx], arr[i]);
	}
}
void bubbleSort(int* arr, unsigned len)
{
	bool changed = false;
	unsigned sorted = 0;
	do
	{
		changed = false;
		for (unsigned i = len - 1; i > sorted; i--)
		{
			if (arr[i] < arr[i - 1])
			{
				swap(arr[i], arr[i - 1]);
				changed = true;
			}
		}
		sorted++;
	} while (changed);
}
void insertionSort(int* arr, int size) {
	int key, j;
	for (int i = 1; i < size; i++) {
		key = arr[i];
		j = i;
		while (j > 0 && arr[j - 1] > key) {
			arr[j] = arr[j - 1];
			j--;
		}
		arr[j] = key;
	}
}
int main()
{
	int arr[6] = { 8,2,5,4,1,3 };
	insertionSort(arr, 6);
	for (int i = 0; i < 6; i++)
		cout << arr[i] << " ";
	return 0;
}