#pragma once
#include <iostream>

using namespace std;

class FileNotFoundException : public exception {
public : 
	const char* what() const {
		return "This file doesn't exist in the system";
	}
};