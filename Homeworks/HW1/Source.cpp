#include <iostream>
#include <fstream>
#include "Building.h"
#include "FileNotFoundException.hpp"

using namespace std;
const size_t MAX_SIZE = 100;

int main() {
	char filename[MAX_SIZE];
	cin.getline(filename, MAX_SIZE);
	try {
		Building building(filename);
		building.runRequests();
	} catch (logic_error& e) {
		cout << e.what();
	} catch (FileNotFoundException& e) {
		cout << e.what();
	} catch (exception& e) {
		cout << e.what();
	}
	return 0;
}