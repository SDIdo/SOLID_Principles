//
// Created by roy on 1/9/19.
//

#ifndef PROJECTPART2_GRAPH_H
#define PROJECTPART2_GRAPH_H


#include<iostream>
#include<list>
#include <map>
#include <float.h>
#include <vector>

using namespace std;
class Graph {
    int V;    // No. of vertices

    double totalCost; //global counter of shortest path cost

    vector<int> shortestPath; //global array for shortest path

    // Pointer to an array containing
    // adjacency lists
    list<int> *adj;

    //Vertex prices
    map<int, double> costTable;

    // A recursive function used by DFS
    void DFSUtil(int v, bool visited[]);

    // A recursive function used by printAllPaths()
    void printAllPathsUtil(int u, int d, bool visited[], int path[], int &path_index);
public:
    Graph(int V);   // Constructor

    // function to add an edge to graph
    void addEdge(int v, int w);

    //Add cost of standing on for a certain vertex.
    void setVertexCost(int u, double cost);


    //Add cost of standing on for a certain vertex.
    double getVertexCost(int u);

    // DFS traversal of the vertices
    // reachable from v
    void DFS(int v);

    vector<int> printAllPaths(int s, int d);


};


#endif //PROJECTPART2_GRAPH_H
