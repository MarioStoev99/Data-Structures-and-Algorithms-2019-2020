#include <iostream>

using namespace std;

void heapSort(int* a, int n) {
	int index = n / 2 - 1;
	for (int j = index; j >= 0; j--) {
		heapInsert(a, j, n);
	}
	n--;
	while (n > 0) {
		swap(a[0], a[n]);
		heapInsert(a, 0, n);
		n--;
	}
}
void heapInsert(int* a, int elemIndex, int n) {
	int biggerChildIndex;
	int childIndex = 2 * elemIndex + 1;
	while (childIndex < n) {
		biggerChildIndex = childIndex;
		if (childIndex < n - 1 && a[childIndex] < a[childIndex + 1]) {
			biggerChildIndex = childIndex + 1;
		}
		if (a[elemIndex] < a[biggerChildIndex]) {
			swap(a[elemIndex], a[biggerChildIndex]);
			elemIndex = biggerChildIndex;
			childIndex = 2 * elemIndex + 1;
		}
		// излизаме от цикъла
		else
			break;
	}
}
int main()
{
	int arr[] = {2,8,5,3,9,1};
	heapSort(arr, 6);
	for (int i = 0; i < 6; i++)
		cout << arr[i] << " ";
	return 0;
}