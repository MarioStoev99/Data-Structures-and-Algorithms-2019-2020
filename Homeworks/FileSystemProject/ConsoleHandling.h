#pragma once
#include "Commands.h"
#include "CommandNotFoundException.hpp"
#include "StringsHandling.h"

class ConsoleHandling {
private :
	Commands commands;
	string expression;
public :
	ConsoleHandling();
	string getExpression();
};