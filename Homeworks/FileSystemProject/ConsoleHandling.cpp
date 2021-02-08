#include "ConsoleHandling.h"

ConsoleHandling::ConsoleHandling() : commands() {}

string ConsoleHandling::getExpression() {
	getline(cin, expression);
	string command = StringsHandling::getCommand(expression);
	int commandIndex = commands.findCommandIndex(command);
	if (commandIndex == -1) {
		throw CommandNotFoundException();
	}
	int getArgumentsNumber = StringsHandling::getNumberOfSpaces(expression);
	expression.size() != 0 ? getArgumentsNumber += 1 : getArgumentsNumber;
	if (!commands.hasValidArguments(commandIndex,getArgumentsNumber)) {
		throw InvalidArgumentsOfCommand();
	}
	expression.size() != 0 ? command += ' ' : command;
	command += expression;
	return command;
}