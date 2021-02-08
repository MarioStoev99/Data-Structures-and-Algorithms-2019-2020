#pragma once
#include "ConsoleHandling.h"
#include "Commands.h"
#include <list>
#include "ChildNotExistException.hpp"
#include <direct.h>
#include <fstream>
#include "FileNotFoundException.hpp"
#include "FilesHandling.h"
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <direct.h>
#include <windows.h>
#include <queue>

struct Node {
	string data;
	list<Node*> children;
	Node(string _data) : data(_data) {};
};
class FileSystem {
private : 
	//struct Node {
	//	string data;
	//	list<Node*> children;
	//	Node(string _data) : data(_data) {};
	//};
private:
	ConsoleHandling console;
	Commands commands;
	Node* root;
	string binaryFilename;
private : 
	void initTree(ifstream& file);
	void returnToStartDirectory(Node*& currentPtrPosition,string& getNewFileOrDirectoryName);
	void removeChildFromTree(Node*& currentPtrPosition,const string& name);
	bool isExistFileInTheSystem(Node* root,const string& path) const;
	
	void executeMkdir(string& expression, Node* currentPtrPosition);
	void executeRmdir(string& expression, Node* currentPtrPosition);

	void executeLs(string& expression, Node* currentPtrPosition);

	void executeWrite(string& firstArgument,const string& secondArgument, Node* currentPtrPosition);

	void executeCat(string& expression, Node* currentPtrPosition);

	void executeCd(string& expression, Node*& currentPtrPosition);

	void executeRemoveFile(string& expression, Node* currentPtrPosition);
	
	void writeInFile(string& destination, Node* currentPtrPosition, queue<string*>& fileLines);
	void readFromFile(string& source, Node* currentPtrPosition, queue<string*>& fileLines);

	void executeExport(string& source, string& destionation, Node* currentPtrPosition);
	void executeImport(string& source, string destionation,Node* currentPtrPosition);

	void executeCP(string& source, string& destination, Node* currentPtrPosition, const char* currentDirectory);
	void printFileSystem(Node* root) const;
	void save(Node* root,ofstream& file,string& path);
private : 
	void commandsWithoutArgument(const string& command,Node* currentPtrPosition);
	void commandsWithOneArgument(const string& command,Node*& currentPtrPosition,string& expression);
	void commandsWithTwoArguments(const string& command, Node*& currentPtrPosition,string& firstArgument,string& secondArgument);
	void commandsWithThreeArguments(const string& command, Node* currentPtrPosition, string& firstArgument,
		string& secondArgument, string& append);
	Node* relativePath(string& expression,Node* rootPtr);
	void del(Node*& root);
	void print(Node* child) const;
public :
	FileSystem();
	FileSystem(const FileSystem& other) = delete;
	FileSystem& operator=(const FileSystem& other) = delete;
	~FileSystem();
	void runFileSystem();
};