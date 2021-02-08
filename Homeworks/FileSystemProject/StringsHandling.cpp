#include "StringsHandling.h"

string StringsHandling::getFileName(string& path) {
	string fileOrDirectory = "";
	if (path[0] == '\\') {
		path.erase(0, 1);
	}
	for (int i = 0; i < path.size() && path[i] != '\\'; ++i) {
		fileOrDirectory += path[i];
	}
	path.erase(0, fileOrDirectory.size());
	return fileOrDirectory;
}
int StringsHandling::getNumberOfSpaces(string& expression) {
	int number = 0;
	bool quotationMarks = false;
	for (int i = 0; i < expression.size(); ++i) {
		if (expression[i] == ' ' && !quotationMarks) {
			++number;
		}
		if (expression[i] == '\"') {
			quotationMarks = !quotationMarks;
		}
	}
	return number;
}
string StringsHandling::getCommand(string& expression) {
	string command = "";
	for (int i = 0; i < expression.size() && expression[i] != ' '; ++i) {
		command += expression[i];
	}
	expression.erase(0, command.size() + 1);
	return command;
}
string StringsHandling::getNewFileOrDirectoryName(const string& expression) {
	string newFolderOrFile = "";
	for (int i = 0; i < expression.size(); ++i) {
		newFolderOrFile += expression[i];
		if (expression[i] == '\\') {
			newFolderOrFile = "";
		}
	}
	return newFolderOrFile;
}
void StringsHandling::removeLastFileOrDirectoryInThePath(string& expression, string getNewFileOrDirectoryName) {
	expression.erase(expression.size() - getNewFileOrDirectoryName.size(), getNewFileOrDirectoryName.size());
	if (expression.size() && expression[expression.size() - 1] == '\\') {
		expression.erase(expression.size() - 1,1);
	}
}
void StringsHandling::removeQuotationMarks(string& expression) {
	if (expression.size() == 0) {
		return;
	}
	if (expression[expression.size() - 1] == '\"' && expression[0] == '\"') {
		expression.erase(0, 1);
		expression.erase(expression.size() - 1, 1);
	} 
	else {
		throw logic_error("Invalid expression.Add quotation marks next time :)");
	}
}
string StringsHandling::toLower(const string& expression) {
	string temporary;
	for (int i = 0; i < expression.size();i++) {
		bool upperCase = expression[i] >= 'A' && expression[i] <= 'Z';
		if (upperCase) {
			temporary += expression[i] + 'a' - 'A';
		}
		else {
			temporary += expression[i];
		}
	}
	return temporary;
}
bool StringsHandling::compareFilesOrDirectories(const string& firstName, const string& secondName) {
	if (firstName.size() != secondName.size()) {
		return false;
	}
	for (int i = 0; i < firstName.size(); ++i) {
		bool condition = firstName[i] == secondName[i] + 'a' - 'A' ||
			firstName[i] == secondName[i] - 'a' + 'A' ||
			firstName[i] == secondName[i];
		if (!condition) {
			return false;
		}
	}
	return true;
}
const char* StringsHandling::getCurrentDirectory()
{
	const unsigned long MAX = 260;
	char* buff = new char[MAX];
	_getcwd(buff, MAX);
	return buff;
}