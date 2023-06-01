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

void Graph::dfs(int id) {
    for (auto itr = vertexSet.begin(); itr != vertexSet.end(); itr++) {
        (*itr)->setVisited(false);
    }

    Vertex* node = findVertex(id);
    node->setVisited(true);

    for (auto itr = node->getAdj().begin(); itr != node->getAdj().end(); itr++) {
        Vertex* target = findVertex((*itr)->getDest()->getID());

        if (!target->isVisited()) {
            dfs((*itr)->getDest()->getID());
        }
    }
}

vector<Vertex *> Graph::prim() {
    MutablePriorityQueue<Vertex> q;

    for (auto v: vertexSet){
        v->setDistance(HIGH);
        v->setVisited(false);
        q.insert(v);
    }

    vertexSet[0]->setVisited(true);
    vertexSet[0]->setPath(nullptr);
    vertexSet[0]->setDistance(0);

    q.decreaseKey(vertexSet[0]);

    while (!q.empty()){
        Vertex* u = q.extractMin();
        for (Edge* e : u->getAdj()){
            Vertex* w = e->getDest();
            if (!w->isVisited() && e->getWeight() < w->getDistance()){
                w->setPath(e);
                w->setDistance(e->getWeight());
                q.decreaseKey(w);
            }
        }
        u->setVisited(true);
    }

    return this->vertexSet;
}