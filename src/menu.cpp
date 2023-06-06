#include "menu.h"

#define MAX std::numeric_limits<double>::max()

bool toggle_exec_time = false;
bool is_real = false;
bool real_chosen = false;
bool is_fully_connected = false;

Menu::Menu(): manager(Manager()) {}

void Menu::invalidInput(){
    cout << '\n';
    cout << "Uh-oh invalid option!\n";
    cin.ignore(10000, '\n');
    cin.clear();
}

void Menu::printMainMenu() {
         cout << """"
                 "----------------------------------------------------------\n"
                 "~          Welcome to the TSP Shipping Service!          ~\n"
                 "----------------------------------------------------------\n"
                 "How can we help you today?\nInsert the number of the operation (0-3).\n"
                 "-------------------------------------------------------------------------------------------------------\n"
                 "|                                                                                                     |\n"
                 "| 1 - Backtracking                                                                                    |\n"
                 "| 2 - Triangular Approximation                                                                        |\n"
                 "| 3 - Custom Heuristic                                                                                |\n"
                 "|                                                                                                     |\n"
                 "| R - Create the Route's Graph                                                                        |\n"
                 "| T - Toggle Execution Time Display                                                                   |\n"
                 "|                                                                                                     |\n"
                 "| 0 - Exit Program                                                                                    |\n"
                 "-------------------------------------------------------------------------------------------------------\n"
                 "> ";
}

void Menu::mainMenu(){
    char choice_menu, choice_submenu;
    do{
        printMainMenu();
        cin >> choice_menu;

        if (!std::cin.fail()){
            switch(choice_menu){
                case '1': {
                    if (is_real) {
                        cout << "I'm sorry, but this service isn't available right now." << endl;
                        cout << endl;
                        break;
                    }
                    int origin = 0;
                    vector<int> min_path;
                    auto start = chrono::high_resolution_clock::now();
                    cout << "Cost: " << manager.backtrack(min_path) << endl;
                    cout << endl;
                    auto end = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::duration<double>>(end - start).count();
                    cout << "Path: ";
                    for (auto element: min_path) {
                        cout << element << " -> ";
                    }
                    cout << origin << endl;

                    if (toggle_exec_time) {
                        cout << "Elapsed Time: " << duration << " s" << endl;
                    }
                    break;
                }
                case '2': {
                    if (real_chosen) {
                        double cost = 0;
                        auto start = chrono::high_resolution_clock::now();
                        vector<RealVertex *> res = manager.realTriangularApprox(cost);
                        auto end = chrono::high_resolution_clock::now();
                        auto duration = chrono::duration_cast<chrono::duration<double>>(end - start).count();
                        cout << "Path: ";
                        for (auto element: res) {
                            cout << element->getID();
                            cout << " -> ";
                        }
                        cout << "0" << endl;
                        cout << endl;
                        cout << "Cost: " << cost << endl;
                        if (toggle_exec_time) {
                            cout << "Elapsed Time: " << duration << " s" << endl;
                        }
                        break;
                    }
                    double cost = 0;
                    auto start = chrono::high_resolution_clock::now();
                    vector<Vertex *> res = manager.triangularApproximation(cost);
                    auto end = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::duration<double>>(end - start).count();
                    cout << "Path: ";
                    for (auto element: res) {
                        cout << element->getID();
                        cout << " -> ";
                    }
                    cout << "0" << endl;
                    cout << endl;
                    cout << "Cost: " << cost << endl;
                    if (toggle_exec_time) {
                        cout << "Elapsed Time: " << duration << " s" << endl;
                    }
                    break;
                }
                case '3':
                {
                    if (!is_fully_connected) {
                        cout << "I'm sorry, but this service isn't available right now." << endl;
                        cout << endl;
                        break;
                    }
                    int origin = 0;
                    vector<int> min_path;
                    auto start = chrono::high_resolution_clock::now();
                    cout << "Cost: " << manager.myHeuristic(min_path) << endl;
                    auto end = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::duration<double>>(end - start).count();
                    cout << "Path: ";
                    for (int i = 0; i < min_path.size() - 1; i++) {
                        cout << min_path[i] << "->";
                    }
                    cout << origin << endl;

                    if (toggle_exec_time) {
                        cout << "Elapsed Time: " << duration << " s" << endl;
                    }
                    break;
                }
                case 'r':
                case 'R':
                    printBuildSubMenu();
                    cin >> choice_submenu;
                    if (!std::cin.fail()){
                        switchBuildSubMenu(choice_submenu);
                    }
                    break;
                case 't':
                case 'T':
                    toggle_exec_time = !toggle_exec_time;
                    break;
                case '0':
                    cout << "So sorry to see you go! :(\n";
                    exit(0);
                default:
                    invalidInput();
                    break;
            }
        }
    } while (choice_menu != '0');
}

void Menu::printBuildSubMenu() {
    std::cout << """"
                 "How can we help you today?\nInsert the number of the operation (0-5).\n"
                 "-------------------------------------------------------------------------------------------------------\n"
                 "|                                                                                                     |\n"
                 "| 1 - Create a Toy Graph (Small)                                                                      |\n"
                 "| 2 - Create a Fully Connected Graph (Medium)                                                         |\n"
                 "| 3 - Create a Real World Graph (Large)                                                               |\n"
                 "|                                                                                                     |\n"
                 "| 0 - Exit Program                                                                                    |\n"
                 "| Any other value - Return to Main Menu                                                               |\n"
                 "-------------------------------------------------------------------------------------------------------\n"
                 "> ";
}

void Menu::switchBuildSubMenu(char option) {
    string nodes, edges;
    string graph_num;
    string path = "../data/";
    switch (option) {
        case '1':
            is_real = false;
            path = path + "Toy-Graphs/";
            cout << "Insert your routing file: ";
            cin >> edges;
            if(edges != "shipping.csv"){
                is_fully_connected = true;
            }
            edges = path + edges;
            std::cin.ignore(); //clear the buffer
            cout << endl;
            manager.buildGraph(edges);
            break;
        case '2':
            is_real = true;
            is_fully_connected = true;
            path = path + "Extra_Fully_Connected_Graphs/";
            cout << "Insert your routing file: ";
            cin >> edges;
            edges = path + edges;
            std::cin.ignore(); //clear the buffer
            cout << endl;
            manager.buildGraph(edges);
            break;
        case '3':
            is_real = true;
            real_chosen = true;
            is_fully_connected = false;
            cout << "Insert the number of the graph you wish to build: ";
            cin >> graph_num;
            if (graph_num == "1") {
                nodes =  "../data/Real-World-Graphs/graph1/nodes.csv";
                edges =  "../data/Real-World-Graphs/graph1/edges.csv";
            }
            else if (graph_num == "2") {
                nodes =  "../data/Real-World-Graphs/graph2/nodes.csv";
                edges =  "../data/Real-World-Graphs/graph2/edges.csv";
            }
            else if (graph_num == "3") {
                nodes =  "../data/Real-World-Graphs/graph3/nodes.csv";
                edges =  "../data/Real-World-Graphs/graph3/edges.csv";
            }
            else {
                cout << "That option is invalid! Returning to the Main Menu." << endl;
                break;
            }
            std::cin.ignore(); //clear the buffer
            cout << endl;
            manager.buildRealGraph(nodes);
            manager.buildRealNetwork(edges);
            break;
        case '0':
            std::cout << "So sorry to see you go! :(\n";
            exit(0);
        default:
            std::cout << "Redirecting to main menu...\n";
            std::this_thread::sleep_for(std::chrono::seconds(2));
            break;
    }
}