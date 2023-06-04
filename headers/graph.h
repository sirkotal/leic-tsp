#ifndef LEIC_TSP_GRAPH_H
#define LEIC_TSP_GRAPH_H

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <queue>
#include <limits>
#include <algorithm>
class Vertex;
#include "vertexedge.h"
#include "mpq.h"

using namespace std;

/**
 * @brief Represents a shipping/delivery network
 */
class Graph {
public:
    Graph() {};

    /**
     * @brief Finds a vertex in the graph with the given ID
     * @details Complexity: O(|V|)
     * @param id The vertex's ID
     * @return The vertex with the specified ID; if it doesn't exist, it returns nullptr
     */
    Vertex *findVertex(int id) const;

    /**
     * @brief Adds a vertex representing a specific place to the graph
     * @param id The ID of the place the vertex represents
     * @return True if the vertex was successfully added; if the vertex already exists, it returns false
     */
    bool addVertex(int id);

    /**
     * @brief Adds an edge between two vertices of a graph
     * @param source The ID of the source vertex
     * @param dest The ID of the destination vertex
     * @param w The capacity of the edge
     * @return True if the edge was successfully added; if the source or destination vertex does not exist, it returns false
     */
    bool addEdge(int source, int dest, double w);

    /**
     * @brief Adds two edges: one from a source to a destination vertex and another one in the opposite direction
     * @param source The ID of the source vertex
     * @param dest The ID of the destination vertex
     * @param w The capacity of the edge
     * @return True if the edges were successfully added; if the source or destination vertex does not exist, it returns false
     */
    bool addBidirectionalEdge(int source, int dest, double w);

    /**
     * @brief Gets the graph's number of vertices
     * @return The number of vertices in the graph
     */
    int getNumVertex() const;

    /**
     * @brief Gets the graph's number of edges
     * @return The number of edges in the graph
     */
    int getNumEdges() const;

    /**
     * @brief Gets the graph's vertices
     * @return An unordered map with every pair of the graph's vertices and their respective IDs
     */
    unordered_map<int, Vertex*> getVertexSet() const;

    /**
     * @brief Calculates the shortest path starting at one point and ending in another while going through every node of the graph
     * @details Complexity: O(V!)
     * @param current The current node
     * @param start The starting node
     * @param counter Counts the visited nodes
     * @param distance Distance between the nodes
     * @param min_distance Current minimum distance between the nodes
     * @param min_path The minimum path
     * @param pathTSP The current path
     * @return The minimum distance between the two nodes
     */
    double bruteforceBacktrack(Vertex* current, Vertex* start, int counter, double distance, double min_distance, vector<int> &min_path, vector<int> &pathTSP);

    /**
     * @brief Finds the Minimum Spanning Tree (MST) of a graph
     * @details Complexity: O(E log V)
     * @param source The ID of the source vertex
     * @param tspCost The cost of going through the path
     * @param mst_graph The graph that represents the Minimum Spanning Tree (MST)
     * @return A vector containing the shortest path
     */
    vector<Vertex*> prim(int source, double &tspCost, Graph &mst_graph);

    /**
     * @brief Visits all the vertices in the graph using a preorder traversal
     * @details Complexity: O(V+E)
     * @param v The current vertex
     * @param path The vector to store the shortest path
     * @param cost The cost of going through the path
     * @param prev_id The ID of the previous vertex
     */
    void preorderTraversal(Vertex* v, vector<Vertex*> &path, double &cost, int &prev_id);

    /**
     * @brief Calculates the cost of traveling between two vertices in the network
     * @param s The source vertex
     * @param t The destination vertex
     * @return The cost of traveling between the two vertices
     */
    double costCalculation(Vertex* s, Vertex* t);
private:
    /**
     * @brief An unordered map containing every pair of the graph's vertices and their respective IDs
     */
    unordered_map<int, Vertex*> vertexSet;    // vertex set

    /**
     * @brief Removes a vertex from the graph
     * @param target The vertex we want to remove
     * @return True if the vertex was successfully removed; if the vertex does not exist, it returns false
     */
    bool removeVertex(int id);
};

#endif //LEIC_TSP_GRAPH_H
