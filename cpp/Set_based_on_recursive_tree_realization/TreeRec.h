#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

// Описание узла дерева:
//     data - значение в узле дерева;
//     lt - укзатель на левое поддерево;
//     rt - указатель на правое поддерево.

/*
В любой из реализаций (можно в обеих) добавьте в класс следующие методы:

* подсчёт количества узлов;
* подсчет количества листьев;
* вычисление глубины дерева;

Выполить перегрузку операции:

* присваивания;
* сравнение деревьев на равенство/неравенство

Реализовать методы построения двоичных деревьев:
* заполнением по ширине (для заданного количества узлов, значения узлов вводятся в потоке):

*/

template <typename T>
class TreeR {
private:
	//int data;
	struct TNode;
	typedef TNode* node_ptr;
	node_ptr root;

	struct TNode {
		T data;
		node_ptr lt, rt;
		TNode(T val, node_ptr l = nullptr, node_ptr r = nullptr) :
			data(val), lt(l), rt(r) {}
	};

	void delTree(node_ptr t) {
		if (t != nullptr) {
			delTree(t->lt);
			delTree(t->rt);
			delete t;
		}
		t = nullptr;
	};

	void swap(TreeR<T>& obj) {
		std::swap(this->root, obj.root);
		//std::swap(this->data, obj.data);
	};

	void add(node_ptr& t, T a) {
		if (t == nullptr) {
			t = new TNode(a);
		}
		else if (t->data > a) {
			this->add(t->lt, a);
		}
		else if (t->data < a) {
			this->add(t->rt, a);
		}
	};

	void printLKR(node_ptr t, std::ostream& os) const {
		if (t != nullptr) {
			printLKR(t->lt, os);
			os << t->data << " ";
			printLKR(t->rt, os);
		}
	};

	void copy(node_ptr t, node_ptr& newT) const {
		if (t != nullptr) {
			newT = new TNode(t->data);
			copy(t->lt, newT->lt);
			copy(t->rt, newT->rt);
		}
		else {
			newT = nullptr;
		}
	};

	int count_num_roots(const node_ptr t) {
		if (t == nullptr) {
			return 0;
		}
		else {
			//t->lt;
			return 1 + count_num_roots(t->lt) + count_num_roots(t->rt);
		}
	};

	int count_num_leaf(const node_ptr t) {
		if (t == nullptr) {
			return 0;
		}
		else if (t->lt == nullptr && t->rt == nullptr) {
			return 1;
		}
		else {
			return count_num_leaf(t->lt) + count_num_leaf(t->rt);
		}
	};

	int count_roots_deep(const node_ptr t) {
		if (t == nullptr) {
			return 0;
		}
		else {
			return 1 + std::max(count_roots_deep(t->lt), count_roots_deep(t->rt));
		}
	};

	void printTree(const node_ptr t, std::ostream& os, int skip = 0) const {
		if (t != nullptr) {
			printTree(t->rt, os, skip + 1);
			for (int i = 0; i < skip; ++i) {
				os << "      ";
			}
			os << t->data << "\n";
			printTree(t->lt, os, skip + 1);
		}
	};

	bool equal(const node_ptr t1, const node_ptr t2) const {
		if (t1 == nullptr && t2 == nullptr) {
			return true;
		}
		else if (t1 == nullptr || t2 == nullptr) {
			return false;
		}
		else {
			return t1->data == t2->data && equal(t1->lt, t2->lt) && equal(t1->rt, t2->rt);
		}
	};

	void add_width(node_ptr& t, T a) {
		if (t == nullptr) {
			t = new TNode(a);
		}
		else {
			if (count_roots_deep(t->lt) == count_roots_deep(t->rt)) {
				if (full_root(t->rt)) {
					add_width(t->lt, a);
				}
				else {
					add_width(t->rt, a);
				}
			}
			else {
				if (!full_root(t->lt)) {
					add_width(t->lt, a);
				}
				else {
					add_width(t->rt, a);
				}
			}
		}
	};

	bool full_root(node_ptr& t) {
		if (t == nullptr) {
			return true;
		}
		else {
			return (std::pow(2, count_roots_deep(t) - 1) == count_num_leaf(t));
		}
	};

	void create_balanced_tree(T n, node_ptr& t, std::stringstream& is) {
		node_ptr p;
		int d;
		T rData;
		if (n > 0) {
			is >> rData;
			t = new TNode(rData);
			d = n / 2;
			create_balanced_tree(d, t->lt, is);
			create_balanced_tree(n - 1 - d, t->rt, is);
		}
		else {
			t = nullptr;
		}
	};

	node_ptr& find(node_ptr t, T a) const {
		if (t == nullptr) {
			node_ptr tt = nullptr;
			return tt;
		}
		else if (a == t->data) {
			return t;
		}
		else if (a < t->data) {
			return this->find(t->lt, a);
		}
		else {
			return this->find(t->rt, a);
		}
	};

	void del_node(node_ptr& t, T a) {
		if (t != nullptr) {
			if (a == t->data) {
				deleteNode(t, a);
			}
			else if (a < t->data) {
				del_node(t->lt, a);
			}
			else {
				del_node(t->rt, a);
			}
		}
	};

	void deleteNode(node_ptr& t, T a) {
		node_ptr delNode;
		T repl;
		if ((t->lt == nullptr) && (t->rt == nullptr)) {// 1
			delete t;
			t = nullptr;
		}
		else if (t->lt == nullptr) {// 2
			delNode = t;
			t = t->rt;
			delete delNode;
		}
		else if (t->rt == nullptr) {// 3
			delNode = t;
			t = t->lt;
			delete delNode;
		}
		else if (t->lt != nullptr && t->rt != nullptr) {// 4
			delLeftLeaf(t->rt, repl);
			t->data = repl;
		}
	};

	void delLeftLeaf(node_ptr& t, T& repl) {
		if (!t->lt) // у самого левого нет левых потомков
		{
			repl = t->data;
			node_ptr delNode = t;
			t = t->rt;
			delete delNode;
		}
		else
			delLeftLeaf(t->lt, repl);
	};

	void get_all_elems(node_ptr& t, std::vector<T>& vec) {
		if (t != nullptr) {
			get_all_elems(t->lt, vec);
			vec.push_back(t->data);
			get_all_elems(t->rt, vec);
		}
	};

public:
	TreeR() : root{ nullptr } {};

	TreeR(const TreeR<T>& t)
	{
		this->copy(t.root, this->root);
	};
 
	~TreeR() {
		this->delTree(this->root);
	};
 

	// getters and setters
	T getData() const
	{
		return this->root->data;
	};

	// methods
	bool is_full_tree()
	{
		return this->full_root(this->root);
	};

	void addNode(T a)
	{
		this->add(this->root, a);
	};

	bool is_Empty() const
	{
		return this->root == nullptr;
	};

	int count_roots()
	{
		return count_num_roots(this->root);
	};

	int count_leaf()
	{
		return this->count_num_leaf(this->root);
	};

	int count_deep()
	{
		return count_roots_deep(this->root);
	};


	void fill_width(std::istream& is)
	{
		T rData;
		while (is.peek() != '\n') {
			is >> rData;
			this->add_width(this->root, rData);
		}

	};

	void create(std::istream& is = std::cin)
	{
		T rData;
		std::vector<T> v;

		while (is.peek() != '\n') {
			is >> rData;
			v.push_back(rData);
		}

		int n{ static_cast<int>(v.size()) };
		std::stringstream t;
		for (auto i : v) {
			t << i << " ";
		}

		this->~TreeR();
		create_balanced_tree(n, this->root, t);

	};

	bool find(T a) const
	{
		return this->find(this->root, a);
	};

	bool pop(T a)
	{
		bool flag{ this->find(a) };
		if (flag == true) {
			this->del_node(this->root, a);
		}

		return flag;
	};
	
	std::vector<T> get_vec()
	{
		std::vector<T> vec;
		get_all_elems(this->root, vec);

		return vec;
	};

	// operators
	//template <typename TT>
	friend std::ostream & operator<<(std::ostream & os, const TreeR<T>& t) {
		t.printTree(t.root, os, 0);
		return os;
	};

	TreeR& operator=(TreeR<T> t)
	{
		this->swap(t);
		return *this;
	}; 

	bool operator==(const TreeR<T>& t) const
	{
		return equal(this->root, t.root);
	};

};



