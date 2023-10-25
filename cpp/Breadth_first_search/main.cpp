#include <queue>
#include <iostream>
#include <string>
#include "bread_first_search/my_graph.h"
#include "bread_first_search/MyFileExceptions.h"

const int PEAKS = 5;

int main() {
    /*std::queue<int> peakQueue;
    int was[PEAKS] = {0};
    int matr[PEAKS][PEAKS] = {
        {1, 0, 1, 1, 1},
        {0, 1, 0, 1, 0},
        {1, 0, 1, 0, 1},
        {1, 1, 0, 1, 0},
        {1, 0, 1, 0, 1}
    };

    peakQueue.push(0);
    was[0] = 1;

    while(!peakQueue.empty()) {
        int peak = peakQueue.front();
        peakQueue.pop();
        for (int i = 0; i < PEAKS; i++) {
            if (i != peak && matr[peak][i] == 1 && was[i] != 1) {
                peakQueue.push(i);
                was[i] = 1;
                std::cout << i << std::endl;
            }
        }

    }*/

    try
    {
        std::string str{ "bread_first_search/test_matrix.txt" };
        my_graph t(str);
    }
    catch (MyFileExceprion& exception) {
        cerr << "Exception: " << exception.what() << endl;
    }
    catch (const std::exception& exception) {

        std::cerr << "Standard exception: " << exception.what() << endl;
    }

}