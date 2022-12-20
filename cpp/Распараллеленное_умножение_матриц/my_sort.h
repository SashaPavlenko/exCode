#include <iostream>
#include <cstdlib>
#include <omp.h>
#include <vector>
#include <ctime>
#include <string>

#pragma once

using namespace std;

typedef void(*sort_func) (vector<int>&, int);

int compare(const void* x1, const void* x2);

void buble_sort(vector<int>& a1, int size);

void paralled_buble_sort(vector<int>& a1, int size);

void merge_sort(vector<int>& a, int beg_for, int med_for, int end_for);

void paralleled_merge_sort(vector<int>& a, int size, int thr_n_mx, int thr_n_init);

void paralleled_selection_sort(vector<int>& a2, int size);

void selection_sort(vector<int>& a2, int size);

void changed_quik_sort(vector<int>& arr, int size);
