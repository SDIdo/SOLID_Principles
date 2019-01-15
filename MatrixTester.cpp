//
// Created by idox on 1/14/19.
//
#include "Searcher.h"
#include "MatrixGraph.h"
#include "AStar.h"
#include "BestFirstSearch.h"
#include "DFS.h"
#include "BFS.h"
#include "MatrixTester.h"
#define NUM_OF_MATRICES 20
#define NUM_OF_TESTS 10
#define MAX_COST 20
#define MAX_DIM 50
#define MIN_DIM 10
using namespace std;

void MatrixTester::runTest() {
    cout << "Welcome to the testing\n";
    int i, j;
    for (i = 0; i < NUM_OF_MATRICES; i++){
        cout << "$ Matrix and costs Creation $" << '\n';
        cout << "_____________________________" << '\n';
        //creating the random width and height of the matrix
        int width = MIN_DIM + (std::rand() % (MAX_DIM - MIN_DIM));
        int height = width;
        cout << height << " X " << width << '\n';
        vector<vector<int>> subjectMatrix = createRandomMatrix(width, height);
        printMatrix(subjectMatrix);
        cout << "______________________________ \n";
        cout << "@ enter and exit creation @" << '\n';
        for (j = 0; j < NUM_OF_TESTS; j++){
            int startX = (std::rand() % width);
            int startY = (std::rand() % height);
            cout << ">>Enter: " << "(" << startX << ", " << startY << ")" << '\n';
            Entry* start = new Entry(startX, startY);
            int endX = (std::rand() % width);
            int endY = (std::rand() % height);
            cout << ">>Exit: " << "(" << endX << ", " << endY << ")" << '\n';
            Entry* end = new Entry(endX, endY);
            MatrixGraph* checkMe = new MatrixGraph(width, height, start, end, subjectMatrix);
            //Here we start with the algorithms themselves
//            cout << "\n";
//            cout << "AStar\n";
//            AStar<Entry> astar;
//            cout << "Shortest Path is: " << astar.search(checkMe) << '\n';
//            cout << "Number of moves: " << astar.getNumberOfNodesEvaluated() << '\n';
            cout << "\n";
            cout << "Best First Search\n";
            BestFirstSearch<Entry> bestFirstSearch;
            cout << "Shortest Path is: " << bestFirstSearch.search(checkMe) << '\n';
            cout << "Number of moves: " << bestFirstSearch.getNumberOfNodesEvaluated() << '\n';
            cout << "\n";
//            cout << "\n";
//            cout << "DFS\n";
//            DFS<Entry> dfs;
//            cout << "Shortest Path is: " << dfs.search(checkMe) << '\n';
//            cout << "Number of moves: " << dfs.getNumberOfNodesEvaluated() << '\n';
//            cout << "\n";
//            cout << "\n";
//            cout << "BFS\n";
//            BFS<Entry> bfs;
//            cout << "Shortest Path is: " << bfs.search(checkMe) << '\n';
//            cout << "Number of moves: " << bfs.getNumberOfNodesEvaluated() << '\n';
//            cout << "\n";


            cout << "**Done a round with all the algorithms**\n";
            cout << "\n";
        }
    }
}

void MatrixTester::goalIsDestTest(){
    MatrixGraph* goalDestMat = new MatrixGraph(3, 3, start, dest, this->goalIsDest);
    cout << "Best First :: Search goalIsDestTest\n";
    BestFirstSearch<Entry> bestFirstSearch;
    cout << "Shortest Path is: " << bestFirstSearch.search(goalDestMat) << '\n';
    cout << "Number of moves: " << bestFirstSearch.getNumberOfNodesEvaluated() << '\n';
    cout << "\n";
}

vector<vector<int>> MatrixTester::createRandomMatrix(int width, int height) {
    double randomCost;
    vector<int> row;
    vector<vector<int>> matrix;
    //creating the random costs of the matrix
    for (int j = height; j >0; j--){
        for (int i = width; i > 0; i--){
            randomCost = 1 + (std::rand() % MAX_COST);
            if ((std::rand()%10) == 4){
                randomCost = -1;
            }
            row.push_back(randomCost);
        }
        matrix.push_back(row);
        row.clear();
    }
    return matrix;
}

void MatrixTester::printMatrix(vector<vector<int>> subject) {
    for (int i = 0; i < subject.size(); i++) {
        for (int j = 0; j < subject[i].size(); j++) {
            cout << subject[i][j] << " ";
        }
        cout << "\n";
    }
}