#pragma once
#include <string>
#include <vector>

using namespace std;

class my_graph
{
private:
	// ������� ���������.
	vector<vector<int> > adj_matr;

	vector<pair<int, int>> edges;
	
	// ����������� ������� ��������� size x size.
	int size;

	// �������, ������������� �� ���������� ����� ����������� ������� ���������.

	int solve_size(string filename);
	// �������, ����������� �� ���������� ����� ������� ���������.

	void read_matrix(string filename, vector<vector<int> >& adj_matr, int size);
	// �������, ����������� ���������� ������ ���������� �����, ����������� ������� ���������.

	bool check_adj_matr_symm(vector<vector<int> >& adj_matr, int size);

public:
	// ����������� ������, ����������� �� ���� ��������� ����, ���������� ������� ���������.
	my_graph(string filename);

	// ����� � ������ �����.
	vector<int> bread_first_search();

	// ������� ������ �� ������� ������� ���������.
	void print();

	vector<vector<int>> get_adj_matr();

	vector<pair<int, int>> get_edges();
};

