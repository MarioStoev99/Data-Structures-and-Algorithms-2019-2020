#include <list>
#include <iostream>
#include <set>
using namespace std;
//list<list<int>> createGraph()
//{
//	list<list<int>> graph;
//	list<int> v0, v1, v2, v3;
//	v0.push_back(0);
//	v0.push_back(1);
//	v1.push_back(1);
//	v1.push_back(2);
//	v2.push_back(2);
//	v2.push_back(3);
//	v3.push_back(3);
//	graph.push_back(v0); 
//	graph.push_back(v1);
//	graph.push_back(v2);
//	graph.push_back(v3);
//	return graph;
//}
list<list<int>> createGraph()
{
	list<list<int>> graph;
	list<int> v0, v1, v2, v3, v4;
	v0.push_back(0);
	v0.push_back(1);
	v1.push_back(1);
	v1.push_back(2);
	v2.push_back(2);
	v2.push_back(3);
	v2.push_back(4);
	v3.push_back(3);
	//v3.push_back(0);
	v4.push_back(4);
	//v4.push_back(2);
	graph.push_back(v0);
	graph.push_back(v1);
	graph.push_back(v2);
	graph.push_back(v3);
	graph.push_back(v4);
	return graph;
}
list<int> getList(int x,list<list<int>>& graph)
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
bool haveCycle(int x,list<list<int>>& graph,set<int>& visited)
{
	if (visited.count(x) == true)
		return true;
	visited.insert(x);
	list<int> l = getList(x, graph);
	list<int>::iterator it = l.begin();
	it++;
	while (it != l.end())
	{
		if(haveCycle(*it,graph,visited))
			return true;
		it++;
	}
	return false;
}
int main()
{
	set<int> visited;
	list<list<int>> graph = createGraph();
	cout << haveCycle(0, graph, visited);
	return 0;
}