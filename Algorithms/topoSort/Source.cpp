#include <iostream>
#include <list>
#include <vector>
#include <set>
using namespace std;
list < list<pair<char, int>>> createGraph() {
	list<pair<char, int>> l1;
	pair<char, int> p1('a', 0);
	pair<char, int> p2('b', 1);
	pair<char, int> p3('c', 2);
	l1.push_back(p1);
	l1.push_back(p2);
	l1.push_back(p3);
	list<pair<char, int>> l2;
	pair<char, int> p5('b', 1);
	pair<char, int> p6('c', 5);
	pair<char, int> p7('d', 1);
	pair<char, int> p8('e', 5);
	l2.push_back(p5);
	l2.push_back(p6);
	l2.push_back(p7);
	l2.push_back(p8);
	list<pair<char, int>> l3;
	pair<char, int> p9('c', 2);
	pair<char, int> p10('d', 4);
	l3.push_back(p9);
	l3.push_back(p10);
	list<pair<char, int>> l4;
	pair<char, int> p11('d', 2);
	pair<char, int> p12('f', 3);
	l4.push_back(p11);
	l4.push_back(p12);
	list<pair<char, int>> l5;
	pair<char, int> p13('e', 2);
	pair<char, int> p14('g', 1);
	l5.push_back(p13);
	l5.push_back(p14);
	list<pair<char, int>> l6;
	pair<char, int> p15('f', 1);
	pair<char, int> p16('g', 0);
	l6.push_back(p15);
	l6.push_back(p16);
	list<pair<char, int>> l7;
	pair<char, int> p17('g', 2);
	l7.push_back(p17);
	list<list<pair<char, int>>> graph;
	graph.push_back(l1);
	graph.push_back(l2);
	graph.push_back(l3);
	graph.push_back(l4);
	graph.push_back(l5);
	graph.push_back(l6);
	graph.push_back(l7);
	return graph;
}
list<pair<char,int>> getVertexWithMinEntranceDegree(list<list<pair<char, int>>>& graph,const set<char>& verteces) {
	list<pair<char, int>> minVertex;
	int minDegree = INT_MAX;
	for (list<pair<char, int>> vertex : graph)	{
		if (verteces.count(vertex.front().first) && minDegree > vertex.front().second) {
			minVertex = vertex;
			minDegree = vertex.front().second;
		}
	}
	return minVertex;
}
set<char> transferVertecesToSet(const list<list<pair<char, int>>>& graph) {
	set<char> verteces;
	for (list<pair<char, int>> vertex : graph) {
		verteces.insert(vertex.front().first);
	}
	return verteces;
}
void decreaseDegree(char v,list<list<pair<char, int>>>& graph) {
	for (list<pair<char, int>>& vertex : graph) {
		if (vertex.front().first == v) {
			--vertex.front().second;
			return;
		}
	}
}
void print(const vector<char>& ordinance) {
	for (char vertex : ordinance) {
		cout << vertex << " ";
	}
}
void topoSort(list<list<pair<char,int>>>& graph) {
	vector<char> ordinance;
	set<char> verteces = transferVertecesToSet(graph);
	while (!verteces.empty()) {
		list<pair<char, int>> vertexWithMinDegree = getVertexWithMinEntranceDegree(graph,verteces);
		list<pair<char, int>>::iterator it = vertexWithMinDegree.begin();
		++it;
		while (it != vertexWithMinDegree.end()) {
			decreaseDegree(it->first,graph);
			++it;
		}
		ordinance.push_back(vertexWithMinDegree.front().first);
		verteces.erase(vertexWithMinDegree.front().first);
	}
	print(ordinance);
}
int main() {
	list<list<pair<char, int>>> graph = createGraph();
	topoSort(graph);
	return  0;
}