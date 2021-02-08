#include <iostream>
#include "ColorfulNecklaces.h"
using namespace std;

int main() {

	try {
		ColorfulNecklaces necklaces("test.txt");
		necklaces.reworkPresents();
	}
	catch (FileNotFoundException & e) {
		cout << e.what();
	}
	catch (logic_error & e) {
		cout << e.what();
	}
	catch (exception& e) {
		cout << e.what();
	}
	return 0;
}