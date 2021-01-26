#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

typedef vector<vector<int>> Matrix;
Matrix createGraph() {
	ifstream file("graph.txt");
	if (!file) {
		throw logic_error("this file doesn't exist");
	}
	int size;
	file >> size;
	Matrix matrix(size,vector<int>(size,100));
	while (!file.eof()) {
		int v1, v2, edge;
		file >> v1 >> v2 >> edge;
		matrix[v1][v2] = edge;
	}
	return matrix;
}
void print(const Matrix& matrix) {
	for (int i = 0; i < matrix.size(); ++i) {
		for (int j = 0; j < matrix.size(); ++j) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}
void Floyd(Matrix& matrix) {
	for (int i = 0; i < matrix.size(); ++i) {
		for (int j = 0; j < matrix.size(); ++j) {
			for (int k = 0; k < matrix.size(); ++k) {
				if (i != j && j != k && k != i) {
					if (matrix[j][k] > matrix[j][i] + matrix[i][k]) {
						matrix[j][k] = matrix[j][i] + matrix[i][k];
					}
				}
			}
		}
	}
	print(matrix);
}
int main() {
	try {
		Matrix graph = createGraph();
		Floyd(graph);
	}
	catch (logic_error & e) {
		cout << e.what();
	}
	return 0;
}