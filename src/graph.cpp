#include "graph.h"
#include <algorithm>

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
                                double min_distance, vector<int> &min_path, vector<int> &pathTSP) {
    current->setVisited(true);
    pathTSP.push_back(current->getID());
    counter++;

    if (counter == getNumVertex()) {
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
            if (!adj->isVisited()) {
                double updated_distance = distance + e->getWeight();
                min_distance = bruteforceBacktrack(adj, start, counter, updated_distance, min_distance, min_path, pathTSP);
            }
        }
    }

    current->setVisited(false);
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

    return path;
}

void Graph::preorderTraversal(Vertex* v, vector<Vertex*> &path, double &cost, int &prev_id) {
    unsigned int signal = 1;
    Vertex* x = this->findVertex(v->getID());
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

double Graph::myHeuristic(Vertex* current, Vertex* start, double dist, vector<int> &pathTSP, int size){


    //vamos somente entrar com :
    //start & pathTSP

    current->setVisited(true);
    pathTSP.push_back(current->getID());

    if(size == pathTSP.size()){
    //ended, put 0 and add the final distance
        for(auto i : current->getAdj())
        {
            if(i->getDest()->getID() == pathTSP.front())
            {
                pathTSP.push_back(start->getID());
                dist += i->getWeight();
                return dist;
            }
        }
    }
    else {
        double minCurrentDist = MAX;
        Vertex *minVertex = start;
        for (auto a: current->getAdj()) {
            if (!a->getDest()->isVisited()) {
                double newDist = a->getWeight();
                if (newDist < minCurrentDist) {
                    minCurrentDist = newDist;
                    minVertex = a->getDest();
                }
            }
        }
        dist = myHeuristic(minVertex, start, (dist + minCurrentDist), pathTSP, size);
    }


   // 2-opt
        int numNodes = pathTSP.size();
        bool improve = true;

        while(improve){
            improve = false;
            for (int i = 0; i < numNodes - 3; i++) {
                    Vertex* v1 =  findVertex(pathTSP[i]);
                    Vertex* v2 =  findVertex(pathTSP[i+1]);
                    Vertex* v3 =  findVertex(pathTSP[i+2]);
                    Vertex* v4 =  findVertex(pathTSP[i+3]);

                    double dist1_2, dist3_4, dist1_3, dist2_4;
                    for (auto edge : v1->getAdj()) {
                        if (edge->getDest() == v2) {
                            dist1_2 = edge->getWeight();
                            break;
                        }
                    }
                    for (auto edge : v3->getAdj()) {
                        if (edge->getDest() == v4) {
                            dist3_4 = edge->getWeight();
                            break;
                        }
                    }
                    for (auto edge : v1->getAdj()) {
                        if (edge->getDest() == v3) {
                            dist1_3 = edge->getWeight();
                            break;
                        }
                    }


                    for (auto edge : v2->getAdj()) {
                        if (edge->getDest() == v4) {
                            dist2_4 =  edge->getWeight();
                            break;
                        }
                    }


                    // Fazer a troca
                    double newDist;
                    double a = dist1_2 + dist3_4;
                    double b = dist2_4 + dist1_3;

                    // Se o novo caminho for mais curto, aceitar a troca
                    if (b < a) {
                        improve = true;
                        dist = dist + b - a;
                        swap(pathTSP[i+1],pathTSP[i+2]);
                    }
                }
            }

    return dist;
}
