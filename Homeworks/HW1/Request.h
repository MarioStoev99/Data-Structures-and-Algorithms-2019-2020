#pragma once
#include <iostream>
#include <string>
using namespace std;

class Request {
protected :
	unsigned floor;
	unsigned time;
public : 
	Request(int _floor = 0, int _time = 0);
	unsigned getFloor() const { return floor; }
	unsigned getTime() const { return time; }
};