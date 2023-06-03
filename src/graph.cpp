#include "graph.h"

#define MAX std::numeric_limits<double>::max()

Vertex* Graph::findVertex(int id) const {
    for (auto v: vertexSet) {
        if (v.first == id) {
            return v.second;
        }
    }

    return nullptr;
}

bool Graph::addVertex(int id) {
    if (findVertex(id) != nullptr) {
        return false;
    }

    vertexSet.emplace(id, new Vertex(id));
    return true;
}

bool Graph::removeVertex(int id) {
    Vertex* node = findVertex(id);

    if (node == nullptr) {
        return false;
    }

    for (auto e : node->getAdj()) {
        auto w = e->getDest();
        w->removeEdge(node->getID());
        node->removeEdge(w->getID());
    }

    for (auto itr = vertexSet.begin(); itr != vertexSet.end(); itr++) {
        if ((*itr).first == id) {
            vertexSet.erase(itr);
            break;
        }
    }

    delete node;
    return true;
}

bool Graph::addEdge(int source, int dest, double weight) {
    auto v1 = vertexSet[source];
    auto v2 = vertexSet[dest];
    if (v1 == nullptr || v2 == nullptr) {
        return false;
    }

    v1->addEdge(v2, weight);
    return true;
}

bool Graph::addBidirectionalEdge(int source, int dest, double weight) {
    auto v1 = vertexSet[source];
    auto v2 = vertexSet[dest];
    if (v1 == nullptr || v2 == nullptr) {
        return false;
    }

    auto e1 = v1->addEdge(v2, weight);
    auto e2 = v2->addEdge(v1, weight);

    e1->setReverse(e2);
    e2->setReverse(e1);

    return true;
}

int Graph::getNumVertex() const {
    return this->vertexSet.size();
}

unordered_map<int, Vertex*> Graph::getVertexSet() const {
    return this->vertexSet;
}

int Graph::getNumEdges() const {
    int res = 0;
    for (auto v: vertexSet) {
        res += v.second->getAdj().size();
    }
    return res;
}

double Graph::bruteforceBacktrack(Vertex* current, Vertex* start, int counter, double distance,
                                double min_distance, vector<bool> &visited, vector<int> &min_path, vector<int> &pathTSP) {
    visited[current->getID()] = true;
    pathTSP.push_back(current->getID());
    counter++;

    if (counter == visited.size()) {
        for (auto e : current->getAdj()) {
            if (e->getDest() == start) {
                double total_distance = distance + e->getWeight();
                if (total_distance < min_distance) {
                    min_distance = total_distance;
                    min_path = pathTSP;
                }
                break;
            }
        }
    }
    else {
        for (auto e : current->getAdj()) {
            Vertex* adj = e->getDest();
            if (!visited[adj->getID()]) {
                double updated_distance = distance + e->getWeight();
                min_distance = bruteforceBacktrack(adj, start, counter, updated_distance, min_distance, visited, min_path, pathTSP);
            }
        }
    }

    visited[current->getID()] = false;
    pathTSP.pop_back();
    counter--;

    return min_distance;
}

/**
 * @brief Allows the sorting of the graph's vertexes by descending order of distance
 */
struct PriorityCompare {
    /**
     * @brief Sorts two vertexes by distance
     * @param s The first vertex
     * @param t The second vertex
     * @return True if the first vertex's distance is bigger than the second's; otherwise, it returns false
     */
    bool operator()(const Vertex* s, const Vertex* t) {
        return s->getDistance() > t->getDistance();
    }
};

vector<Vertex*> Graph::prim(int source, double &tspCost, Graph &mst_graph) {
    vector<Vertex*> path;

    MutablePriorityQueue<Vertex> pq;
    Vertex* src = vertexSet[source];

    for (auto node : vertexSet) {
        mst_graph.addVertex(node.second->getID());
        node.second->setVisited(false);
        node.second->setDistance(MAX);
        node.second->setPath(nullptr);
    }

    src->setDistance(0);
    pq.insert(src);

    while (!pq.empty()) {
        Vertex* t = pq.extractMin();

        if (t->isVisited()) {
            continue;
        }

        t->setVisited(true);

        if (t->getID() != src->getID()) {
            mst_graph.addBidirectionalEdge(t->getPath()->getOrig()->getID(), t->getID(), t->getPath()->getWeight());
        }

        for (auto e : t->getAdj()) {
            Vertex *v = e->getDest();
            double w = e->getWeight();

            if (!v->isVisited() && w < v->getDistance()) {
                v->setPath(e);
                double prev_dist = v->getDistance();
                v->setDistance(w);
                if (prev_dist == MAX) {
                    pq.insert(v);
                }
                else {
                    pq.decreaseKey(v);
                }
            }
        }
    }

    Vertex* mst_src = mst_graph.vertexSet[source];
    for (auto v: vertexSet) {
        v.second->setVisited(false);
    }

    path.clear();
    int id;
    preorderTraversal(mst_src, path, tspCost, id);

    /*for (auto element: mst_graph.vertexSet) {
        cout << element->getID() << endl;
    }*/

    return path;
}

void Graph::preorderTraversal(Vertex* v, vector<Vertex*> &path, double &cost, int &prev_id) {
    unsigned int signal = 1;
    Vertex* x = this->findVertex(v->getID());
    // cout << "(" << x->getID() << ")" << endl;
    path.push_back(x);
    v->setVisited(true);

    for (auto e: v->getAdj()) {
        Vertex* t = e->getDest();
        if (!t->isVisited() && signal) {
            prev_id = t->getID();
            cost += e->getWeight();
        }
        else if (!t->isVisited()) {
            Vertex* s = vertexSet[prev_id];
            cost += costCalculation(s, t);
            prev_id = t->getID();
        }
        signal = 0;

        if (!t->isVisited()) {
            preorderTraversal(t, path, cost, prev_id);
        }
    }
}

double Graph::costCalculation(Vertex* s, Vertex* t) {
    if (s == nullptr) {
        return 0.0;
    }

    for (auto e: s->getAdj()) {
        if (e->getDest()->getID() == t->getID()) {
            return e->getWeight();
        }
    }

    return 0.0;
}
