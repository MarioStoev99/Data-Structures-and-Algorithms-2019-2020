#include "FindProteins.h"
/*
dna_sequence.txt
proteins.txt
codonToAminoacids.txt
4
34
12
2
52
*/
int main() {
	try {
		FindProteins proteins;
		proteins.findProteins();
	}
	catch(FileNotFoundException& e) {
		cout << e.what();
	}
	catch (logic_error & e) {
		cout << e.what();
	}
	catch (exception & e) {
		cout << e.what();
	}
	return 0;
}