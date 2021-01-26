#include "Heap.h"

Heap::Heap(int size) {
	pair<int, int> p(0, 0);
	minHeap.push_back(p);
	for (int i = 1; i < size; ++i) {
		pair<int, int> temp(i, INT_MAX);
		minHeap.push_back(temp);
	}
}
pair<int,int> Heap::minElement() {
	pair<int, int> minVertex = minHeap[0];
	swap(minHeap[0], minHeap[minHeap.size() - 1]);
	minHeap.pop_back();
	shift_down(0);
	return minVertex;
}
void Heap::shift_up(int index) {
	while (index > 0) {
		int father = (index - 1) / 2;
		if (minHeap[father].second > minHeap[index].second) {
			swap(minHeap[(index - 1) / 2], minHeap[index]);
			index = father;
		}
		else {
			break;
		}
	}
}
void Heap::shift_down(int index) {
	while (index * 2 + 1 < minHeap.size()) {
		int s = index * 2 + 1;
		if (s + 1 < minHeap.size() && minHeap[s].second > minHeap[s + 1].second) {
			++s;
		}
		if (minHeap[s].second < minHeap[index].second) {
			swap(minHeap[s], minHeap[index]);
			index = s;
		}
		else {
			break;
		}
	}
}
void Heap::replace(int vertex,int edgeWeight) {
	for (int i = 0; i < minHeap.size();++i) {
		if (minHeap[i].first == vertex) {
			minHeap[i].second = edgeWeight;
			shift_up(i);
			break;
		}
	}
}
