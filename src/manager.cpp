#include "manager.h"

#define endF "../data/Toy-Graphs/shipping.csv"

Manager::Manager() {
    this->network = new Graph();
    buildGraph(endF);
}

Manager::~Manager() {
    delete network;
}

void Manager::buildGraph(const string& filename) {
    string orig, dest, dist;

    ifstream thefile(filename);

    if (thefile.is_open())
    {
        string fline;
        getline(thefile, fline);

        while (!thefile.eof()) {
            getline(thefile, orig, ',');
            getline(thefile, dest, ',');
            getline(thefile, dist, '\n');

            if (orig.size() == 0) {
                continue;
            }

            //cout << orig << "||" << dest << "||" << dist << endl;

            int orig_id = stoi(orig);
            int dest_id = stoi(dest);
            double distance = stod(dist);

            network->addVertex(orig_id);
            network->addVertex(dest_id);
            network->addBidirectionalEdge(orig_id, dest_id, distance);
        }
        thefile.close();
    }
    else
    {
        cout << "Error: The program was unable to open the file.";
    }
}

void Manager::testing() {
    cout << network->getNumVertex() << endl;
    cout << network->getNumEdges() << endl;
    cout << network->getVertexSet().at(2)->getID() << endl;
}