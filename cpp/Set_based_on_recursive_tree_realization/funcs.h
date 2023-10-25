#pragma once
#include "mSet.h"
#include <string>

template <typename T>
void readSet(std::string s, mSet<T>& t) {
	std::string filename{ "test1.txt" };
	std::ifstream i1(filename);

	i1 >> t;
};