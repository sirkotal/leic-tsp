#ifndef LEIC_TSP_MENU_H
#define LEIC_TSP_MENU_H

#include <iostream>
#include <thread>
#include <chrono>
// #include "gnuplot-iostream.h"
#include "manager.h"

using namespace std;

/**
 * @brief Represents the railway network management system's menu
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
     * @brief Builds a graph containing the railway's train stations and its connections
     * @param r File containing the train stations' information
     * @param n File containing the railway network's information
     */
    void dataBuilder(const string &f);

    /**
     * @brief Builds a graph containing the railway's train stations and its connections
     * @param r File containing the train stations' information
     * @param n File containing the railway network's information
     */
    void realDataBuilder(const string &n, const string &e);

    /**
     * @brief According to the chosen option, presents and deals with the options to choose: submenus, create a railway network or exit the program.
     */
    void mainMenu();

    void printBuildSubMenu();

    void switchBuildSubMenu(char option);


private:
    /**
     * @brief A manager that handles the interface between the graph and the menu
     */
    Manager manager;
};

#endif //LEIC_TSP_MENU_H
