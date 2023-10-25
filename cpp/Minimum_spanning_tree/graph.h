#include <vector>
#include <string>
#include <queue>

#pragma once

using namespace std;

class graph {
public:
	enum class type_out
	{
		adj_matr,
		adj_list,
		adj_list_points,
	};

	enum class type_in {
		list_vert,
		list_coord,
		glossary,
		floors,
	};

	enum class status_vert {
		unvisited,
		visited,
		procceced,
	};
private:
	vector<vector<int>> adj_matr;
	vector<string> names;
	type_out type;

	void BFS_Vist(int i, vector<graph::status_vert>& status, vector<int>& pred, queue<int>& q, vector<vector<int>>& predList, vector<int>& order, int def_no_edje = 0);
	string BFS_Vist_loop_out(int i, vector<graph::status_vert>& status, vector<int>& pred, queue<int>& q, vector<vector<int>>& predList);
	void DFS_Top_sort_Visit(int v, vector<graph::status_vert>& status, vector<int>& pred, vector<int>& Time_in, vector<int>& Time_out, vector<int>& TopNum, int& CurTime, int& CurTopNum);

	friend int find_name(vector<string> vec, string name);
	friend int find_diff_floor(const string& s1, const string& s2);

public:
	void Updare_C_P(priority_queue< pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>& pq, std::vector<bool>& inMST, std::vector<int>& C, std::vector<int>& R);
	graph(vector<vector<int>> in_info, vector<string> in_name);
	graph(string filename, type_in type_in=type_in::list_vert);
	~graph();

	int get_num_V(string V);

	void set_type(type_out type);
	type_out get_type();
	int get_num_V();
	int get_total_weights(int def_no_edje=0);

	vector<vector<int>> BFS(int def_no_edje=0);
	string BFS_loop();

	vector<string> DFS_Top_sort();

	graph PRIM();
	string task4();

	friend ostream& operator<< (std::ostream& out, const graph& gr);
};

typedef graph::status_vert stv_t;