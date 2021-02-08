#pragma once
#include<iostream>
#include <vector>
#include <cmath>
using namespace std;

class Aminoacids
{
	int hashFunction(const string& key) const;
private:
	vector<char> hashTable;
public:
	explicit Aminoacids(int _capacity = 209);
	void put(const string& key, char data);
	char get(const string& key) const;
};