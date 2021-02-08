#pragma once
#pragma warning(disable: 4996)

#include <iostream>
#include <string>
#include <direct.h>

using namespace std;

class StringsHandling
{
public : 
	static string getFileName(string& path);
	static string getCommand(string&);
	static int getNumberOfSpaces(string& expression);
	static string getNewFileOrDirectoryName(const string& expression);
	static void removeLastFileOrDirectoryInThePath(string& expression,string getNewFileOrDirectoryName);
	static void removeQuotationMarks(string& expression);
	static string toLower(const string& expression);
	static bool compareFilesOrDirectories(const string& firstName, const string& secondName);
	static const char* getCurrentDirectory();
};

