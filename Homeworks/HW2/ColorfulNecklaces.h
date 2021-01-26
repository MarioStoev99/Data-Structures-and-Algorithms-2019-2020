#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "FileNotFoundException.hpp"
#include <set>
#include <list>
using namespace std;

class ColorfulNecklaces
{
private : 
	list<list<pair<char, int>>> colours;
	string firstNecklace;
	string secondNecklace;
private : 
	// deserialize
	void chargeNecklaces(ifstream& file,int N);
	void chargeColours(ifstream& file,int M);
	void addColourToGraph(const pair<char,int>& firstColour,const pair<char,int>& colourPlusTime);
	void addFinalState(const pair<char, int>& colour);

	list<pair<char, int>> getList(char colour);
	void findShortestPath(char a, char b,set<char>& visited,int currentPathNumber, int& shortestPathNumber);
	int chooseTheBestGeneralColour(const list<pair<char, int>>& generalColours, int index);
	list<pair<char, int>>getAllGeneralColours(char a, char b);
public:
	explicit ColorfulNecklaces(const char* filename);
	void reworkPresents();
};

