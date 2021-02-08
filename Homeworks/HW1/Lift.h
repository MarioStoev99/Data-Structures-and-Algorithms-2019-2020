#pragma once
#include <iostream>
using namespace std;
class Lift {
private : 
	int maxCapPlaces;
	int currentFloor;
public : 
	Lift(int _maxCapPlaces = 1,int _currentFloor = 1);
	void setMaxCapPlaces(int _maxCapPlaces);
	void setCurrentFloor(int _currentFloor) { currentFloor = _currentFloor; }
	int getMaxCapPlaces() const { return maxCapPlaces; }
	int getCurrentFloor() const { return currentFloor; }
};