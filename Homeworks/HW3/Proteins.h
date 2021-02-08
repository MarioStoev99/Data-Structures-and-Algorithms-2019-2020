#pragma once
#include<iostream>
#include <vector>

using namespace std;

class Proteins
{
private:
	struct table_elem {
		unsigned long key;
		string data;
	};
	int hashFunction(unsigned long key) const;
	void resize();
private:
	vector<table_elem> hashTable;
	size_t capacity;
	size_t size;
public:
	explicit Proteins(size_t _capacity = 8);
	void put(unsigned long key, const string& data);
	string get(unsigned long key) const;
};
