#ifndef LEIC_TSP_REALGRAPH_H
#define LEIC_TSP_REALGRAPH_H

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <queue>
#include <limits>
#include <algorithm>
class RealVertex;
#include "realvertexedge.h"
#include "mpq.h"
#include "haversine.h"

using namespace std;

/**
 * @brief Represents a real shipping/delivery network
 */
class RealGraph {
public:
    RealGraph() {};

    /**
     * @brief Finds a vertex in the graph with the given ID
     * @details Complexity: O(|V|)
     * @param id The vertex's ID
     * @return The vertex with the specified ID; if it doesn't exist, it returns nullptr
     */
    RealVertex *findVertex(int id) const;

    /**
     * @brief Adds a vertex representing a specific place to the graph
     * @param id The ID of the place the vertex represents
     * @param lon The place's longitude
     * @param lat The place's latitude
     * @return True if the vertex was successfully added; if the vertex already exists, it returns false
     */
    bool addVertex(int id, double lon, double lat);

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
    unordered_map<int, RealVertex *> getVertexSet() const;

    /**
     * @brief Finds the Minimum Spanning Tree (MST) of a real graph
     * @details Complexity: O(E log V)
     * @param source The ID of the source vertex
     * @param tspCost The cost of going through the path
     * @param mst_graph The graph that represents the Minimum Spanning Tree (MST)
     * @return A vector containing the shortest path
     */
    vector<RealVertex*> prim(int source, double &tspCost, RealGraph &mst_graph);

    /**
     * @brief Visits all the vertices in the graph using a preorder traversal
     * @details Complexity: O(V+E)
     * @param v The current vertex
     * @param path The vector to store the shortest path
     * @param cost The cost of going through the path
     * @param prev_id The ID of the previous vertex
     */
    void preorderTraversal(RealVertex* v, vector<RealVertex*> &path, double &cost, int &prev_id);

    /**
     * @brief Calculates the cost of traveling between two vertices in the network
     * @param s The source vertex
     * @param t The destination vertex
     * @return The cost of traveling between the two vertices
     */
    double costCalculation(RealVertex* s, RealVertex* t);

private:
    /**
     * @brief An unordered map containing every pair of the graph's vertices and their respective IDs
     */
    unordered_map<int, RealVertex*> vertexSet;    // vertex set

    /**
     * @brief Removes a vertex from the graph
     * @param target The vertex we want to remove
     * @return True if the vertex was successfully removed; if the vertex does not exist, it returns false
     */
    bool removeVertex(int id);
};


#endif
