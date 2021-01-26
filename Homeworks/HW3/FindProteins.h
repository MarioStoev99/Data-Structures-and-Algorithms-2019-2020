#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "FileNotFoundException.hpp"
#include "Aminoacids.h"
#include "Proteins.h"

class FindProteins
{
private : 
	struct ProteinInfo {
		int id;
		short posInSequence;
		vector<string> aminoacidsInProtein;
	};
private :
	string dna_sequence;
	Aminoacids aminoacids;
	Proteins proteins;
	vector<ProteinInfo> findRequests;
	string proteinsFilename;

private : 
	static const int notExistInFile;
	static const int notExistInSequence;
private : 
	void takeOutAminoacidsFromProtein(ProteinInfo& protein, const string& prot);
	void deserializeProteins();
	void deserializeAminoacids(const string& filename);
	void deserializeDNASequence(const string& filename);
	void inputLogic(string& dnaSequence, string& codonToAminoacids);
	void findTheBeginningOfEveryProteinInTheSequence();
public :
	FindProteins();
	void findProteins();
};

