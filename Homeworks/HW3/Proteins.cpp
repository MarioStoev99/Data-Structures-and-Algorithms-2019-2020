#include "Proteins.h"

Proteins::Proteins(size_t _capacity) : hashTable(_capacity), size(0), capacity(_capacity) { }
int Proteins::hashFunction(unsigned long key) const {
	return key % capacity;
}
void Proteins::put(unsigned long key, const string& data) {
	if (key < 0) {
		return;
	}
	// load factor
	if (size / capacity > 0.7) {
		resize();
	}
	int index = hashFunction(key);
	while (!(hashTable[index].data).empty()) {
		index = (index + 1) % hashTable.size();
	}
	hashTable[index].data = data;
	hashTable[index].key = key;
	++size;
}
string Proteins::get(unsigned long key) const {
	if (key < 0) {
		throw logic_error("invalid key");
	}
	int sizeOfTable = hashTable.size();
	int index = hashFunction(key);
	while (hashTable[index].key != key && sizeOfTable) {
		index = (index + 1) % hashTable.size();
		--sizeOfTable;
	}
	if (hashTable[index].key == key) {
		return hashTable[index].data;
	}
	return "";
}
void Proteins::resize() {
	Proteins newProteins(hashTable.size() * 2);
	capacity = hashTable.size() * 2;
	for (const table_elem& elem : hashTable) {
		if (!elem.data.empty()) {
			newProteins.put(elem.key, elem.data);
		}
	}
	newProteins.hashTable.swap(hashTable);
}