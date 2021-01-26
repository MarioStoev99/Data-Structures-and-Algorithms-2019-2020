#include "Aminoacids.h"

Aminoacids::Aminoacids(int _capacity) : hashTable(_capacity) { }
int Aminoacids::hashFunction(const string& key) const {
	int res = 0;
	int number = 31 * 31 * 31;
	for (int i = 0; i < key.size(); ++i) {
		res += key[i] * number;
		number /= 31;
	}
	return res % hashTable.size();
}
void Aminoacids::put(const string& key, char data) {
	if (key.empty()) {
		throw logic_error("invalid key");
	}
	int index = hashFunction(key);
	hashTable[index] = data;
}
char Aminoacids::get(const string& key) const {
	if (key.empty()) {
		throw logic_error("invalid key");
	}
	return hashTable[hashFunction(key)];
}
