#include "graph.h"

#define MAX std::numeric_limits<double>::max()
#define HIGH INT32_MAX

/*Graph::Graph(Graph& g) {
    for (auto v : g.getVertexSet()) {
        addVertex(v->getStation());
    }

    for (auto v : g.getVertexSet()) {
        auto v_copy = findVertex(v->getStation().getName());
        for (auto e : v->getAdj()) {
            auto w = e->getDest();
            auto w_copy = findVertex(w->getStation().getName());
            addEdge(v_copy->getStation().getName(), w_copy->getStation().getName(), e->getWeight(), e->getService());
        }
    }
}*/

Vertex* Graph::findVertex(int id) const {
    for (auto v: vertexSet) {
        if (v->getID() == id) {
            return v;
        }
    }

    return nullptr;
}

bool Graph::addVertex(int id) {
    if (findVertex(id) != nullptr) {
        return false;
    }

    vertexSet.push_back(new Vertex(id));
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
        if ((*itr)->getID() == id) {
            vertexSet.erase(itr);
            itr--;
            break;
        }
    }

    delete node;
    return true;
}

bool Graph::addEdge(int source, int dest, double weight) {
    auto v1 = findVertex(source);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr) {
        return false;
    }

    v1->addEdge(v2, weight);
    return true;
}

bool Graph::addBidirectionalEdge(int source, int dest, double weight) {
    auto v1 = findVertex(source);
    auto v2 = findVertex(dest);
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

vector<Vertex *> Graph::getVertexSet() const {
    return this->vertexSet;
}

int Graph::getNumEdges() const {
    int res = 0;
    for (auto v: vertexSet) {
        res += v->getAdj().size();
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

vector<Vertex*> Graph::prim(int source, double &tspCost) {
    vector<Vertex*> path;
    priority_queue<Vertex*, vector<Vertex*>, PriorityCompare> pq;
    Vertex* src = findVertex(source);
    for (auto node : vertexSet){
        node->setVisited(false);
        node->setDistance(INT_MAX);
        node->setPath(nullptr);
    }

    src->setDistance(0);
    pq.push(src);

    while (!pq.empty()) {
        Vertex* t = pq.top();
        pq.pop();

        t->setVisited(true);

        for (auto e : t->getAdj()) {
            Vertex *v = e->getDest();
            double w = e->getWeight();

            if (!v->isVisited() && w < v->getDistance()) {
                v->setSRC(t);
                v->setDistance(w);
                pq.push(v);
            }
        }
    }
    for (auto v: vertexSet) {
        v->setVisited(false);
    }

    path.clear();

    preorderTraversal(src, path, tspCost);
    return path;
}

void Graph::preorderTraversal(Vertex* v, vector<Vertex*> &path, double &cost) {
    if (v == nullptr) {
        return;
    }
    path.push_back(v);
    v->setVisited(true);

    for (auto e : v->getAdj()) {
        Vertex* t = e->getDest();
        double w = e->getWeight();
        if (t->getSRC() == v && !t->isVisited()) {
            cost += w;
            preorderTraversal(t, path, cost);
        }
    }
}


double Graph::myHeuristic(Vertex* current, Vertex* start, double dist, vector<int> &pathTSP, int size){


    //vamos somente entrar com :
    //start & pathTSP

    current->setVisited(true);
    pathTSP.push_back(current->getID());

    if(size  == pathTSP.size()){
    //ended, put 0 and add the final distance
        pathTSP.push_back(start->getID());
        for(auto i : current->getAdj())
        {
            if(i->getDest() == start)
            {
                dist += i->getWeight();
                current = start;
                return dist;
            }
        }
    }
    else {
        double minCurrentDist = MAX;
        Vertex *minVertex;
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
    if (pathTSP.size() == size + 1){
        int numNodes = pathTSP.size();
        bool improve = true;

        while (improve){
            improve = false;
            for (int i = 0; i < numNodes - 2; ++i) {
                for (int j = i + 2; j < numNodes; ++j) {
                    Vertex* v1 =  findVertex(i);
                    Vertex* v2 =  findVertex(i + 1);
                    Vertex* v3 =  findVertex(j);
                    Vertex* v4 =  findVertex(j + 1);

                    double dist1, dist2, dist3, dist4;
                    for (const auto& edge : v1->getAdj()) {
                        if (edge->getDest() == v2) {
                            dist1 = edge->getWeight();
                            break;
                        }
                    }
                    for (const auto& edge : v3->getAdj()) {
                        if (edge->getDest() == v4) {
                            dist2 = edge->getWeight();
                            break;
                        }
                    }
                    for (const auto& edge : v1->getAdj()) {
                        if (edge->getDest() == v3) {
                            dist3 = edge->getWeight();
                            break;
                        }
                    }
                    for (const auto& edge : v2->getAdj()) {
                        if (edge->getDest() == v4) {
                            dist4 =  edge->getWeight();
                            break;
                        }
                    }

                    // Fazer a troca
                    double newDist = dist - dist1 - dist2;
                    newDist += dist3 + dist4;

                    // Se o novo caminho for mais curto, aceitar a troca
                    if (newDist < dist) {
                        improve = true;
                        dist = newDist;
                        std::reverse(pathTSP.begin() + i + 1, pathTSP.begin() + j + 1);
                    }
                }
            }

            }

    }

    return dist;
}
