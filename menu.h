#ifndef MENU_H
#define MENU_H

#include "geometricobject.h"
#include "plotter.h"
#include <vector>

class Menu {
    public:
        void processOption(int option);
        void manageObjects();
        void showMenu();
    private:
        std::vector<geometricObject *> geometricObjects;
};

#endif // MENU_H