#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "InvalidArgumentsOfCommand.hpp"

using namespace std;

class Commands {
private:
	vector<pair<string, vector<bool>>> commands;

private : 
	void ls();
	void mkdir();
	void rmdir();
	void cd();
	void cp();
	void rm();
	void cat();
	void write();
	void import();
	void exportCommand();
	void exit();
public:
	Commands();
	bool hasValidArguments(int index,int arguments) const;
	int findCommandIndex(const string& userCommand) const;
};