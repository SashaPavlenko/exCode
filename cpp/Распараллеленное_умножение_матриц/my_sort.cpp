//#include <iostream>
//#include <cstdlib>
//#include <omp.h>
//#include <vector>
//#include <ctime>
//#include <string>
//#include "funcs.h"
//#include "my_sort.h"
//
//using namespace std;
//
//int compare(const void* x1, const void* x2)
//{
//	return (*(int*)x1 - *(int*)x2);
//}
//
//void buble_sort(vector<int>& a1, int size) {
//	bool flag = true;
//	for (int i = 0; i < size - 1 && flag; ++i) {
//		flag = false;
//		for (int k = 0; k < size - 1; ++k) {
//			if (a1[k] > a1[k + 1]) {
//				flag = true;
//				swap(a1[k], a1[k + 1]);
//			}
//		}
//	}
//}
//
//void paralled_buble_sort(vector<int>& a1, int size) {
//	bool flag = true;
//
//	int i, k, n, beg_for, end_for, thr_n_mx{ 4 };
//
//	omp_set_dynamic(1);
//	omp_set_num_threads(thr_n_mx);
//#pragma omp parallel shared(a1, size, flag, thr_n_mx) private(i, n, k, beg_for, end_for)
//	{
//
//		n = omp_get_thread_num();
//
//		int plus = size % thr_n_mx != 0 ? (thr_n_mx - size % thr_n_mx) : 0;
//		int full_size = size + plus;
//
//		if (n == omp_get_max_threads() - 1 && size % 4 != 0) {
//			beg_for = full_size / thr_n_mx * (n);
//			end_for = size - 1;
//		}
//		else {
//			beg_for = full_size / thr_n_mx * n;
//			end_for = full_size / thr_n_mx * (n + 1) - 1;
//		}
//
//		for (i = beg_for; i < end_for; ++i) {
//			flag = false;
//
//			for (k = beg_for; k < end_for; ++k) {
//				if (a1[k] > a1[k + 1]) {
//					flag = true;
//					swap(a1[k], a1[k + 1]);
//				}
//			}
//
//			if (!flag) {
//				break;
//			}
//		}
//	}
//
//	int thr_n_init{ thr_n_mx };
//
//	while (thr_n_mx / 2 != 0) {
//		//cout << vec_to_string(a1);
//		thr_n_mx /= 2;
//		paralleled_merge_sort(a1, size, thr_n_mx, thr_n_init);
//	}
//
//	thr_n_mx = 4;
//	omp_set_num_threads(thr_n_mx);
//}
//
//void paralleled_merge_sort(vector<int>& a, int size, int thr_n_mx, int thr_n_init) {
//	int i, n, k, beg_for, end_for;
//
//	int plus = size % (thr_n_mx * 2) != 0 ? (thr_n_init - size % thr_n_init) : 0;
//	int full_size = size + plus;
//
//	if (thr_n_mx > 1) {
//		omp_set_num_threads(thr_n_mx);
//
//#pragma omp parallel shared(a, size, thr_n_mx, full_size) private(i, n, k, beg_for, end_for)
//		{
//			//printf("Hello");
//			n = omp_get_thread_num();
//
//			if (n == omp_get_max_threads() - 1 && size % 4 != 0) {
//				beg_for = full_size / thr_n_mx * (n);
//				end_for = size;
//			}
//			else {
//				beg_for = full_size / thr_n_mx * n;
//				end_for = full_size / thr_n_mx * (n + 1);
//			}
//			// Начало второго подмассива
//			int med_for{ beg_for + full_size / thr_n_mx / 2 };
//
//			merge_sort(a, beg_for, med_for, end_for);
//		}
//	}
//	else if (thr_n_mx == 1){
//		int med_for{ full_size / 2 };
//		merge_sort(a, 0, med_for, a.size());
//	}
//
//	thr_n_mx *= 2;
//
//	omp_set_num_threads(thr_n_mx);
//
//}
//
//void merge_sort(vector<int>& a, int beg_for, int med_for, int end_for) {
//	// Собирает массив а относительно подмассива с индексами [beg_for; med_for-1] и подмассива [med_for; end_for],
//
//	int index_first{ beg_for }, index_second{ med_for };
//	vector<int> sub_vect;
//
//	while (index_first < med_for || index_second < end_for) {
//		// В обоих массивах остались элементы.
//		if (index_first < med_for && index_second < end_for) {
//			if (a[index_first] < a[index_second])
//				sub_vect.push_back(a[index_first++]);
//			else
//				sub_vect.push_back(a[index_second++]);
//		}
//		// Второй массив закончился, остался первый.
//		else if (index_first < med_for) {
//			while (index_first < med_for) sub_vect.push_back(a[index_first++]);
//		}
//		// Первый массив закончился, остался второй.
//		else if (index_second < end_for) {
//			while (index_second < end_for) sub_vect.push_back(a[index_second++]);
//
//		}
//	}
//
//	for (int i = beg_for; i < end_for; i++) {
//		a[i] = sub_vect.at(i - beg_for);
//	}
//}
//
//void paralleled_selection_sort(vector<int>& a2, int size)
//{
//	bool flag = true;
//
//	int i, k, n, beg_for, end_for, thr_n_mx{ 4 };
//
//	omp_set_dynamic(1);
//	omp_set_num_threads(thr_n_mx);
//#pragma omp parallel shared(a2, size, flag, thr_n_mx) private(i, n, k, beg_for, end_for)
//	{
//
//		n = omp_get_thread_num();
//
//		int plus = size % thr_n_mx != 0 ? (thr_n_mx - size % thr_n_mx) : 0;
//		int full_size = size + plus;
//
//		if (n == omp_get_max_threads() - 1 && size % 4 != 0) {
//			beg_for = full_size / thr_n_mx * (n);
//			end_for = size - 1;
//		}
//		else {
//			beg_for = full_size / thr_n_mx * n;
//			end_for = full_size / thr_n_mx * (n + 1) - 1;
//		}
//
//		for (int i = beg_for; i < end_for+1; ++i) {
//			int mmin{ a2[i] }, min_index{ i };
//			for (int k = i; k < end_for+1; k++)
//			{
//				if (a2[k] < mmin) {
//					mmin = a2[k];
//					min_index = k;
//				}
//			}
//			swap(a2[i], a2[min_index]);
//
//		}
//	}
//
//	int thr_n_init{ thr_n_mx };
//
//	while (thr_n_mx / 2 != 0) {
//		//cout << vec_to_string(a1);
//		thr_n_mx /= 2;
//		paralleled_merge_sort(a2, size, thr_n_mx, thr_n_init);
//	}
//
//	thr_n_mx = 4;
//	omp_set_num_threads(thr_n_mx);
//}
//
//void selection_sort(vector<int>& a2, int size) {
//	for (int i = 0; i < size; ++i) {
//		int mmin{ a2[i] }, min_index{ i };
//		for (int k = i; k < size; k++)
//		{
//			if (a2[k] < mmin) {
//				mmin = a2[k];
//				min_index = k;
//			}
//		}
//		swap(a2[i], a2[min_index]);
//
//	}
//}
//
//void changed_quik_sort(vector<int>& arr, int size) {
//	qsort(arr.begin()._Ptr, size, sizeof(int), compare);
//}
