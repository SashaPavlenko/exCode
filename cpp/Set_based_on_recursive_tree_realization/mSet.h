#pragma once
#include "TreeRec.h"
#include <iostream>

class Error : public std::exception { //можно сделать реализацию или наследовать от exception
private:
	std::string m_error;
public:
	Error(std::string text = "Undefined error") : m_error{ text } {};
	const char* what() const noexcept { return m_error.c_str(); }
};

template <typename T>
class set_iter;

template <typename T>
class mSet
{
private:
	TreeR<T> t;
	int length;

	void swap(mSet<T> s)
	{
		std::swap(this->length, s.length);
		std::swap(this->t, s.t);
	};
public:
	mSet()
	{
		this->t = TreeR<T>();
		this->length = 0;
	};

	mSet(T a[], int size)
	{
		TreeR<T> tr;

		for (int i = 0; i < size; ++i) {
			tr.addNode(a[i]);
		}
		length = tr.count_roots();
		this->t = tr;
	};


	mSet(T a)
	{
		TreeR<T> tr;

		tr.addNode(a);
		length = tr.count_roots();
		this->t = tr;
	};

	mSet(const mSet<T>& s)
	{
		this->t = s.t;
		this->length = s.length;
	};

	~mSet() {};

	set_iter<T> begin() const {
		return set_iter<T>(this, this->t);
	};

	set_iter<T> end() const
	{
		return set_iter<T>(this, TreeR<T>());
	};

	mSet<T>& operator= (const mSet<T>& s) {
		mSet<T> s_copy = s;
		this->swap(s);

		return *this;
	};

	bool is_there(T a) const
	{
		return this->t.find(a);
	};

	int capacity()
	{
		return this->length;
	};

	bool operator==(const mSet<T>& s)
	{
		bool flag{ this->length == s.length };
		for (auto i = this->begin(); i != this->end() && flag; ++i) {
			flag = s.is_there(*i);
		}

		return flag;
	};

	bool pop(T a)
	{
		bool flag = this->is_there(a);
		if (flag) {
			this->t.pop(a);
			length--;
		}

		return flag;
	};

	const mSet<T> operator+(const mSet<T>& s)
	{
		mSet set_copy = *this;

		for (auto i : s) {
			if (!this->is_there(i)) {
				set_copy.t.addNode(i);
				set_copy.length++;
			}
		}

		return set_copy;
	};

	const mSet<T> operator*(const mSet<T>& s)
	{
		mSet set_copy;

		for (auto i : s) {
			if (this->is_there(i)) {
				set_copy.t.addNode(i);
				set_copy.length++;
			}
		}

		return set_copy;
	};

	mSet<T>& operator+=(const mSet<T>& s)
	{
		mSet set_copy = *this;

		for (auto i : s) {
			if (!this->is_there(i)) {
				set_copy.t.addNode(i);
				set_copy.length++;
			}
		}

		*this = set_copy;
		return *this;
	};

	mSet<T>& operator+=(T s)
	{
		this->t.addNode(s);
		this->length++;
		return *this;
	};

	mSet<T>& operator-=(const mSet<T>& s)
	{
		mSet set_copy = *this;

		for (auto i : s) {
			if (set_copy.is_there(i)) {
				set_copy.pop(i);
			}
		}

		*this = set_copy;
		return *this;
	};


	//template <typename TT>
	friend std::ostream& operator << (std::ostream& out, const mSet<T>& y)
	{
		for (auto i : y) {
			std::cout << i << " ";
		}
		std::cout << std::endl;

		return out;
	};

	//template <typename TT>
	friend std::istream& operator>> (std::istream& in, mSet<T>& y)
	{
		T rData;
		while (!in.eof()) {
			in >> rData;
			y += rData;
		}

		return in;
	};
};

template <typename T>
class set_iter {
public:
	class Error {
	public:
		void what() {
			std::cout << "Iterator error" << std::endl;
		}
	};
private:
	const mSet<T>* collection;
	std::vector<T> root;
	int ind;
public:
	set_iter(const mSet<T>* s, TreeR<T> r) : collection{ s } {
		root = r.get_vec();
		if (root.size() > 0) {
			ind = 0;
		}
		else {
			ind = -1;
		}
	};

	T& operator*() {
		if (ind != -1 && ind != root.size()) {
			return root[ind];
		}
		else {
			throw Error();
		}
	}

	set_iter<T> operator++() {
		if (ind != -1 && ind != root.size()) {
			ind++;
			return *this;
		}
		else {
			throw Error();
		}
	}

	bool operator == (const set_iter<T>& ri) const {
		return ((collection == ri.collection) && ((ind == ri.ind) || \
			(ind == -1 && ri.ind == ri.root.size()) || (ind == this->root.size() && ri.ind == -1)));
	}
	bool operator != (const set_iter<T>& ri) const {
		return !(*this == ri);
	}

};
