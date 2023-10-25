#include <iostream>
#include <vector>
#include "graph.h"
#include <fstream>
#include <string>
#include <exception>

class ErrorArguments : exception {
	virtual const char* what() const throw() {
		return "ErrorArguments";
	}
};

using namespace std;

int main(int argc, char* argv[]) {
	setlocale(0, "RUS");


	if (argc == 3) {
		string filename(argv[1]);
		graph gr(filename, graph::type_in::floors);

		ofstream file(argv[2]);
		file << gr.task4();

		file.close();
	}
	else {
		cout << argc;
		throw ErrorArguments();
	}


	/*string filename("Input2.txt");
	graph gr(filename, graph::type_in::floors);
	
	cout << gr.task4();*/

	return 0;
}