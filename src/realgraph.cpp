#include "realgraph.h"

#define MAX std::numeric_limits<double>::max()

RealVertex* RealGraph::findVertex(int id) const {
    for (auto v: vertexSet) {
        if (v.first == id) {
            return v.second;
        }
    }

    return nullptr;
}

bool RealGraph::addVertex(int id, double lon, double lat) {
    if (findVertex(id) != nullptr) {
        return false;
    }

    vertexSet.emplace(id, new RealVertex(id, lon, lat));
    return true;
}

bool RealGraph::removeVertex(int id) {
    RealVertex* node = findVertex(id);

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

bool RealGraph::addEdge(int source, int dest, double weight) {
    auto v1 = vertexSet[source];
    auto v2 = vertexSet[dest];
    if (v1 == nullptr || v2 == nullptr) {
        return false;
    }

    v1->addEdge(v2, weight);
    return true;
}

bool RealGraph::addBidirectionalEdge(int source, int dest, double weight) {
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

int RealGraph::getNumVertex() const {
    return this->vertexSet.size();
}

unordered_map<int, RealVertex *> RealGraph::getVertexSet() const {
    return this->vertexSet;
}

int RealGraph::getNumEdges() const {
    int res = 0;
    for (auto v: vertexSet) {
        res += v.second->getAdj().size();
    }
    return res;
}

vector<RealVertex*> RealGraph::prim(int source, double &tspCost, RealGraph &mst_graph) {
    vector<RealVertex*> path;

    MutablePriorityQueue<RealVertex> pq;
    RealVertex* src = findVertex(source);

    for (auto node : vertexSet) {
        mst_graph.addVertex(node.second->getID(), node.second->getLongitude(), node.second->getLatitude());
        node.second->setVisited(false);
        node.second->setDistance(MAX);
        node.second->setPath(nullptr);
    }

    src->setDistance(0);
    pq.insert(src);

    while (!pq.empty()) {
        RealVertex* t = pq.extractMin();

        if (t->isVisited()) {
            continue;
        }

        t->setVisited(true);

        if (t->getID() != src->getID()) {
            mst_graph.addBidirectionalEdge(t->getPath()->getOrig()->getID(), t->getID(), t->getPath()->getWeight());
        }

        for (auto e : t->getAdj()) {
            RealVertex *v = e->getDest();
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

    RealVertex* mst_src = mst_graph.findVertex(source);
    for (auto v: vertexSet) {
        v.second->setVisited(false);
    }

    path.clear();
    int id;
    preorderTraversal(mst_src, path, tspCost, id);

    return path;
}

void RealGraph::preorderTraversal(RealVertex* v, vector<RealVertex*> &path, double &cost, int &prev_id) {
    unsigned int signal = 1;
    RealVertex* x = this->findVertex(v->getID());
    path.push_back(x);
    v->setVisited(true);

    for (auto e: v->getAdj()) {
        RealVertex* t = e->getDest();
        if (!t->isVisited() && signal) {
            prev_id = t->getID();
            cost += e->getWeight();
        }
        else if (!t->isVisited()) {
            RealVertex* s = findVertex(prev_id);
            cost += costCalculation(s, t);
            prev_id = t->getID();
        }
        signal = 0;

        if (!t->isVisited()) {
            preorderTraversal(t, path, cost, prev_id);
        }
    }
}

double RealGraph::costCalculation(RealVertex* s, RealVertex* t) {
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