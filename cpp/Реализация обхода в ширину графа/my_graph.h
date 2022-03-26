#pragma once
#include <string>
#include <vector>

using namespace std;

class my_graph
{
private:
	// Матрица смежности.
	vector<vector<int> > adj_matr;

	vector<pair<int, int>> edges;
	
	// Размерность матрицы смежности size x size.
	int size;

	// Функция, высчитывающая из текстового файла размерность матрицы смежности.

	int solve_size(string filename);
	// Функция, считывающая из текстового файла матрицу смежности.

	void read_matrix(string filename, vector<vector<int> >& adj_matr, int size);
	// Функция, проверяющая валидность данных текстового файла, содержащего матрицу смежности.

	bool check_adj_matr_symm(vector<vector<int> >& adj_matr, int size);

public:
	// Конструктор класса, принимающий на вход текстовый файл, содержащий матрицу смежности.
	my_graph(string filename);

	// Обход в ширину графа.
	vector<int> bread_first_search();

	// Функция вывода на консоль матрицы смежности.
	void print();

	vector<vector<int>> get_adj_matr();

	vector<pair<int, int>> get_edges();
};

