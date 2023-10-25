//#include <vector>
//#include "Matrix.h"
//#include <iostream>
//#include <omp.h>
//
//using namespace std;
//
//Matrix::Matrix(int rowN, int colN, double init)
//{
//	/*if (rowN == colN)
//		throw 0;*/
//
//	v_t vec(rowN, vector<double>(colN, init));
//	data = vec;
//	rows = rowN;
//	columns = colN;
//}
//
//Matrix::Matrix(v_t vec) : rows{ vec.size() }, columns{ vec[0].size() }, data{ vec }
//{
//}
//
//Matrix::~Matrix()
//{
//}
//
//vector<double>& Matrix::operator[](int ind)
//{
//	return data[ind];
//}
//
//const vector<double>& Matrix::operator[](int ind) const
//{
//	return data[ind];
//}
//
//int Matrix::getN()
//{
//	return rows;
//}
//
//int Matrix::getM()
//{
//	return columns;
//}
//
//void Matrix::print()
//{
//	for (int i = 0; i < this->rows; ++i) {
//		for (int j = 0; j < this->columns; j++) {
//			cout << data[i][j] << " ";
//		}
//		cout << endl;
//	}
//	
//}
//
//Matrix par_mul_matr(const Matrix& m1, const Matrix& m2, int num_threads)
//{
//	if (m1.columns != m2.rows) {
//		throw 1;
//	}
//	int threads = num_threads;
//	omp_set_num_threads(threads);
//
//	Matrix mRes(m1.rows, m2.columns);
//
//	int i, j, k;
//#pragma omp parallel for shared(m1, m2, mRes) private(i, j, k)
//	for (i = 0; i < m1.rows; i++) {
//		for (j = 0; j < m2.columns; j++) {
//			for (k = 0; k < m1.columns; k++)
//				mRes[i][j] += m1[i][k] * m2[k][j];
//		}
//	}
//	return mRes;
//}
//
//Matrix operator*(const Matrix& m1, const Matrix& m2)
//{
//	if (m1.columns != m2.rows) {
//		throw 1;
//	}
//
//	Matrix mRes(m1.rows, m2.columns);
//	
//	for (int i = 0; i < m1.rows; i++) {
//		for (int j = 0; j < m2.columns; j++) {
//			for (int k = 0; k < m1.columns; k++)
//				mRes[i][j] += m1[i][k] * m2[k][j];
//		}
//	}
//	return mRes;
//}
//
//
//
//std::ostream& operator<< (ostream& out, const Matrix& m)
//{
//	for (int i = 0; i < m.rows; ++i) {
//		for (int j = 0; j < m.columns; j++) {
//			out << m[i][j] << " ";
//		}
//		out << endl;
//	}
//	return out;
//}
