#pragma once
#include <iostream>
class CommandNotFoundException : public std::exception {
public : 
	const char* what() const {
		return "This command doesn't exist in the system";
	}
};