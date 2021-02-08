#include <iostream>
#include "FileSystem.h"
using namespace std;

int main() {
	try {
		FileSystem system;
		system.runFileSystem();
	}
	catch (CommandNotFoundException& e) {
		cout << e.what();
	}
	catch (InvalidArgumentsOfCommand& e) {
		cout << e.what();
	}
	catch (exception & e) {
		cout << e.what();
	}
	return 0;
}