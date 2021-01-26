#include <iostream>
#include "Heap.h"
#include <vector>
#include <list>
#include <fstream>
#include <set>
using namespace std;

typedef vector<list<pair<int,int>>> Graph;
Graph createGraph(const string& filename) {
	Graph graph;
	for (int i = 0; i < 9; ++i) {
		list<pair<int,int>> temp;
		pair<int, int> p;
		p.first = i;
		p.second = -1;
		temp.push_back(p);
		graph.push_back(temp);
	}
	ifstream file(filename.c_str());
	while (!file.eof()) {
		int x, y, z;
		file >> x >> y >> z;
		pair<int, int> vertexAndEdge;
		vertexAndEdge.first = y;
		vertexAndEdge.second = z;
		graph[x].push_back(vertexAndEdge);
	}
	return graph;
}
list < pair<int, int>> getList(const Graph& graph,int startVertex) {
	return graph[startVertex];
}
void print(const vector<Edge>& result) {
	int total = 0;
	for (Edge edge : result) {
		cout << edge.v1 << " " << edge.v2 << " " << edge.e << endl;
		total += edge.e;
	}
	cout << "MST : " << total << endl;
}
void initVerteces(const Graph& graph,set<int>& visited) {
	for (list<pair<int, int>> vertex : graph) {
		visited.insert(vertex.begin()->first);
	}
}
void trasnferEdgesToHeap(const Graph& graph,Heap& minHeap,int startVertex) {
	list<pair<int, int>> heirs = getList(graph, startVertex);
	list<pair<int, int>>::iterator it = heirs.begin();
	int currentVertex = it->first;
	++it;
	for (it; it != heirs.end();++it) {
		Edge edge(currentVertex, it->first, it->second);
		minHeap.insert(edge);
	}
}
void Prim(const Graph& graph,int startVertex) {
	vector<Edge> result;
	set<int> visited;
	Heap minHeap;
	initVerteces(graph,visited); // O(V)
	trasnferEdgesToHeap(graph,minHeap, startVertex); // O(E)
	visited.erase(startVertex);
	while (!visited.empty()) {
		Edge edge = minHeap.popMin();  // O(1)
		if (visited.count(edge.v2)) { // O(log V)
			result.push_back(edge); // O(1)
			visited.erase(edge.v2); // O(log V)
			trasnferEdgesToHeap(graph, minHeap, edge.v2); // O(log V)
		}
	}
	print(result); // O(V)
}
int main() {
	Graph graph = createGraph("file.txt");
	Prim(graph, 0);
	return 0;
}