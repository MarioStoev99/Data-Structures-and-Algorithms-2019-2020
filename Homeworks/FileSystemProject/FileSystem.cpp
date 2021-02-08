#include "FileSystem.h"
void FileSystem::initTree(ifstream& file) {
	while (true) {
		string path;
		size_t sizePath = 0;
		file.read((char*)&sizePath, sizeof(size_t));
		char* str = new char[sizePath + 1];
		file.read(str, sizePath);
		str[sizePath] = 0;
		path = str;
		delete[] str;
		if (path.size() == 0) {
			break;
		}
		if (path[path.size() - 4] == '.') {
			commandsWithOneArgument("write", root, path);
		}
		else {
			commandsWithOneArgument("mkdir", root, path);
		}
	}
}
FileSystem::FileSystem() {
	cout << "Enter file's name : ";
	getline(cin, binaryFilename);
	ifstream file(binaryFilename.c_str(), ios::binary);
	mkdir("root");
	chdir("root");
	root = new Node("root");
	if (file) {
		initTree(file);
	}
}
void FileSystem::del(Node*& root) {
	for (Node* node : root->children) {
		del(node);
	}
	delete root;
}
FileSystem::~FileSystem() {
	del(root);
}
void FileSystem::printFileSystem(Node* root) const {
	cout << root->data << " ";
	for (Node* node : root->children) {
		printFileSystem(node);
	}
}
void FileSystem::save(Node* root,ofstream& file,string& path) {
	for (Node* node : root->children) {
		path += '\\' + node->data;
		size_t size = path.size();
		file.write((const char*)&size, sizeof(size_t));
		file.write(path.c_str(), size);
		save(node, file, path);
		path.erase(path.size() - node->data.size());
		path.pop_back();
	}
}
void FileSystem::print(Node* currentPtrPosition) const {
	for (Node* child : currentPtrPosition->children) {
		cout << child->data << " ";
	}
	cout << endl;
}
void FileSystem::runFileSystem() {
	Node* currentPtrPosition = root;
	while (true) {
		string expression = console.getExpression();
		if (expression == "exit") {
			while (chdir("FileSystem")) {
				chdir("..");
			}
			ofstream file(binaryFilename.c_str(), ios::binary);
			string path;
			save(root, file, path);
			return;
		}
		int getArgumentsNumber = StringsHandling::getNumberOfSpaces(expression);
		string command = StringsHandling::getCommand(expression);
		if (getArgumentsNumber == 0) {
			commandsWithoutArgument(command, currentPtrPosition);
		}
		else if (getArgumentsNumber == 1) {
			commandsWithOneArgument(command,currentPtrPosition,expression);
		}
		else if (getArgumentsNumber == 2) {
			string firstArgument = StringsHandling::getCommand(expression);
			commandsWithTwoArguments(command, currentPtrPosition,firstArgument, expression);
		}
		else if (getArgumentsNumber == 3) {
			string firstArgument = StringsHandling::getCommand(expression);
			string secondArgument = StringsHandling::getCommand(expression);
			commandsWithThreeArguments(command, currentPtrPosition, firstArgument,secondArgument, expression);
		}
	}
}
void FileSystem::commandsWithoutArgument(const string& command, Node* currentPtrPosition) {
	if (command == "ls") {
		print(currentPtrPosition);
	}
}
void FileSystem::commandsWithOneArgument(const string& command, Node*& currentPtrPosition, string& expression) {
	const char* currentDirectory = StringsHandling::getCurrentDirectory();
	bool cdPass = false;
	if (expression[0] == '\\') {
		returnToStartDirectory(currentPtrPosition, expression);
	}
	if (command == "mkdir") {
		executeMkdir(expression, currentPtrPosition);
	}
	else if (command == "rmdir") {
		executeRmdir(expression, currentPtrPosition);
	}
	else if (command == "ls") {
		executeLs(expression, currentPtrPosition);
	}
	else if (command == "cd") {
		executeCd(expression, currentPtrPosition);
		cdPass = true;
	}
	else if (command == "rm") {
		executeRemoveFile(expression, currentPtrPosition);
	}
	else if (command == "cat") {
		executeCat(expression, currentPtrPosition);
	}
	else if (command == "write") {
		executeWrite(expression,"" ,currentPtrPosition);
	}
	if (!cdPass && _chdir(currentDirectory)) {
		FileNotFoundException();
	}
	delete[] currentDirectory;
}
void FileSystem::commandsWithTwoArguments(const string& command, Node*& currentPtrPosition,string& source,string& destination) {
	const char* currentDirectory = StringsHandling::getCurrentDirectory();
	Node* rootPtr = currentPtrPosition;
	if (source[0] == '\\') {
		returnToStartDirectory(currentPtrPosition, source);
	}
	if (command == "write") {
		StringsHandling::removeQuotationMarks(destination);
		executeWrite(source, destination, currentPtrPosition);
	}
	else if (command == "cp") {
		executeCP(source,destination,rootPtr,currentDirectory);
	}
	else if (command == "export") {
		executeExport(source, destination, currentPtrPosition);
	}
	else if (command == "import") {
		executeImport(source, destination, currentPtrPosition);
	}
	if (_chdir(currentDirectory)) {
		throw ChildNotExistException();
	}
	delete[] currentDirectory;
}
void FileSystem::commandsWithThreeArguments(const string& command, Node* currentPtrPosition,
	string& firstArgument, string& secondArgument, string& append) {
	if (command == "import") {
		commandsWithTwoArguments(command, currentPtrPosition, firstArgument, secondArgument);
		commandsWithTwoArguments("write", currentPtrPosition, secondArgument, append);
	}
}
Node* FileSystem::relativePath(string& expression,Node* rootPtr) {
	if (expression == "") {
		return rootPtr;
	}
	string fileName = StringsHandling::getFileName(expression);
	string workOnlyWithLowerCases = StringsHandling::toLower(fileName);
	if (_chdir(workOnlyWithLowerCases.c_str())) {
		throw ChildNotExistException();
	}
	bool findChild = false;
;	for (Node* child : rootPtr->children) {
		if (StringsHandling::compareFilesOrDirectories(fileName, child->data)) {
			findChild = true;
			rootPtr = relativePath(expression, child);
		}
	}
	if (!findChild) {
		throw logic_error("Invalid path");
	}
	return rootPtr;
}
void FileSystem::returnToStartDirectory(Node*& currentPtrPosition, string& expression) {
	expression.erase(0, 1);
	while (_chdir("root")) {
		if (_chdir("..")) {
			throw ChildNotExistException();
		}
	}
	currentPtrPosition = root;
}
void FileSystem::removeChildFromTree(Node*& currentPtrPosition, const string& name) {
	list<Node*>::iterator it = currentPtrPosition->children.begin();
	for (it; it != currentPtrPosition->children.end(); ++it) {
		if (StringsHandling::compareFilesOrDirectories((*it)->data,name)) {
			if ((*it)->children.size() == 0) {
				Node* detach = *it;
				currentPtrPosition->children.erase(it);
				delete detach;
				detach = nullptr;
				break;
			}
		}
	}
}
bool FileSystem::isExistFileInTheSystem(Node* currentRootPos, const string& fileName) const {
	if (currentRootPos == nullptr) {
		throw logic_error("nullptr exception");
	}
	for (Node* child : currentRootPos->children) {
		if (StringsHandling::compareFilesOrDirectories(child->data, fileName)) {
			return true;
		}
	}
	return false;
}
void FileSystem::executeLs(string& expression, Node* currentPtrPosition) {
	currentPtrPosition = relativePath(expression, currentPtrPosition);
	print(currentPtrPosition);
}
void FileSystem::executeRmdir(string& expression, Node* currentPtrPosition) {
	string filename = StringsHandling::getNewFileOrDirectoryName(expression);
	StringsHandling::removeLastFileOrDirectoryInThePath(expression, filename);
	currentPtrPosition = relativePath(expression, currentPtrPosition);
	if (!isExistFileInTheSystem(currentPtrPosition, filename)) {
		cout << "This file doesn't exist in the system" << endl;
		return;
	}
	string temporary = StringsHandling::toLower(filename);
	_rmdir(temporary.c_str());
	removeChildFromTree(currentPtrPosition, filename);
}
void FileSystem::executeMkdir(string& expression, Node* currentPtrPosition)  {
	string filename = StringsHandling::getNewFileOrDirectoryName(expression);
	StringsHandling::removeLastFileOrDirectoryInThePath(expression, filename);
	currentPtrPosition = relativePath(expression, currentPtrPosition);
	if (isExistFileInTheSystem(currentPtrPosition, filename)) {
		cout << "This file is already exist in the system" << endl;
		return;
	}
	string temporary = StringsHandling::toLower(filename);
	_mkdir(temporary.c_str());
	currentPtrPosition->children.push_back(new Node(filename));
}
void FileSystem::executeCat(string& path, Node* currentPtrPosition) {
	string filename = StringsHandling::getNewFileOrDirectoryName(path);
	StringsHandling::removeLastFileOrDirectoryInThePath(path, filename);
	currentPtrPosition = relativePath(path, currentPtrPosition);
	if (!isExistFileInTheSystem(currentPtrPosition, filename)) {
		cout << "This file doesn't exist in the system" << endl;
		return;
	}
	FilesHandling::deserialize(StringsHandling::toLower(filename));
}
void FileSystem::executeCd(string& expression, Node*& currentPtrPosition) {
	currentPtrPosition = relativePath(expression, currentPtrPosition);
}
void FileSystem::executeRemoveFile(string& expression, Node* currentPtrPosition) {
	string filename = StringsHandling::getNewFileOrDirectoryName(expression);
	StringsHandling::removeLastFileOrDirectoryInThePath(expression, filename);
	currentPtrPosition = relativePath(expression, currentPtrPosition);
	if (!isExistFileInTheSystem(currentPtrPosition, filename)) {
		cout << "This file doesn't exist in the system" << endl;
		return;
	}
	string temporary = StringsHandling::toLower(filename);
	remove(temporary.c_str());
	removeChildFromTree(currentPtrPosition, filename);
}
void FileSystem::executeWrite(string& path, const string& append, Node* currentPtrPosition) {
	string filename = StringsHandling::getNewFileOrDirectoryName(path);
	StringsHandling::removeLastFileOrDirectoryInThePath(path, filename);
	currentPtrPosition = relativePath(path, currentPtrPosition);
	if (!isExistFileInTheSystem(currentPtrPosition, filename)) {
		currentPtrPosition->children.push_back(new Node(filename));
	}
	string lowerCasesPath = StringsHandling::toLower(filename);
	ofstream file(lowerCasesPath.c_str(), ios::app);
	if (append.size() != 0) {
		file << append << endl;
	}
}
void FileSystem::executeExport(string& source, string& destination, Node* currentPtrPosition) {
	string filenameSource = StringsHandling::getNewFileOrDirectoryName(source);
	StringsHandling::removeLastFileOrDirectoryInThePath(source, filenameSource);
	currentPtrPosition = relativePath(source, currentPtrPosition);
	if (!isExistFileInTheSystem(currentPtrPosition, filenameSource)) {
		cout << "This file doesn't exist in the system" << endl;
		return;
	}
	FilesHandling::deserialize(StringsHandling::toLower(filenameSource), destination);
}
void FileSystem::executeImport(string& source, string destination,Node* currentPtrPosition) {
	string filenameDestination = StringsHandling::getNewFileOrDirectoryName(destination);
	StringsHandling::removeLastFileOrDirectoryInThePath(destination, filenameDestination);
	currentPtrPosition = relativePath(destination, currentPtrPosition);
	currentPtrPosition->children.push_back(new Node(filenameDestination));
	FilesHandling::deserialize(source, StringsHandling::toLower(filenameDestination));
}
void FileSystem::readFromFile(string& source, Node* currentPtrPosition, queue<string*>& fileLines) {
	string filenameSource = StringsHandling::getNewFileOrDirectoryName(source);
	StringsHandling::removeLastFileOrDirectoryInThePath(source, filenameSource);
	currentPtrPosition = relativePath(source, currentPtrPosition);
	if (!isExistFileInTheSystem(currentPtrPosition, filenameSource)) {
		throw FileNotFoundException();
	}
	FilesHandling::ChargingFileInMemory(fileLines, StringsHandling::toLower(filenameSource));
}
void FileSystem::writeInFile(string& destination, Node* currentPtrPosition, queue<string*>& fileLines) {
	string filenameDestination = StringsHandling::getNewFileOrDirectoryName(destination);
	StringsHandling::removeLastFileOrDirectoryInThePath(destination, filenameDestination);
	currentPtrPosition = relativePath(destination, currentPtrPosition);

	FilesHandling::serialize(fileLines, StringsHandling::toLower(filenameDestination));
	currentPtrPosition->children.push_back(new Node(filenameDestination));
}
void FileSystem::executeCP(string& source,string& destination,Node* currentPtrPosition,const char* currentDirectory) {
	queue<string* > fileLines;
	Node* rootPtr = currentPtrPosition;
	readFromFile(source, currentPtrPosition, fileLines);
	if (_chdir(currentDirectory)) {
		throw ChildNotExistException();
	}
	currentPtrPosition = rootPtr;
	if (destination[0] == '\\') {
		returnToStartDirectory(currentPtrPosition, destination);
	}
	writeInFile(destination, currentPtrPosition, fileLines);
}