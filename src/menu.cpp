#include "menu.h"

#define MAX std::numeric_limits<double>::max()

bool toggle_exec_time = false;

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
                 "| 2 - Cost Optimization                                                                               |\n"
                 "| 3 - Reliability and Sensitivity to Line Failures                                                    |\n"
                 "|                                                                                                     |\n"
                 "| R - Create the Route graph                                                                          |\n"
                 "|                                                                                                     |\n"
                 "| 0 - Exit Program                                                                                    |\n"
                 "-------------------------------------------------------------------------------------------------------\n"
                 "> ";
}


void Menu::dataBuilder(const string &f) {
    manager.buildGraph(f);
}

void Menu::realDataBuilder(const string &n, const string &e) {
    manager.buildRealGraph(n);
    manager.buildRealNetwork(e);
}

void Menu::mainMenu(){
    char choice_menu, choice_submenu;
    Menu menu = Menu();
    do{
        menu.printMainMenu();
        cin >> choice_menu;

        if (!std::cin.fail()){
            switch(choice_menu){
                case '1': {
                    int origin = 0;
                    vector<int> min_path;
                    cout << manager.backtrack(min_path) << endl;
                    for (auto element: min_path) {
                        cout << element << "->";
                    }
                    cout << origin << endl;
                    break;
                }
                /*case '2':
                    menu.printSubMenu2();
                    cin >> choice_submenu;
                    if (!std::cin.fail()){
                        menu.switchSubMenu2(choice_submenu);
                    }
                    break;
                case '3':
                    menu.printSubMenu3();
                    cin >> choice_submenu;
                    if (!std::cin.fail()){
                        menu.switchSubMenu3(choice_submenu);
                    }
                    break;*/
                case 'r':
                case 'R':
                    menu.printBuildSubMenu();
                    cin >> choice_submenu;
                    if (!std::cin.fail()){
                        menu.switchBuildSubMenu(choice_submenu);
                    }
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
    string path = "../data/";
    switch (option) {
        case '1':
            path = path + "Toy-Graphs/";
            cout << "Insert your routing file: ";
            cin >> edges;
            edges = path + edges;
            std::cin.ignore(); //clear the buffer
            cout << endl;
            manager.buildGraph(edges);
            break;
        case '2':
            path = path + "Extra_Fully_Connected_Graphs/";
            cout << "Insert your routing file: ";
            cin >> edges;
            edges = path + edges;
            std::cin.ignore(); //clear the buffer
            cout << endl;
            manager.buildGraph(edges);
            break;
        case '3':
            path = path + "Real-World-Graphs/";
            cout << "Insert your routing's nodes file: ";
            cin >> nodes;
            edges = path + nodes;
            std::cin.ignore(); //clear the buffer
            cout << endl;

            cout << "Insert your routing's edges file: ";
            cin >> edges;
            edges = path + edges;
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