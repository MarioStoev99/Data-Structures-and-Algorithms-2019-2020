#include "FindProteins.h"
const int FindProteins::notExistInSequence = -1;
const int FindProteins::notExistInFile = -2;
void FindProteins::inputLogic(string& filenameSequence,string& filenameCodonToAminoacids) {
	getline(cin, filenameSequence);
	getline(cin, proteinsFilename);
	getline(cin, filenameCodonToAminoacids);
	int numberOfProteints;
	cin >> numberOfProteints;
	for (int i = 0; i < numberOfProteints; ++i) {
		ProteinInfo protein;
		cin >> protein.id;
		findRequests.push_back(protein);
	}
}
void FindProteins::deserializeProteins() {
	ifstream file(proteinsFilename.c_str());
	if (!file) {
		FileNotFoundException();
	}
	while (!file.eof()) {
		unsigned long key;
		string protein;
		file >> key;
		file.get();
		getline(file, protein);
		proteins.put(key, protein);
	}
}
void FindProteins::deserializeAminoacids(const string& filename) {
	ifstream file(filename.c_str());
	if (!file) {
		FileNotFoundException();
	}
	while (!file.eof()) {
		string word;
		char key;
		getline(file, word, ' ');
		file >> key;
		file.get();
		aminoacids.put(word, key);
	}
}
void FindProteins::deserializeDNASequence(const string& filename) {
	ifstream file(filename.c_str());
	if (!file) {
		throw FileNotFoundException();
	}
	getline(file, dna_sequence);
}
void FindProteins::takeOutAminoacidsFromProtein(ProteinInfo& protein,const string& prot) {
	string amino;
	for (char nucleotideBase : prot) {
		amino += nucleotideBase;
		if (amino.size() == 3) {
			protein.aminoacidsInProtein.push_back(amino);
			amino.clear();
		}
	}
}
void FindProteins::findTheBeginningOfEveryProteinInTheSequence() {
	for (ProteinInfo& protein : findRequests) {
		string prot = proteins.get(protein.id);
		if (prot.empty()) {
			protein.posInSequence = -2;
		}
		else {
			protein.posInSequence = dna_sequence.find(prot);
			if (protein.posInSequence > 0) {
				takeOutAminoacidsFromProtein(protein, prot);
			}
 		}
	}
}
FindProteins::FindProteins() {
	string dnaSequence, codonToAminoacids;
	inputLogic(dnaSequence, codonToAminoacids);
	deserializeDNASequence(dnaSequence);
	deserializeProteins();
	deserializeAminoacids(codonToAminoacids);
}
void FindProteins::findProteins() {
	findTheBeginningOfEveryProteinInTheSequence();
	for (const ProteinInfo& protein : findRequests) {
		if (protein.posInSequence == notExistInFile) {
			cout << "No protein in " << proteinsFilename << " with id " << protein.id << endl;
		}
		else if (protein.posInSequence == notExistInSequence) {
			cout << "No" << endl;
		}
		else {
			cout << "Yes " << protein.posInSequence << " ";
			for (const string& amino : protein.aminoacidsInProtein) {
				char c = aminoacids.get(amino);
				if (c != '*') {
					cout << c;
				}
			}
			cout << endl;
		}
	}
}
