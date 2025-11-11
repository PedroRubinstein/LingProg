#ifndef MENU_H
#define MENU_H

#include "geometricobject.h"
#include "plotter.h"
#include <vector>

class Menu {
    public:
        void showMenu();
    private:
        void processOption(int option);
        int getNumericInput();
        void manageObjects();
        void addObject();
        void removeObject();
        void listObjects();
        void saveObjects(); //ver o template, botei qq coisa
        void loadObjects(); //ver o template, botei qq coisa
        std::vector<geometricObject *> geometricObjects;
};

#endif // MENU_H