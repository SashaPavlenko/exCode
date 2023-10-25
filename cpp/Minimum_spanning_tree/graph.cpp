#include <vector>
#include "graph.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include "Point.h"
#include <queue>
#include <set>
#include <cassert>
#include <list>

using namespace std;

int find_name(vector<string> vec, string name)
{
	vector<string>::iterator it = find(begin(vec), end(vec), name);

	return (it - begin(vec));
}

int find_diff_floor(const string& s1, const string& s2)
{
	int n{ static_cast<int>(s1.size()) };
	if (s1.size() != s2.size())
		if (s1.size() < s2.size())
			n = s2.size();

	int count{ 0 };
	for (int i = 0; i < n; ++i)
		if (s1[i] != s2[i])
			count++;

	return count;
}

void graph::BFS_Vist(int i, vector<graph::status_vert>& status, vector<int>& pred, queue<int>& q, vector<vector<int>>& predList, vector<int>& order, int def_no_edje)
{
	q.push(i);
	while (!q.empty())	
	{

		int v{ q.front() };
		//cout << Point(names[v]) << " ";
		q.pop();

		vector<int> way;

		for (int u = 0; u < adj_matr[v].size(); u++)
		{
			// 
			if (adj_matr[v][u] != def_no_edje) {
				if (status[u] == stv_t::unvisited) {
					status[u] = stv_t::visited;
					pred[u] = v;
					q.push(u);

					int index{ u };
					while (pred[index] != -1) {
						predList[u].push_back(pred[index]);
						index = pred[index];
					}
				}
			}
		}
		status[v] = stv_t::procceced;
		order.push_back(v);
	}
}

string graph::BFS_Vist_loop_out(int i, vector<graph::status_vert>& status, vector<int>& pred, queue<int>& q, vector<vector<int>>& predList)
{
	string loop;
	stringstream stream(loop);

	q.push(i);
	while (!q.empty())
	{


		int v{ q.front() };
		q.pop();

		vector<int> way;

		for (int u = 0; u < adj_matr[v].size() && loop == ""; u++)
		{
			if (adj_matr[v][u] != 0) {
				if (status[u] == stv_t::unvisited) {
					status[u] = stv_t::visited;
					pred[u] = v;
					q.push(u);

					int index{ u };
					while (pred[index] != -1) {
						predList[u].push_back(pred[index]);
						index = pred[index];
					}
				}
				// Проверяем наличие цикла.
				else if (pred[v] != u) {
					int index_u{ static_cast<int>(predList[u].size() - 1) }, index_v{ static_cast<int>(predList[v].size() - 1) };
					while (index_u > 0 && index_v > 0 && predList[u][index_u - 1] == predList[v][index_v - 1]) {
						index_u--;
						index_v--;
					}

					way.push_back(u);
					for (int k = 0; k <= index_u; ++k) {
						//cout << predList[u][k] << " ";
						way.push_back(predList[u][k]);
					}

					for (int k = index_v; k > 0; --k) {
						//cout << predList[v][k] << " ";
						way.push_back(predList[v][k]);
					}
					way.push_back(v);


					stream << way.size() << endl;
					for (auto& k : way) {
						stream << names[k] << endl;
					}

					loop = stream.str();

				}
			}
		}
		status[v] = stv_t::procceced;
	}

	return loop;
}

graph::graph(vector<vector<int>> in_info, vector<string> in_names): adj_matr {in_info}, names{in_names}, type{ type_out::adj_list }
{
}

graph::graph(string filename, type_in type_in) : type{type_out::adj_matr}
{
	switch (type_in)
	{
	case graph::type_in::list_vert:
	{
		ifstream fin(filename);
		string str;
		vector<string> names;

		// Считываем имена вершин.
		getline(fin, str);
		stringstream stream(str);
		int index{ -1 };
		for_each(istream_iterator<string>(stream), istream_iterator<string>(),
			[&](auto word) {
				auto pos = str.find(word, index + 1);
				if (pos != string::npos) {
					names.push_back(word);
				}
				index = pos;
			}
		);

		this->names = names;
		int size = this->names.size();

		// Инициализируем матрицу смежности.
		vector<vector<int>> am(size, vector<int>(size, 0));
		this->adj_matr = am;

		// Считываем список ребер, записываем в матрицу смежности.
		string in_v, out_v;
		while (!fin.eof()) {
			str = "";
			getline(fin, str);
			stringstream stream(str);
			stream >> out_v >> in_v;
			auto it_out = find(begin(this->names), end(this->names), out_v);
			auto it_in = find(begin(this->names), end(this->names), in_v);

			int index_out{ it_out - begin(this->names) }, index_in{ it_in - begin(this->names) };
			this->adj_matr[index_out][index_in] = 1;
			this->adj_matr[index_in][index_out] = 1;
		}
	}
		break;
	case graph::type_in::list_coord:
	{
		ifstream fin(filename);
		string str;
		vector<string> names;

		int count;
		fin >> count;

		// Считываем имена за первую проходку.
		int d1, d2, d3, d4;
		for (int i = 0; i < count; ++i) {
			fin >> d1 >> d2 >> d3 >> d4;

			string new_name1{ to_string(d1) + " " + to_string(d2) }, new_name2{ to_string(d3) + " " + to_string(d4) };
			if (find_name(names, new_name1) == names.size()) {
				names.push_back(new_name1);
			}
			if (find_name(names, new_name2) == names.size()) {
				names.push_back(new_name2);
			}
			
		}

		this->names = names;

		fin.close();
		fin.open(filename);
		fin >> count;

		int size = this->names.size();
		vector<vector<int>> am(size, vector<int>(size, 0));
		this->adj_matr = am;

		// Заполняем матрицу смежности
		for (int i = 0; i < count; ++i) {
			fin >> d1 >> d2 >> d3 >> d4;
			string new_name1{ to_string(d1) + " " + to_string(d2) }, new_name2{ to_string(d3) + " " + to_string(d4) };
			int ind1{ find_name(this->names, new_name1) }, ind2	{ find_name(this->names, new_name2) };
			
			this->adj_matr[ind1][ind2] = this->adj_matr[ind2][ind1] = 1;
		}
	}
		break;
	case graph::type_in::glossary: {
		ifstream fin(filename);
		string str;
		vector<string> names;

		int count, l1, l2;
		fin >> count;

		vector<pair<char, char>> edges;
		string s_prev, s_next;

		// Считываем имена, запоминаем ребра: первое несовпадение букв в соседних словах.
		fin >> s_prev;
		set<char> nms;

		for (auto j : s_prev)
			nms.insert(j);

		for (int i = 1; i < count; s_prev=s_next, ++i) {
			fin >> s_next;

			l1 = s_prev.length();
			l2 = s_next.length();
			int ind{ 0 };

			for (auto j : s_next)
				nms.insert(j);

			while (ind < l1 && ind < l2 && s_prev[ind] == s_next[ind])
				ind++;

			if (ind < s_prev.size() and (l1 != ind or l2 != ind)) {
				pair<char, char> new_edge(s_prev[ind], s_next[ind]);
				edges.push_back(new_edge);
			}
		}

		for (auto nm : nms) {
			string nm1;
			nm1.push_back(nm);
			names.push_back(nm1);
		}

		//copy(begin(nms), end(nms), back_inserter(names));

		this->names = names;

		fin.close();
		fin.open(filename);
		fin >> count;

		int size = this->names.size();
		vector<vector<int>> am(size, vector<int>(size, 0));
		this->adj_matr = am;

		for (const auto edge : edges) {
			string v1, v2;
			v1.push_back(edge.first);
			v2.push_back(edge.second);
			int ind1{ find_name(this->names, v1) }, ind2{ find_name(this->names, v2) };
			this->adj_matr[ind1][ind2] = 1;

		}
		break;
	}

	case graph::type_in::floors:
	{
		ifstream fin(filename);

		if (fin.is_open()) {
			vector<string> names;
			string str;

			int n, m, k, w, ind{ 0 };
			fin >> n >> m >> k >> w;

			vector<string> floors(k, "");

			int i, j;
			for (int i1 = 0; i1 < k; ++i1) {
				for (i = 0; i < n; ++i) {
					for (j = 0; j < m; ++j) {
						char c;
						fin >> c;

						floors[ind] += c;
					}
				}
				ind++;
			}

			for (int i = 0; i <= k; ++i)
				names.push_back(to_string(i));
			this->names = names;
			
			this->adj_matr = vector<vector<int>>(k + 1, vector<int>(k + 1, -1));
			for (int i = 0; i < floors.size(); ++i) {
				for (int j = 0; j < floors.size(); ++j)
				{
					int diff;
					if (j != i) {
						diff = find_diff_floor(floors[i], floors[j]);
						adj_matr[i+1][j+1] = diff*w;
						adj_matr[j+1][i+1] = diff*w;
					}
				}
			}

			for (int i = 1; i < adj_matr.size(); ++i) {
				adj_matr[0][i] = adj_matr[i][0] = n * m;
			}

		}
		else{
			throw 0;
		}
	}

	break;
	default:
		break;
	}
}

graph::~graph()
{
}

int graph::get_num_V(string V)
{
	auto it = find(begin(this->names), end(this->names), V);

	int index{ it - begin(this->names) };
	return index;
}

void graph::set_type(type_out type)
{
	this->type = type;
}

graph::type_out graph::get_type()
{
	return this->type;
}

int graph::get_num_V()
{
	return adj_matr.size();
}

int graph::get_total_weights(int def_no_edje)
{
	int sum{ 0 };
	for (int i = 0; i < names.size(); ++i) {
		for (int j = 0; j < names.size(); ++j)
			if (adj_matr[i][j] != def_no_edje)
				sum += adj_matr[i][j];
	}

	return sum;
}

vector<vector<int>> graph::BFS(int def_no_edje)
{
	int num_V{ static_cast<int>(adj_matr.size()) };
	vector<stv_t> state(num_V, stv_t::unvisited);
	vector<int> pred(num_V, -1);
	
	vector<vector<int>> predList(num_V, vector<int>());

	queue<int> q;

	vector<int> order;

	for (int i = 0; i < num_V; ++i) {
		if (state[i] == stv_t::unvisited) {
			BFS_Vist(i, state, pred, q, predList, order, def_no_edje);

		}
	}

	vector<vector<int>> result(2, vector<int>());
	result[0] = pred;
	result[1] = order;

	return result;
}

string graph::BFS_loop()
{
	int num_V{ static_cast<int>(adj_matr.size()) };
	vector<stv_t> state(num_V, stv_t::unvisited);
	vector<int> pred(num_V, -1);

	vector<vector<int>> predList(num_V, vector<int>());

	queue<int> q;
	string loop;
	for (int i = 0; i < num_V && loop == ""; ++i) {
		if (state[i] == stv_t::unvisited && loop == "") {
			loop = BFS_Vist_loop_out(i, state, pred, q, predList);

		}
	}

	return loop;
}

vector<string> graph::DFS_Top_sort()
{
	int num_V{ static_cast<int>(adj_matr.size()) };
	vector<stv_t> state(num_V, stv_t::unvisited);
	vector<int> pred(num_V, -1);
	vector<int> Time_in(num_V, -1);
	vector<int> Time_out(num_V, -1);
	vector<int> TopNum(num_V, -1);
	int CurTime{ 0 };
	int CurTopNum{ num_V-1 };

	for (int i = 0; i < num_V; ++i) {
		if (state[i] == stv_t::unvisited) {
			DFS_Top_sort_Visit(i, state, pred, Time_in, Time_out, TopNum, CurTime, CurTopNum);
		}
	}

	// Заполняем вывод топологической сортировки.
	vector<string> res;
	int ind{ 0 };
	while (ind < TopNum.size()) {
		int indTop{ 0 };

		while (indTop < TopNum.size() && TopNum[indTop] != ind) {
			indTop++;
		}

		assert(indTop != TopNum.size());

		res.push_back(this->names[indTop]);

		ind++;
	}

	/*for (auto i : TopNum)
		cout << i << " ";
	cout << endl;
	for (auto i : pred)
		cout << i << " ";
	cout << endl;

	for (auto i : this->names)
		cout << i << " ";
	cout << endl;*/

	return res;
}

void graph::Updare_C_P(priority_queue< pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>& pq, std::vector<bool>& inMST, std::vector<int>& C, std::vector<int>& R)
{

	while (!pq.empty())
	{
		int u = pq.top().second;
		pq.pop();

		if (inMST[u] == true) {
			continue;
		}

		inMST[u] = true;


		for (int i = 0; i < adj_matr[u].size(); ++i) {
			if (adj_matr[u][i] != -1) {
				int v = i;
				int weight = adj_matr[u][i];

				//printf("(u, v): (%d, %d), C[%d]=%d\n", u, v, v, C[v]);
				if (inMST[v] == false && C[v] > weight)
				{
					C[v] = weight;
					pq.push(make_pair(C[v], v));
					R[v] = u;
				}
			}
		}
	}

	/*for (auto i : R)
		cout << i << " ";
	cout << endl;*/
}

graph graph::PRIM()
{
	// Путь до вершины и название вершины
	priority_queue< pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

	int src = 0;
	int N = names.size();
	vector<int> C(N, INT_MAX);
	vector<int> R(N, -1);

	// Отслеживает, включена ли вершина в остовное дерево.
	vector<bool> inMST(N, false);

	pq.push(make_pair(0, src));
	C[src] = 0;

	Updare_C_P(pq, inMST, C, R);

	vector<vector<int>> new_adj_matr(N, vector<int>(N, -1));
	for (int i = 0; i < R.size(); ++i) {
		if (R[i] != -1) {
			new_adj_matr[R[i]][i] = adj_matr[R[i]][i];
			new_adj_matr[i][R[i]] = adj_matr[i][R[i]];
		}
	}

	graph gr(new_adj_matr, this->names);
	gr.set_type(graph::type_out::adj_matr);
	//cout << endl << gr;

	return gr;
}

string graph::task4()
{
	string result = "";
	graph gr_prim = this->PRIM();

	int sum{ gr_prim.get_total_weights(-1) };
	result += to_string(sum/2);

	result += "\n";
	vector<vector<int>> bfs_res = gr_prim.BFS(-1);
	
	vector<int> pred = bfs_res[0];
	vector<int> order = bfs_res[1];
	for (int i = 1; i < order.size(); ++i)
		result += to_string(order[i]) + " " + to_string(pred[order[i]]) + "\n";

	return result;
}

void graph::DFS_Top_sort_Visit(int v, vector<graph::status_vert>& status, vector<int>& pred, vector<int>& Time_in, vector<int>& Time_out, vector<int>& TopNum, int& CurTime, int& CurTopNum)
{
	status[v] = graph::status_vert::visited;
	CurTime++;
	Time_in[v] = CurTime;

	for (int u = 0; u < adj_matr[v].size(); u++)
	{
		if (adj_matr[v][u] != 0) {
			if (status[u] == stv_t::unvisited) {
				status[u] = stv_t::visited;
				pred[u] = v;
				DFS_Top_sort_Visit(u, status, pred, Time_in, Time_out, TopNum, CurTime, CurTopNum);
			}
		}
	}

	status[v] = stv_t::procceced;
	CurTime++;
	Time_out[v] = CurTime;
	TopNum[v] = CurTopNum;
	CurTopNum--;
}

ostream& operator<<(std::ostream& out, const graph& gr)
{
	//for (auto i : gr.names) {
	//	out << i << " ";
	//}

	//out << endl;

	if (gr.type == graph::type_out::adj_matr) {
		string s;
		for (int i = 0; i < gr.adj_matr.size(); ++i) {
			for (int j = 0; j < gr.adj_matr[0].size(); ++j) {
				int val{ gr.adj_matr[i][j] };
				s += to_string(val) + string(" ");
			}
			s.pop_back();
			s += "\n";
		}
		out << s;
	}
	else if (gr.type == graph::type_out::adj_list) {
		for (int i = 0; i < gr.adj_matr.size(); ++i) {
			
			out << gr.names[i] << ":";

			for (int j = 0; j < gr.adj_matr[i].size(); ++j) {
				if (i != j && gr.adj_matr[i][j] != 0) {
					out << " " << gr.names[j];
				}
			}
			out << endl;
		}
	} 
	else if (gr.type == graph::type_out::adj_list_points) {
		for (int i = 0; i < gr.adj_matr.size(); ++i) {

			out << Point(gr.names[i]) << ":";

			for (int j = 0; j < gr.adj_matr[i].size(); ++j) {
				if (i != j && gr.adj_matr[i][j] != 0) {
					out << " " << Point(gr.names[j]);
				}
			}
			out << endl;
		}
	}


	return out;
}
