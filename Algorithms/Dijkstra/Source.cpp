#include <iostream>
#include <list>
#include <vector>
#include <set>
#include <fstream>
#include "Heap.h"
using namespace std;
typedef vector<list<pair<int, int>>> Graph;
Graph createGraph(const string& filename) {
	ifstream file(filename.c_str());
	if (!file) {
		throw logic_error("This file doesn't exist in the system");
	}
	int graphSize;
	file >> graphSize;
	Graph graph(graphSize);
	while (!file.eof()) {
		int v1, v2, e;
		file >> v1 >> v2 >> e;
		pair<int, int> p(v2,e);
		graph[v1].push_back(p);
	}
	return graph;
}
void print(const vector<int>& bestPaths,const vector<int>& predecessors) {
	for (int i = 0; i < bestPaths.size(); ++i) {
		cout << i << " ";
	}
	cout << endl;
	for (int element : bestPaths) {
		cout << element << " ";
	}
	cout << endl;
	for (int pred : predecessors) {
		cout << pred << " ";
	}
}
void Dijkstra(char startPoint,const Graph& graph) {
	Heap minHeap(graph.size());
	vector<int> visited(graph.size(), INT_MAX);
	vector<int> predecessors(graph.size());
	predecessors[0] = -1;
	visited[0] = 0;
	while (minHeap.size()) {
		pair<int,int> minVertex = minHeap.minElement(); // O(1)
		list<pair<int, int>> vertex = graph[minVertex.first]; // O(1)
		list<pair<int, int>>::iterator it = vertex.begin();
		while (it != vertex.end()) {
			if (minVertex.second + it->second < visited[it->first]) {
				minHeap.replace(it->first,minVertex.second + it->second);
				predecessors[it->first] = minVertex.first;
				visited[it->first] = minVertex.second + it->second;
			}
			++it;
		}
	}
	print(visited,predecessors);
}
int main() {
	try {
		Graph graph = createGraph("file.txt");
		Dijkstra(0, graph);
	}
	catch (logic_error & e) {
		cout << e.what();
	}
	catch (exception & e) {
		cout << e.what();
	}
	return 0;
}