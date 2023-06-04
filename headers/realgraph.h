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
 * @brief Represents the railway network
 */
class RealGraph {
public:
    RealGraph() {};

    /**
     * @brief Finds a vertex in the graph with the given id
     * @details Complexity: O(|V|)
     * @param id The vertex's id
     * @return The vertex with the specified id; if it doesn't exist, it returns nullptr
     */
    RealVertex *findVertex(int id) const;

    /**
     * @brief Adds a vertex representing a specific train station to the graph
     * @param station The train station the vertex represents
     * @return True if the vertex was successfully added; if the vertex already exists, it returns false
     */
    bool addVertex(int id, double lon, double lat);

    /**
     * @brief Adds an edge between to vertexes of a graph
     * @param source The id of the source vertex
     * @param dest The id of the destination vertex
     * @param w The capacity of the edge
     * @param serv The service provided in the edge
     * @return True if the edge was successfully added; if the source or destination vertex does not exist, it returns false
     */
    bool addEdge(int source, int dest, double w);

    /**
     * @brief Adds two edges: one from a source to a destination vertex and another one in the opposite direction
     * @param source The id of the source vertex
     * @param dest The id of the destination vertex
     * @param w The capacity of the edge
     * @param serv The service provided in the edge
     * @return True if the edges were successfully added; if the source or destination vertex does not exist, it returns false
     */
    bool addBidirectionalEdge(int source, int dest, double w);

    /**
     * @brief Gets the graph's number of vertexes
     * @return The number of vertexes in the graph
     */
    int getNumVertex() const;

    /**
     * @brief Gets the graph's number of edges
     * @return The number of edges in the graph
     */
    int getNumEdges() const;

    /**
     * @brief Gets the graph's vertexes
     * @return A vector with all of the graph's vertexes
     */
    unordered_map<int, RealVertex *> getVertexSet() const;

    vector<RealVertex*> prim(int source, double &tspCost, RealGraph &mst_graph);

    void preorderTraversal(RealVertex* v, vector<RealVertex*> &path, double &cost, int &prev_id);

    double costCalculation(RealVertex* s, RealVertex* t);

private:
    /**
     * @brief A vector containing all of the graph's vertexes
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
