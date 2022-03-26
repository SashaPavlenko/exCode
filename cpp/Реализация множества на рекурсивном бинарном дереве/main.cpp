#include <iostream>
#include "TreeRec.h"
#include "mSet.h"
#include <fstream>
#include <sstream>
#include <string>
#include "funcs.h"
using namespace std;

int main() {
	setlocale(LC_ALL, "rus");
	string filename1{ "test1.txt" };
	mSet<int> t1;
	readSet(filename1, t1);

	cout << "Первый набор: "<< t1;
	
	string filename2{ "test2.txt" };
	mSet<int> t2;
	readSet(filename2, t2);

	cout << "Второй набор: " << t2;

	cout << "Набор чисел первого файла равен набору чисел второго: " << ((t1 == t2) ? "ДА" : "НЕТ" ) << endl;

	cout << endl;
	mSet<double> t3;
	
	double a[] = { 1.53,-7.47,-3.67,-0.80,-6.40,-5.94,-6.69,3.78,-6.27,-6.24, -6.28, -0.75, -0.72, -0.73, -0.71 };
	int size = sizeof(a) / sizeof(double);
	for (int i = 0; i < size; ++i) {
		t3 += (a[i]);
	}

	cout << "Третий набор : " << t3;
	return 0;

}