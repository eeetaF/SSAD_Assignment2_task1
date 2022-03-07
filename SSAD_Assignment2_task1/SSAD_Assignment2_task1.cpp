#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <cstdio>
using namespace std;

bool is_legal_character(char c) {
	if ((c >= '0' && c <= '9') || c == '-')
		return 1;
	return 0;
}
void add_many_rows(double** matrix, int MATRIX_SIZE, int row_to_add, int row_from_which_to_add, double many_times) {
	for (int i = 0; i < MATRIX_SIZE; i++)
		matrix[row_to_add][i] += many_times * matrix[row_from_which_to_add][i];
}
void matrix_inverse(double** matrix, int MATRIX_SIZE) {
	double** inv_matrix = new double* [MATRIX_SIZE];
	for (int i = 0; i < MATRIX_SIZE; i++)
		inv_matrix[i] = new double[MATRIX_SIZE];
	for (int i = 0; i < MATRIX_SIZE; i++)
		for (int j = 0; j < MATRIX_SIZE; j++)
			inv_matrix[i][j] = (i == j ? 1 : 0);

	// to echelon
	for (int i = 0; i < MATRIX_SIZE; i++) {
		for (int j = 0; j < i; j++) {
			if (matrix[i][j] == 0)
				continue;
			if (matrix[j][j] == 0) {
				add_many_rows(matrix, MATRIX_SIZE, j, i, 1.0);
				add_many_rows(inv_matrix, MATRIX_SIZE, j, i, 1.0);
			}
			double many = matrix[i][j] / matrix[j][j];
			add_many_rows(matrix, MATRIX_SIZE, i, j, -many);
			add_many_rows(inv_matrix, MATRIX_SIZE, i, j, -many);
		}
	}
	// to diagonal
	for (int i = MATRIX_SIZE - 1; i >= 0; i--) {
		for (int j = MATRIX_SIZE - 1; j > i; j--) {
			if (matrix[i][j] == 0)
				continue;
			double many = matrix[i][j] / matrix[j][j];
			add_many_rows(matrix, MATRIX_SIZE, i, j, -many);
			add_many_rows(inv_matrix, MATRIX_SIZE, i, j, -many);
		}
	}
	// to identity
	for (int i = 0; i < MATRIX_SIZE; i++)
		for (int j = 0; j < MATRIX_SIZE; j++)
			inv_matrix[i][j] /= matrix[i][i];

	FILE* out = fopen("output.txt", "w");
	for (int i = 0; i < MATRIX_SIZE; i++) {
		for (int j = 0; j < MATRIX_SIZE; j++) {
			fprintf(out, "%.2f ", inv_matrix[i][j]);
		}
		fprintf(out, "\n");
	}

	for (int i = 0; i < MATRIX_SIZE; i++)
		delete[] inv_matrix[i];
	delete[] inv_matrix;
	fclose(out);
}
int main() {
	ifstream inp("input.txt");
	
	string s;
	int n = 1;
	while (getline(inp, s, ','))
		n++;
	int MATRIX_SIZE = sqrt(n);
	
	inp.close();
	inp.open("input.txt");

	double** matrix = new double*[MATRIX_SIZE];
	for (int i = 0; i < MATRIX_SIZE; i++)
		matrix[i] = new double[MATRIX_SIZE];

	for (int i = 0; i < MATRIX_SIZE; i++) {
		for (int j = 0; j < MATRIX_SIZE; j++) {
			getline(inp, s, ',');
			while (!is_legal_character(s[0]))
				s.erase(0, 1);
			while (!is_legal_character(s[s.length() - 1]))
				s.pop_back();
			matrix[i][j] = stod(s);
		}
	}

	matrix_inverse(matrix, MATRIX_SIZE);

	for (int i = 0; i < MATRIX_SIZE; i++)
		delete[] matrix[i];
	delete[] matrix;
	inp.close();
	return 0;
}