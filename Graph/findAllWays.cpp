#include<iostream>
#include <stack>
#include <list>
#include <set>
using namespace std;
list<list<int>> createGraph()
{
	list<int> v0, v1, v2, v3, v4, v5;
	list<list<int>> graph;
	v0.push_back(0);
	v0.push_back(1);
	v0.push_back(4);
	v0.push_back(5);
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v2.push_back(2);
	v2.push_back(4);
	v3.push_back(3);
	v3.push_back(5);
	v3.push_back(4);
	v4.push_back(5);
	v4.push_back(4);
	v5.push_back(4);

	graph.push_back(v0);
	graph.push_back(v1);
	graph.push_back(v2);
	graph.push_back(v3);
	graph.push_back(v4);
	graph.push_back(v5);
	return graph;
}
list<int> getList(int x, list<list<int>>& graph)
{
	list<list<int>>::iterator it = graph.begin();
	list<int>::iterator j = (*it).begin();
	while (*j != x && j != (*it).end())
	{
		it++;
		j = (*it).begin();
	}
	return *it;
}
void findAcyclicWay(int a, int b, list<list<int>>& graph,set<int>& visited, list<int>& way)
{
	visited.insert(a);
	way.push_back(a);
	if (a == b)
	{
		for (list<int>::iterator it = way.begin(); it != way.end(); it++)
			cout << *it << " ";
		cout << endl;
		visited.erase(b);
	}
	list<int> l = getList(a, graph);
	list<int>::iterator it = l.begin();
	it++;
	while (it != l.end())
	{
		if (visited.count(*it) == 0)
		{
			findAcyclicWay(*it, b, graph, visited, way);
		}
		it++;
	}
	way.pop_back();
}
int main()
{
	set<int> visited;
	list<int> l;
	list<list<int>> graph =createGraph();
	findAcyclicWay(0, 3, graph,visited,l);
	return 0;
}