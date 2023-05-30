#ifndef LEIC_TSP_MANAGER_H
#define LEIC_TSP_MANAGER_H
#include <bits/stdc++.h>
#include "graph.h"
#include "realgraph.h"

using namespace std;

/**
 * @brief Represents the interface between the menu and the graph
 */
class Manager {
public:
    Manager();

    ~Manager();

    /**
     * @brief Builds a graph containing the railway's train stations
     * @param filename The name of the file containing the train stations' data
     */
    void buildGraph(const string &filename);

    /**
     * @brief Tests if the graph was successfully created (not meant for the end user)
     */
    void testing();

private:
    /**
     * @brief The network's graph
     */
    Graph *network;

    RealGraph *real_network;
};

#endif //LEIC_TSP_MANAGER_H
