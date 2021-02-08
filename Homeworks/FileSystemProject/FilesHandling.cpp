#include "FilesHandling.h"

void FilesHandling::deserialize(const string& source) {
	ifstream file(source.c_str());
	if (!file) {
		throw FileNotFoundException();
	}
	while (!file.eof()) {
		string line;
		getline(file, line);
		cout << line << endl;
	}
}
void FilesHandling::deserialize(const string& source, const string& destination) {
	ifstream readFromSource(source.c_str());
	ofstream writeInDestination(destination.c_str());
	if (!readFromSource) {
		throw FileNotFoundException();
	}
	while (!readFromSource.eof()) {
		string line;
		getline(readFromSource, line);
		writeInDestination << line << endl;
	}
}
void FilesHandling::ChargingFileInMemory(queue<string*>& fileLines,const string& source) {
	ifstream file(source.c_str());
	if (!file) {
		throw FileNotFoundException();
	}
	while (!file.eof()) {
		string* line = new string;
		getline(file, *line);
		fileLines.push(line);
	}
}
void FilesHandling::serialize(queue<string*>& fileLines, const string& source) {
	ofstream file(source.c_str());
	if (!file) {
		throw FileNotFoundException();
	}
	while (!fileLines.empty()) {
		string* ptr = fileLines.front();
		fileLines.pop();
		file << *ptr << endl;
		delete ptr;
		ptr = nullptr;
	}
}