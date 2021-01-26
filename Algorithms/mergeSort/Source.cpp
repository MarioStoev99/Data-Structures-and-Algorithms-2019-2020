#include <iostream>
using namespace std;

template <typename T>
void quickSort(T* a, int n) {
	int leftIndex = 0, rightIndex = n - 1;
	T x = a[rightIndex / 2];
	do {
		while (a[leftIndex] < x) leftIndex++;
		while (a[rightIndex] > x) rightIndex--;
		if (leftIndex < rightIndex) {
			swap(a[leftIndex], a[rightIndex]);
			leftIndex++;
			rightIndex--;
		}
		else if (leftIndex == rightIndex) {
			leftIndex++; rightIndex--;
		}
	} while (leftIndex <= rightIndex);
	if (rightIndex > 0) quickSort(a, rightIndex + 1);
	if (leftIndex < n - 1) quickSort(a + leftIndex, n - leftIndex);
}

int main()
{
	int arr[] = { 38,27,43,3,9,82,10 };
	quickSort(arr, 7);
	for (int i = 0; i < 7; i++)
		cout << arr[i] << " ";
	return 0;
}