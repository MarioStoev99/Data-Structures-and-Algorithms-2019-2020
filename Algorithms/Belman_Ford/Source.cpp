#include <iostream>
#include <list>
#include <fstream>
#include <vector>
using namespace std;

typedef list<pair<pair<int, int>, int>> Graph;
typedef pair<pair<int, int>, int> Edge;
Graph listEdges() {
	Graph graph;
	ifstream file("file.txt");
	while (!file.eof()) {
		pair<pair<int, int>, int> temp;
		file >> temp.first.first >> temp.first.second >> temp.second;
		graph.push_back(temp);
	}
	return graph;
}
void print(const vector<int>& dist,const vector<int>& predesessors) {
	for (int el : predesessors) {
		cout << el << " ";
	}
	cout << endl;
	for (int el : dist) {
		cout << el << " ";
	}
}
void BellmanFord(Graph graph,int start,int size) {
	vector<int> dist(size,INT_MAX);
	vector<int> predesessors(size,-1);
	dist[0] = 0;
	for (int i = 0; i <= graph.size() - 2; ++i) {
		for (Edge edge : graph) {
			if (dist[edge.first.first] + edge.second < dist[edge.first.second]) {
				dist[edge.first.second] = dist[edge.first.first] + edge.second;
				predesessors[edge.first.second] = edge.first.first;
			}
		}
	}
	for (Edge edge : graph) {
		if (dist[edge.first.first] + edge.second < dist[edge.first.second]) {
			cout << "There is a negative cycle" << endl;
			return;
		}
	}
	print(dist, predesessors);
}
int main() {
	Graph graph = listEdges();
	BellmanFord(graph, 0,6);
	return 0;
}