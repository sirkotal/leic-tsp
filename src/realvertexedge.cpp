#include "realvertexedge.h"

/************************* Vertex  **************************/

RealVertex::RealVertex(int id, double longitude, double latitude): id(id),  longitude(longitude),  latitude(latitude) {}

RealEdge * RealVertex::addEdge(RealVertex *d, double w) {
    auto newEdge = new RealEdge(this, d, w);
    adj.push_back(newEdge);
    d->incoming.push_back(newEdge);
    return newEdge;
}

bool RealVertex::removeEdge(int destID) {
    bool removedEdge = false;
    auto it = adj.begin();
    while (it != adj.end()) {
        RealEdge *edge = *it;
        RealVertex *dest = edge->getDest();
        if (dest->getID() == destID) {
            it = adj.erase(it);
            // Also remove the corresponding edge from the incoming list
            auto it2 = dest->incoming.begin();
            while (it2 != dest->incoming.end()) {
                if ((*it2)->getOrig()->getID() == this->id) {
                    it2 = dest->incoming.erase(it2);
                }
                else {
                    it2++;
                }
            }
            delete edge;
            removedEdge = true; // allows for multiple edges to connect the same pair of vertices (multigraph)
        }
        else {
            it++;
        }
    }
    return removedEdge;
}

int RealVertex::getID() const {
    return this->id;
}

double RealVertex::getLongitude() const {
    return this->longitude;
}

double RealVertex::getLatitude() const {
    return this->latitude;
}

std::vector<RealEdge*> RealVertex::getAdj() const {
    return this->adj;
}

int RealVertex::getDistance() const {
    return this->dist;
}

bool RealVertex::isVisited() const {
    return this->visited;
}

bool RealVertex::isProcessing() const {
    return this->processing;
}

unsigned int RealVertex::getIndegree() const {
    return this->indegree;
}

RealEdge* RealVertex::getPath() const {
    return this->path;
}

std::vector<RealEdge *> RealVertex::getIncoming() const {
    return this->incoming;
}

void RealVertex::setVisited(bool visited) {
    this->visited = visited;
}

void RealVertex::setProcesssing(bool processing) {
    this->processing = processing;
}

void RealVertex::setIndegree(unsigned int indegree) {
    this->indegree = indegree;
}

void RealVertex::setPath(RealEdge *path) {
    this->path = path;
}

void RealVertex::setDistance(int num) {
    this->dist = num;
}

/********************** Edge  ****************************/

RealEdge::RealEdge(RealVertex *orig, RealVertex *dest, double w): orig(orig), dest(dest), weight(w) {}

RealVertex* RealEdge::getDest() const {
    return this->dest;
}

double RealEdge::getWeight() const {
    return this->weight;
}

RealVertex* RealEdge::getOrig() const {
    return this->orig;
}

RealEdge* RealEdge::getReverse() const {
    return this->reverse;
}

double RealEdge::getFlow() const {
    return flow;
}

void RealEdge::setReverse(RealEdge *reverse) {
    this->reverse = reverse;
}

void RealEdge::setFlow(double flow) {
    this->flow = flow;
}
