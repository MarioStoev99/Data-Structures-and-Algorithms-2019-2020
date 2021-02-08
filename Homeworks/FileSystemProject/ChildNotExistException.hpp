#pragma once
#include <iostream>
class ChildNotExistException : public std::exception {
public : 
	const char* what() const {
		return "Invalid directory or file's name";
	}
};
