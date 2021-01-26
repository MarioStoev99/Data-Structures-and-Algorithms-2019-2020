#include <iostream>
#include <list>
#include <forward_list>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

struct Edge {
	int v1, v2, edg;
	Edge(int _v1 = 0,int _v2 = 0,int _edg = 0) : v1(_v1) ,v2(_v2) ,edg(_edg) {}
};
typedef vector<Edge> Graph;
struct vertex {
	int rank;
	int parent;
	vertex(int _rank = 0,int _parent = -1) : rank(_rank) , parent(_parent) {}
};
pair<Graph,int> createGraph() {
	vector<Edge> graph;
	int size = 0;
	ifstream file("file.txt");
	while (!file.eof()) {
		Edge edge;
		file >> edge.v1 >> edge.v2 >> edge.edg;
		int biggerVertexValue = max(edge.v1, edge.v2);
		size = max(size, biggerVertexValue);
		graph.push_back(edge);
	}
	pair<Graph, int> temp(graph,size);
	return temp;
}
int find(vector<vertex>& tree,int index) {
	if (tree[index].parent != index) {
		tree[index].parent = find(tree, tree[index].parent);
	}
	return tree[index].parent;
}
void unionByRank(vector<vertex>& tree,int x,int y) {
	int xRoot = find(tree, x);
	int yRoot = find(tree, y);
	if (tree[xRoot].rank > tree[yRoot].rank) {
		tree[yRoot].parent = xRoot;
	}
	else if (tree[xRoot].rank < tree[yRoot].rank) {
		tree[xRoot].parent = yRoot;
	}
	else {
		tree[xRoot].parent = yRoot;
		tree[yRoot].rank++;
	}
}
void bubbleSort(Graph& edges, int len)
{
	bool flag = false;
	unsigned count = 0;
	do
	{
		flag = false;
		for (int i = len - 1; i > count; --i)
		{
			if (edges[i].edg > edges[i - 1].edg)
			{
				swap(edges[i], edges[i - 1]);
				flag = true;
			}
		}
		count++;
	} while (flag);
}
void initTree(vector<vertex>& tree,int size) {
	for (int i = 0; i < size; ++i) {
		vertex v;
		v.parent = i;
		tree.push_back(v);
	}
}
void Kruskal(Graph& graph,int size) {
	vector<vertex> tree;
	initTree(tree, size);
	bubbleSort(graph, graph.size());
	int cnt = 0;
	int min = 0;
	while (cnt < size - 1 && !graph.empty()) {
		Edge edge = graph[graph.size() - 1];
		graph.pop_back();
		int v1Parent = find(tree, edge.v1);
		int v2Parent = find(tree, edge.v2);
		if (v1Parent != v2Parent) {
			cout << edge.v1 << " " << edge.v2 << " " << edge.edg << endl;
			min += edge.edg;
			++cnt;
			unionByRank(tree, edge.v1, edge.v2);
		}
	}
	cout << "weight : " << min << endl;
}
int main() {
	pair<Graph, int> graph = createGraph();
	Kruskal(graph.first, graph.second + 1);
	return 0;
}