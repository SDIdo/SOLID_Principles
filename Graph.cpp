//
// Created by roy on 1/9/19.
//

#include "Graph.h"

using namespace std;

// Graph class represents a directed graph
// using adjacency list representation
Graph::Graph(int V)     //set number of vertexes for the graph
{
    this->V = V;        //get the number from input
    adj = new list<int>[V]; //set adj list according to the input a graph
    totalCost = DBL_MAX; // the current min cost (max).
}

//setter of vertex cost
void Graph::setVertexCost(int u, double cost) {
    costTable[u] = cost;
}

//getter of vertex cost
double Graph::getVertexCost(int u) {
    return costTable[u];
}

void Graph::addEdge(int v, int w) //Now we have departed vertexes so connecting them here.
{
    adj[v].push_back(w); // Add w to v’s list.
}

/**
 * A recursive function to print all paths from 'u' to 'd'.
 * visited[] keeps track of vertices in current path.
 * path[] stores actual vertices and path_index is current
 * index in path[]
 * @param u
 * @param d
 * @param visited
 * @param path
 * @param path_index
 */
void Graph::printAllPathsUtil(int u, int d, bool visited[], int path[], int &path_index) {
    // Mark the current node and store it in path[]
    visited[u] = true;
    path[path_index] = u;
    path_index++;

    // If current vertex is same as destination, then print
    // current path[]
    if (u == d) //backward taking all the path
    {
        double sum = 0;
        for (int i = 0; i < path_index; i++) {
            cout << path[i] << " ";
            sum += this->getVertexCost(path[i]);
        }
        if (sum < totalCost) {
            totalCost = sum;
            this->shortestPath.clear();

            for (int i = 0; i < path_index; i++) {
                shortestPath.push_back(path[i]);
            }

        }
        cout << "Current minimum sum is " << totalCost << endl;

    }
        // If current vertex is not destination
    else {
        // Recur for all the vertices adjacent to current vertex
        list<int>::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
            if (!visited[*i])
                printAllPathsUtil(*i, d, visited, path, path_index);
    }
    // Remove current vertex from path[] and mark it as unvisited
    path_index--;
    visited[u] = false;
}

/** Prints all paths from 's' to 'd'
 * @param s
 * @param d
 * @return
 */
vector<int> Graph::printAllPaths(int s, int d) {
    // Mark all the vertices as not visited
    bool *visited = new bool[V];

    // Create an array to store paths
    int *path = new int[V];
    int path_index = 0; // Initialize path[] as empty

    // Initialize all vertices as not visited
    for (int i = 0; i < V; i++) {
        visited[i] = false;
    }
    // Call the recursive helper function to print all paths
    printAllPathsUtil(s, d, visited, path, path_index);
//
    return this->shortestPath;
}




//void Graph::DFSUtil(int v, bool visited[])  //The actual parsing (now we know.. shouldn't be here!)
//{
//    // Mark the current node as visited and
//    // print it
//    visited[v] = true; //immediately upon reaching should be considered visited.
//    cout << v << " ";   //immediately print it (or in our save it to a list of rout)
//
//    // Recur for all the vertices adjacent
//    // to this vertex
//    list<int>::iterator i;  //going through all the neighbors of a certain unvisited node
//    for (i = adj[v].begin(); i != adj[v].end(); ++i)
//        if (!visited[*i])
//            DFSUtil(*i, visited);
//}

//// DFS traversal of the vertices reachable from v.
//// It uses recursive DFSUtil()
//void Graph::DFS(int v) {
//    // Mark all the vertices as not visited
//    bool *visited = new bool[V];
//    for (int i = 0; i < V; i++)
//        visited[i] = false;
//
//    // Call the recursive helper function
//    // to print DFS traversal
//    DFSUtil(v, visited); //visited is a list of info about which visited and which not
//}