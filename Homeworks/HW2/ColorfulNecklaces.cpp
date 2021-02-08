#include "ColorfulNecklaces.h"
void ColorfulNecklaces::chargeNecklaces(ifstream& file,int N) {
	getline(file, firstNecklace, ' ');
	getline(file, secondNecklace);
	if (firstNecklace.size() != N || secondNecklace.size() != N) {
		throw logic_error("These necklaces are with different size");
	}
}
void ColorfulNecklaces::addColourToGraph(const pair<char, int>& firstColour, const pair<char, int>& colourPlusTime) {
	for (list<pair<char, int>>& colour : colours) {
		if ( firstColour.first == colour.front().first) {
			colour.push_back(colourPlusTime);
			return;
		}
	}
	list<pair<char, int>> newColour;
	newColour.push_back(firstColour);
	newColour.push_back(colourPlusTime);
	colours.push_back(newColour);
}
void ColorfulNecklaces::addFinalState(const pair<char, int>& secondColour) {
	for (list<pair<char, int>> colour : colours)			 {
		if (colour.front().first == secondColour.first) {
			return;
		}
	}
	list < pair<char, int>> newColour;
	newColour.push_back(secondColour);
	colours.push_back(newColour);
}
void ColorfulNecklaces::chargeColours(ifstream& file,int M) {
	int cnt = 0;
	while (!file.eof()) {
		if (cnt >= M) {
			throw logic_error("Invalid input,too many colours");
		}
		pair<char, int> firstColour;
		file >> firstColour.first;
		if (firstColour.first < '!' || firstColour.first > '~') {
			throw logic_error("invalid input characters.You are going out from the limit");
		}
		firstColour.second = -1;
		pair<char, int> colourPlusTime;
		file >> colourPlusTime.first >> colourPlusTime.second;
		if (colourPlusTime.second < 0) {
			throw logic_error("invalid input time");
		}
		if (colourPlusTime.first < '!' || colourPlusTime.first > '~') {
			throw logic_error("invalid input characters");
		}
		addFinalState(colourPlusTime);
		addColourToGraph(firstColour, colourPlusTime);
		cnt++;
	}
	if (cnt != M) {
		throw logic_error("There aren't enough colours");
	}
}
ColorfulNecklaces::ColorfulNecklaces(const char* filename) {
	ifstream file(filename);
	if (!file) {
		throw FileNotFoundException();
	}
	int N, M;
	file >> N >> M;
	file.get();
	chargeNecklaces(file, N);
	chargeColours(file, M);
}
list<pair<char, int>> ColorfulNecklaces::getList(char firstColour) {
	for (list<pair<char, int>> colour : colours)	{
		if (colour.front().first == firstColour) {
			return colour;
		}
	}
}
// DFS
void ColorfulNecklaces::findShortestPath(char a, char b,set<char>& visited, int currentPathNumber,int& shortestPathNumber) {
	visited.insert(a);
	if (a == b) {
		visited.erase(a);
		shortestPathNumber = shortestPathNumber > currentPathNumber ? currentPathNumber : shortestPathNumber;
		return;
	}

	list<pair<char, int>> l = getList(a);
	list<pair<char, int>>::iterator it = l.begin();
	++it;
	while (it != l.end()) {
		if (!visited.count(it->first)) {
			findShortestPath(it->first, b, visited, currentPathNumber + it->second, shortestPathNumber);
		}
		++it;
	}
}
list<pair<char,int>> ColorfulNecklaces::getAllGeneralColours(char a,char b) {
	list<pair<char, int>> generalColours;
	list<pair<char, int>> firstColour = getList(a);
	list<pair<char, int>> secondColour = getList(b);
	list<pair<char, int>>::iterator i = firstColour.begin();
	list<pair<char, int>>::iterator j = secondColour.begin();
	++i;
	++j;
	for (i; i != firstColour.end(); ++i) {
		for (j; j != secondColour.end(); ++j) {
			if (i->first == j->first) {
				generalColours.push_back(*i);
				break;
			}
		}
	}
	return generalColours;
}
int ColorfulNecklaces::chooseTheBestGeneralColour(const list<pair<char,int>>& generalColours,int index) {
	char bestColour = firstNecklace[index];
	int shortestPath = INT_MAX;
	set<char> visited;
	for (pair<char, int> colour : generalColours) {
		int theShortestPathFromAtoGeneralVertex = INT_MAX, theShortestPathFromBtoGeneralVertex = INT_MAX;
		findShortestPath(firstNecklace[index], colour.first, visited, 0, theShortestPathFromAtoGeneralVertex);
		visited.clear();
		findShortestPath(secondNecklace[index], colour.first, visited, 0, theShortestPathFromBtoGeneralVertex);
		visited.clear();
		if (theShortestPathFromAtoGeneralVertex + theShortestPathFromBtoGeneralVertex < shortestPath) {
			shortestPath = theShortestPathFromAtoGeneralVertex + theShortestPathFromBtoGeneralVertex;
			bestColour = colour.first;
		}
	}
	firstNecklace[index] = bestColour;
	secondNecklace[index] = bestColour;
	return shortestPath;
}
void ColorfulNecklaces::reworkPresents() {
	int sum = 0;
	set<char> visited;
	for (int i = 0; i < firstNecklace.size(); ++i)	 {
		if (firstNecklace[i] != secondNecklace[i]) {
			int theShortestPathFromAtoB = INT_MAX, theShortestPathFromBtoA = INT_MAX;
			findShortestPath(firstNecklace[i], secondNecklace[i], visited, 0, theShortestPathFromAtoB);
			visited.clear();
			findShortestPath(secondNecklace[i], firstNecklace[i], visited, 0, theShortestPathFromBtoA);
			visited.clear();
			if (theShortestPathFromAtoB == INT_MAX && theShortestPathFromBtoA == INT_MAX) {
				list<pair<char, int>> generalColours = getAllGeneralColours(firstNecklace[i], secondNecklace[i]);
				if (generalColours.size() == 0) {
					cout << "-1" << endl << "Not Possible";
					return;
				}
				else {
					sum += chooseTheBestGeneralColour(generalColours,i);
				}
			}
			else if (theShortestPathFromAtoB < theShortestPathFromBtoA) {
				sum += theShortestPathFromAtoB;
				firstNecklace[i] = secondNecklace[i];
			}
			else {
				sum += theShortestPathFromBtoA;
				secondNecklace[i] = firstNecklace[i];
			}
		}
	}
	cout << sum << endl;
	cout << firstNecklace;
}