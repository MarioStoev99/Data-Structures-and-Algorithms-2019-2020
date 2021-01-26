#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
	int v1, e, v2;
	Edge(int _v1 = 0, int _v2 = 0, int _edge = 0) {
		v1 = _v1;
		v2 = _v2;
		e = _edge;
	}
};

class Heap
{
private : 
	vector<Edge> sequence;
private : 
	void shift_down(int index);
	void shift_up(int index);
	int find_index_edge(const Edge& edge);
public : 
	Heap();
	Edge readMin() const;
	Edge popMin();
	void insert(Edge element);
	//void replace(Edge remove, Edge newEl);
	//void print() const;
};

