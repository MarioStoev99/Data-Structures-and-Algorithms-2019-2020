#include<iostream>
#include <list>
#include <queue>
#include <stack>
using namespace std;
list<list<int>> createGraph()
{
	list<int> v0, v1, v2, v3, v4;
	list<list<int>> graph;
	v0.push_back(0);
	v0.push_back(1);
	v0.push_back(2);
	v0.push_back(3);
	v1.push_back(1);
	v1.push_back(0);
	v1.push_back(4);
	v2.push_back(2);
	v2.push_back(0);
	v2.push_back(3);
	v3.push_back(3);
	v3.push_back(0);
	v3.push_back(2);
	v4.push_back(4);
	graph.push_back(v0);
	graph.push_back(v1);
	graph.push_back(v2);
	graph.push_back(v3);
	graph.push_back(v4);
	return graph;
}
list<int> getList(int x, list<list<int>>& graph)
{
	list<list<int>>::iterator i = graph.begin();
	list<int>::iterator j = (*i).begin();
	while (j != (*i).end() && *j != x)
	{
		i++;
		j = (*i).begin();
	}
	return *i;
}

void dfsAux(int x, list<list<int>>& graph, bool* visited)
{
	cout << x << " ";
	visited[x] = true;
	list<int> l = getList(x, graph);
	list<int>::iterator it = l.begin();
	it++;
	while (it != l.end())
	{
		if (visited[*it] == false)
			dfsAux(*it, graph, visited);
		it++;
	}
}
void dfs(list<list<int>>& graph)
{
	int size = graph.size();
	bool* visited = new bool[size];
	fill_n(visited, size, false);
	for (int i = 0; i < size; i++)
	{
		if (visited[i] == false)
			dfsAux(i, graph, visited);
	}
	delete[] visited;
}
void bfs(int x,list<list<int>> graph)
{
	int size = graph.size();
	bool* visited = new bool[size];
	fill_n(visited, size, false);
	stack<int> q;
	q.push(x);
	visited[x] = true;
	//q.push(-1);
	while (!q.empty())
	{
		int current = q.top();
		q.pop();
		//if (current != -1)
		//{
			cout << current << " ";
			list<int> l = getList(current, graph);
			list<int>::iterator it = l.begin();
			it++;
			while (it != l.end())
			{
				if (!visited[*it])
				{
					visited[*it] = true;
					q.push(*it);
				}
				it++;
			}
		//}
		//else
		//{
		//	if (!q.empty())
		//		q.push(-1);
		//}
	}
	delete[] visited;
}
int main()
{
	list<list<int>> graph = createGraph();
	bfs(4,graph);
	//dfs(graph);
	//list<int> l = getList(0, graph);
	//printList(l);
	return 0;
}