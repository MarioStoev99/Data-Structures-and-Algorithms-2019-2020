#pragma once
#include <iostream>
class InvalidArgumentsOfCommand : public std::exception {
public : 
	const char* what() const {
		return "Invalid arguments ";
	}
};