//
// Created by idox on 1/4/19.
//

#include <vector>
#include "DFS.h"

std::string DFS::search(Graph &graph, int source, int dest) {
    cout << "Scatishly calling DFS of graph itself\n";
    vector<int>sol = graph.printAllPaths(source, dest);
    for (std::vector<int>::iterator it = sol.begin() ; it != sol.end(); ++it)
        std::cout << ' ' << *it;


    return "Done";
}
int DFS::getNumberOfNodesEvaluated() {
    return 0;
}
