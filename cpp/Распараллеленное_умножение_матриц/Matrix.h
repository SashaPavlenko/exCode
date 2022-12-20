#pragma once

#include <vector>
#include <iostream>

using namespace std;

typedef vector<vector<double>> v_t;

#pragma once
class Matrix
{
private:
	v_t data;
	size_t rows;
	size_t columns;

public:
	Matrix(int rowN, int colN, double init=0);
	Matrix(v_t vec);
	~Matrix();

	int getN();
	int getM();

	friend Matrix par_mul_matr(const Matrix& m1, const Matrix& m2, int num_threads);

	vector<double>& operator[](int ind);
	const vector<double>& operator[](int ind) const;
	friend Matrix operator*(const Matrix& m1, const Matrix& m2);
	friend ostream& operator<< (std::ostream& out, const Matrix& m);

	void print();
};

