#include <iostream>
#include "manager.h"
#include "menu.h"


int main() {
    Manager manager = Manager();
    manager.testing();
    Menu menu = Menu();
    menu.mainMenu();
    return 0;
}