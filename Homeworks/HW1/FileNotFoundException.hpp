#pragma once
#include <iostream>
using namespace std;
class FileNotFoundException : public exception {
public:
	char const* what() const {
		return "This file doesn't exist";
	}
};