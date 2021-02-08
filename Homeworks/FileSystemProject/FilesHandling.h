#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "FileNotFoundException.hpp"
#include <queue>
using namespace std;

class FilesHandling
{
public : 
	static void deserialize(const string& source);
	static void deserialize(const string& source, const string& destination);
	static void ChargingFileInMemory(queue<string*>& fileLines,const string& source);
	static void serialize(queue<string*>& fileLines, const string& source);
};

