#include <iostream>
#include <list>

using namespace std;
list<list<int>> createGraph()
{
	list<int> v1, v2, v3, v4;
	list<list<int>> graph;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);
	v2.push_back(2);
	v2.push_back(1);
	v2.push_back(3);
	v2.push_back(4);
	v3.push_back(3);
	v3.push_back(2);
	v3.push_back(1);
	v3.push_back(4);
	v4.push_back(4);
	v4.push_back(2);
	v4.push_back(3);
	//v4.push_back(1);
	graph.push_back(v1);
	graph.push_back(v2);
	graph.push_back(v3);
	graph.push_back(v4);
	return graph;
}
bool fullGraph(list<list<int>>& graph)
{
	unsigned size = graph.size();
	for (list<list<int>>::iterator it = graph.begin(); it != graph.end(); it++)
	{
		if ((*it).size() != size)
			return false;
	}
	return true;
}
int main()
{
	list<list<int>> graph = createGraph();
	cout << fullGraph(graph);
	return 0;
}