#ifndef LEIC_TSP_VERTEXEDGE_H
#define LEIC_TSP_VERTEXEDGE_H

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

class Edge;

/************************* Vertex  **************************/

/**
 * @brief Represents a station in the railway network
 */
class Vertex {
public:
    Vertex(int id);

    /**
     * @brief Gets the vertex's adjacency list
     * @return A vector with all of the vertex's outgoing edges
     */
    std::vector<Edge *> getAdj() const;

    /**
     * @brief Gets the train station associated to the vertex
     * @return The vertex's station
     */
    int getID() const;

    /**
     * @brief Checks if the vertex has been visited
     * @return True if the vertex has been visited; if it hasn't, it returns false
     */
    bool isVisited() const;

    /**
     * @brief Checks if the vertex is being processed
     * @return True if the vertex is being processed; if it isn't, it returns false
     */
    bool isProcessing() const;

    /**
     * @brief Gets the vertex's indegree
     * @return The indegree of the vertex
     */
    unsigned int getIndegree() const;

    /**
     * @brief Gets the path that travels to the vertex
     * @return The edge that travels to the vertex
     */
    Edge *getPath() const;

    /**
     * @brief Gets all of the vertex's incoming edges
     * @return A vector with all of the vertex's incoming edges
     */
    std::vector<Edge *> getIncoming() const;

    /**
     * @brief Gets the vertex's distance (cost) to a source vertex
     * @return The vertex's distance to the source
     */
    int getDistance() const;

    /**
     * @brief Sets the vertex to either visited or unvisited
     * @param visited True if setting the vertex to visited; otherwise, it is false
     */
    void setVisited(bool visited);

    /**
     * @brief Sets the vertex to either being processed or not
     * @param processing True if setting the vertex to being processed; otherwise, it is false
     */
    void setProcesssing(bool processing);

    /**
     * @brief Sets the vertex's indegree
     * @param indegree The vertex's new indegree
     */
    void setIndegree(unsigned int indegree);

    /**
     * @brief Sets the path to the vertex
     * @param path The edge that leads to the vertex
     */
    void setPath(Edge *path);

    /**
     * @brief Sets the vertex's distance (cost) to a source vertex
     * @param num The vertex's distance to the source
     */
    void setDistance(int num);

    /**
     * @brief Adds an edge that originates from the vertex
     * @param dest The destination vertex
     * @param w The edge's capacity/weight
     * @param service The edge's type of service
     * @return The new edge that has been added
     */
    Edge* addEdge(Vertex *dest, double w);

    /**
     * @brief Removes an edge that originates from the vertex
     * @param destID The destination vertex's station name
     * @return True if the edge was successfully removed; if it doesn't exist, it returns false
     */
    bool removeEdge(int destID);

    /**
     * @brief Gets the previous vertex
     * @return The previous vertex
     */
    Vertex* getSRC();

    /**
     * @brief Sets the previous vertex
     * @param v The previous vertex
     */
    void setSRC(Vertex *v);

    bool operator<(Vertex & v2) const;

private:
    /**
     * @brief The vertex's station
     */
    int id;

    std::string label = "";

    /**
     * @brief The vertex's adjacency list (outgoing edges)
     */
    std::vector<Edge *> adj;  // outgoing edges

    /**
     * @brief The vertex has been visited
     */
    bool visited = false; // used by DFS, BFS, Prim ...

    /**
     * @brief The vertex is being processed
     */
    bool processing = false; // used by isDAG (in addition to the visited attribute)

    /**
     * @brief The vertex's indegree
     */
    unsigned int indegree; // used by topsort

    /**
     * @brief The edge that travels to this vertex
     */
    Edge *path = nullptr;

    /**
     * @brief The vertex's incoming edges
     */
    std::vector<Edge *> incoming; // incoming edges

    /**
     * @brief The cost of reaching this vertex
     */
    int dist = INT_MAX;

    /**
     * @brief The previous vertex
     */
    Vertex* src = nullptr;
};

/********************** Edge  ****************************/

/**
 * @brief Represents the path between two stations in a railway network
 */
class Edge {
public:
    Edge(Vertex *orig, Vertex *dest, double w);

    /**
     * @brief Gets the destination vertex
     * @return The destination vertex
     */
    Vertex* getDest() const;

    /**
     * @brief Gets the edge's weight/capacity
     * @return The edge's weight
     */
    double getWeight() const;

    /**
     * @brief Gets the origin vertex
     * @return The origin vertex
     */
    Vertex * getOrig() const;

    /**
     * @brief Gets the reverse edge
     * @return The reverse edge
     */
    Edge *getReverse() const;

    /**
     * @brief Gets the edge's flow
     * @return The edge's flow
     */
    double getFlow() const;

    /**
     * @brief Sets the reverse edge
     * @param reverse The reverse edge
     */
    void setReverse(Edge *reverse);

    /**
     * @brief Sets the edge's flow
     * @param flow The edge's flow
     */
    void setFlow(double flow);
private:
    /**
     * @brief The destination vertex
     */
    Vertex * dest; // destination vertex

    /**
     * @brief The edge's weight/capacity
     */
    double weight; // edge weight, can also be used for capacity

    // used for bidirectional edges
    /**
     * @brief The origin vertex
     */
    Vertex *orig;

    /**
     * @brief The reverse edge
     */
    Edge *reverse = nullptr;

    /**
     * @brief The number of trains that are simultaneously in the edge
     */
    double flow; // for flow-related problems
};

#endif //LEIC_TSP_VERTEXEDGE_H
