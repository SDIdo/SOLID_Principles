//
// Created by idox on 1/14/19.
//

#ifndef VER2_MATRIXTESTER_H
#define VER2_MATRIXTESTER_H
#include <iostream>
#include <vector>
#include <string>


class MatrixTester {
private:
    vector<vector<int>> goalIsDest = {{1, 0, 1},{0, 1, -1},{2, 1, 0}};
    Entry *start = new Entry(2,0);
    Entry *dest = new Entry(0,2);
    vector<vector<int>> createRandomMatrix(int, int);
    void printMatrix(vector<vector<int>> subject);
public:
    void runTest();
    void goalIsDestTest();
};


#endif //VER2_MATRIXTESTER_H
