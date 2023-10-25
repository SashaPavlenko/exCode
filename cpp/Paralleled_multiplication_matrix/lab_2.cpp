#include <iostream>
#include <omp.h>
#include <vector>
#include <ctime>
#include <string>

using namespace std;

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
	Matrix(int rowN, int colN, double init = 0);
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



int main() {

	/*Matrix m1(5, 2, 1);
	Matrix m2(2, 4, 2);

	cout << m1 << endl << m2 << endl << (m1 * m2) << endl << par_mul_matr(m1, m2, 4);*/

	int n, m, p;
	vector<int> N{ 200, 300, 700, 800 };
	//n = m = p = 500;

	for (auto num : N) {
		n = m = p = num;
		vector<vector<double>> res(4, vector<double>());

		printf("N = %d\n", num);
		for (int i = 0; i < 4; ++i) {
			double val1{ test_time_matrix(n, m, p, matrix_mult::def, 1) };
			double val2{ test_time_matrix(n, m, p, matrix_mult::par_for, 2) };
			double val3{ test_time_matrix(n, m, p, matrix_mult::par_for, 3) };
			//double val1{ 0. };
			double val4{ test_time_matrix(n, m, p, matrix_mult::par_for, 4) };


			res[0].push_back(val1);
			res[1].push_back(val2);
			res[2].push_back(val3);
			res[3].push_back(val4);

			printf("Test %d for matrix of %dx%d * %dx%d\n_____________________\n", i + 1, n, m, m, p);
			printf("Paralleled 1 threads: %f\n", val1);
			printf("Paralleled 2 threads: %f\n", val2);
			printf("Paralleled 3 threads: %f\n", val3);
			printf("Paralleled 4 threads: %f\n-----------------\n", val4);
		}

		double av1, av2, av3, av4;
		av1 = (res[0][0] + res[0][1] + res[0][2] + res[0][3]) / 4.;
		av2 = (res[1][0] + res[1][1] + res[1][2] + res[1][3]) / 4.;
		av3 = (res[2][0] + res[2][1] + res[2][2] + res[2][3]) / 4.;
		av4 = (res[3][0] + res[3][1] + res[3][2] + res[3][3]) / 4.;

		printf("N = %d\npar 1 threads average = %f\n", num, av1);
		printf("N = %d\npar 2 threads average = %f\n", num, av2);
		printf("N = %d\npar 3 threads average = %f\n", num, av3);
		printf("N = %d\npar 4 threads average = %f\n", num, av4);

		cout << "________________________________\n";
	}
	return 0;
}

Matrix::Matrix(int rowN, int colN, double init)
{
	/*if (rowN == colN)
		throw 0;*/

	v_t vec(rowN, vector<double>(colN, init));
	data = vec;
	rows = rowN;
	columns = colN;
}

Matrix::Matrix(v_t vec) : rows{ vec.size() }, columns{ vec[0].size() }, data{ vec }
{
}

Matrix::~Matrix()
{
}

vector<double>& Matrix::operator[](int ind)
{
	return data[ind];
}

const vector<double>& Matrix::operator[](int ind) const
{
	return data[ind];
}

int Matrix::getN()
{
	return rows;
}

int Matrix::getM()
{
	return columns;
}

void Matrix::print()
{
	for (int i = 0; i < this->rows; ++i) {
		for (int j = 0; j < this->columns; j++) {
			cout << data[i][j] << " ";
		}
		cout << endl;
	}

}

Matrix par_mul_matr(const Matrix& m1, const Matrix& m2, int num_threads)
{
	if (m1.columns != m2.rows) {
		throw 1;
	}
	int threads = num_threads;
	omp_set_num_threads(threads);

	Matrix mRes(m1.rows, m2.columns);

	int i, j, k;
#pragma omp parallel for shared(m1, m2, mRes) private(i, j, k)
	for (i = 0; i < m1.rows; i++) {
		for (j = 0; j < m2.columns; j++) {
			for (k = 0; k < m1.columns; k++)
				mRes[i][j] += m1[i][k] * m2[k][j];
		}
	}
	return mRes;
}

Matrix operator*(const Matrix& m1, const Matrix& m2)
{
	if (m1.columns != m2.rows) {
		throw 1;
	}

	Matrix mRes(m1.rows, m2.columns);

	for (int i = 0; i < m1.rows; i++) {
		for (int j = 0; j < m2.columns; j++) {
			for (int k = 0; k < m1.columns; k++)
				mRes[i][j] += m1[i][k] * m2[k][j];
		}
	}
	return mRes;
}



std::ostream& operator<< (ostream& out, const Matrix& m)
{
	for (int i = 0; i < m.rows; ++i) {
		for (int j = 0; j < m.columns; j++) {
			out << m[i][j] << " ";
		}
		out << endl;
	}
	return out;
}
