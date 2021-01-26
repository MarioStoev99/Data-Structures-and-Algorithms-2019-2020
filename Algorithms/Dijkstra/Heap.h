#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Heap
{
private : 
	vector<pair<int,int>> minHeap;
private : 
	void shift_up(int index);
	void shift_down(int index);
public : 
	explicit Heap(int size);
	pair<int,int> minElement();
	void replace(int vertex,int edgeWeight);
	int size() const { return minHeap.size(); }
};



