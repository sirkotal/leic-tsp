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
    bool operator()(const Edge* x, const Edge* y) {
        return x->getWeight() > y->getWeight();
    }
};

void Graph::prim(vector<Edge*> mst, double &tspCost) {
    priority_queue<Edge*, vector<Edge*>, PriorityCompare> pq;

    Vertex* src = this->findVertex(0);

    // Add the edges connected to the source vertex to the priority queue
    for (auto e : src->getAdj()) {
        if (e->getOrig() == src)
            pq.push(e);
    }

    src->setVisited(true);

    while (!pq.empty()) {
        Edge* e = pq.top();
        pq.pop();

        Vertex* u = e->getOrig();
        Vertex* v = e->getDest();

        if (v->isVisited())
            continue;

        v->setVisited(true);

        mst.push_back(e);

        for (const auto& neighbor : this->vertexSet) {
            if (neighbor == v) {
                for (auto edge : neighbor->getAdj()){
                    if(!edge->getDest()->isVisited()){
                        pq.push(edge);
                    }
                }
            }
        }
    }
    for (auto element: mst) {
        //cout << element->getOrig()->getID() << "->" << element->getDest()->getID() << " ";
        Vertex* o = element->getOrig();
        Vertex* d = element->getDest();
        o->addAuxEdge(d, element->getWeight());
        d->addAuxEdge(o, element->getWeight());
    }

    for (auto node : vertexSet){
        node->setVisited(false);
    }

    /*for (auto element: findVertex(1)->aux) {
        cout << element->getDest()->getID() << endl;
    }*/
}

void Graph::preorderTraversal(Vertex* n, vector<Vertex*> &path, double &cost) {
    if (n->getID() == 0) {
        path.push_back(n);
        n->setVisited(true);
    }

    for (auto e: n->aux) {
        Vertex* t = e->getDest();
        double w = e->getWeight();
        if (!t->isVisited()) {
            t->setVisited(true);
            path.push_back(t);
            cost += w;
            cout << n->getID() << " | " << t->getID() << " | " << e->getWeight() << " | " << cost << endl;
            preorderTraversal(t, path, cost);
        }
    }
}