#include "manager.h"

#define endF "../data/Toy-Graphs/shipping.csv"
#define realNF "../data/Real-World-Graphs/graph1/nodes.csv"
#define realEF "../data/Real-World-Graphs/graph1/edges.csv"

#define MAX std::numeric_limits<double>::max()

Manager::Manager() {
    this->network = new Graph();
    this->real_network = new RealGraph();
    // buildGraph(endF);
    /*buildRealGraph(realNF);
    buildRealNetwork(realEF);*/
}

Manager::~Manager() {
    delete network;
    delete real_network;
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

void Manager::buildRealGraph(const string& filename) {
    string node, latitude, longitude;
    int count = 0;
    ifstream thefile(filename);

    if (thefile.is_open())
    {
        string fline;
        getline(thefile, fline);

        while (!thefile.eof()) {
            getline(thefile, node, ',');
            getline(thefile, latitude, ',');
            getline(thefile, longitude, '\n');

            if (node.size() == 0) {
                continue;
            }

            //cout << orig << "||" << dest << "||" << dist << endl;

            int node_id = stoi(node);
            double lon = stod(longitude);
            double lat = stod(latitude);

            real_network->addVertex(node_id, lon, lat);
            count++;
        }
        thefile.close();
    }
    else
    {
        cout << "Error: The program was unable to open the file.";
    }
    cout << count << endl;
}

void Manager::buildRealNetwork(const string& filename) {
    string orig, dest, dist;
    int count = 0;
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

            int orig_id = stoi(orig);
            int dest_id = stoi(dest);
            double distance = stod(dist);

            real_network->addBidirectionalEdge(orig_id, dest_id, distance);
            count++;
        }
        thefile.close();
    }
    else
    {
        cout << "Error: The program was unable to open the file.";
    }
    cout << count << endl;
}

void Manager::testing() {
    cout << network->getNumVertex() << endl;
    // cout << real_network.getNumVertex() << endl;
    cout << network->getNumEdges() << endl;
    cout << network->getVertexSet().at(2)->getID() << endl;
    Vertex* v = network->findVertex(0);
    int n = network->getNumVertex();
    vector<bool> visit(n, false);
    int counter = 0;
    double distance = 0;
    double min_distance = MAX;
    vector<int> min_path;
    vector<int> test;
    cout << network->bruteforceBacktrack(v,v, counter, distance, min_distance, visit, min_path, test);
    cout << endl;
    for (auto element: min_path) {
        cout << element << "->";
    }
    cout << v->getID() << endl;
}

double Manager::backtrack(vector<int> &min_path) {
    vector<Vertex*> mst = network->prim(0, 12);
    for (auto element: mst) {
        cout << element->getID() << " | ";
    }
    cout << endl;
    Vertex *v = network->findVertex(0);
    int n = network->getNumVertex();
    vector<bool> visit(n, false);
    int counter = 0;
    double distance = 0;
    double min_distance = MAX;
    vector<int> test;
    return network->bruteforceBacktrack(v, v, counter, distance, min_distance, visit, min_path, test);
}

/*int Manager::numTest() {
    cout << real_network->getNumVertex() << endl;
}*/