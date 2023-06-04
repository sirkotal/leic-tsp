#ifndef LEIC_TSP_MENU_H
#define LEIC_TSP_MENU_H

#include <iostream>
#include <thread>
#include <chrono>
// #include "gnuplot-iostream.h"
#include "manager.h"

using namespace std;

/**
 * @brief Represents the shipping/delivery network heuristics system's menu
 */
class Menu {
public:
    Menu();

    /**
     * @brief If the option chosen in the main menu is invalid, clears the buffer
     */
    void invalidInput();

    /**
     * @brief Displays the main menu, indicating the meaning of each option
     */
    void printMainMenu();

    /**
     * @brief According to the chosen option, presents and deals with the options to choose: heuristics, create a shipping/delivery network or exit the program.
     */
    void mainMenu();

    /**
     * @brief Displays the "Create the Route's Graph" menu, indicating the meaning of each option
     */
    void printBuildSubMenu();

    /**
     * @brief According to the chosen option, builds a graph for the user
     * @param option Option chosen by the user
     */
    void switchBuildSubMenu(char option);


private:
    /**
     * @brief A manager that handles the interface between the graph and the menu
     */
    Manager manager;
};

#endif //LEIC_TSP_MENU_H
