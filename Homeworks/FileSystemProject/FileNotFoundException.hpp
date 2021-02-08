#pragma once
#include <iostream>
using namespace std;
class FileNotFoundException : public exception {
	const char* what() const {
		return "The file with this name doesn't exist in the system";
	}
};