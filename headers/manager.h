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
     * @brief Builds a graph containing the shipping/delivery network's places and its connections
     * @param filename The name of the file containing the places' data
     */
    void buildGraph(const string &filename);

    /**
     * @brief Builds a graph containing the real shipping/delivery network's places
     * @param filename The name of the file containing the real places' data
     */
    void buildRealGraph(const string &filename);

    /**
     * @brief Adds the real shipping/delivery network's connections to the graph
     * @param filename The name of the file containing the real connections' data
     */
    void buildRealNetwork(const string &filename);

    /**
     * @brief Tests if the graph was successfully created (not meant for the end user)
     */
    void testing();

    /**
     * @brief Calculates the shortest path starting at one point and ending in another while going through every node of the graph using a brute force approach
     * @param min_path The vector to store the shortest path
     * @return The cost of going through the shortest path between the two points
     */
    double backtrack(vector<int> &min_path);

    /**
     * @brief Calculates the shortest path starting at one point and ending in another while going through every node of the graph using a triangular approximation heuristic
     * @param cost The cost of going through the shortest path between the two points
     * @return A vector containing the shortest path
     */
    vector<Vertex*> triangularApproximation(double &cost);


    /**
     * @brief Calculates the shortest path starting at one point and ending in another, in a real graph, while going through every node of the graph using a triangular approximation heuristic
     * @param cost The cost of going through the shortest path between the two points
     * @return A vector containing the shortest path
     */
    vector<RealVertex*> realTriangularApprox(double &cost);

    double myHeuristic(vector<int> &min_path);
    // int numTest();


private:
    /**
     * @brief The network's graph
     */
    Graph *network;


    /**
     * @brief The real network's graph
     */
    RealGraph real_network;

};

#endif //LEIC_TSP_MANAGER_H
