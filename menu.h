#ifndef MENU_H
#define MENU_H

#include "geometricobject.h"
#include "plotter.h"
#include "calculator.h"
#include <vector>

class Menu {
    public:
        Menu() = default;
        ~Menu();
        void showMenu();
    private:
        void processOption(int option);
        int getNumericInput();
        void manageObjects();
        void addObject(geometricObject* obj = nullptr);
        void removeObject();
        void listObjects();
        void saveObjects(); //ver o template, botei qq coisa
        void loadObjects(); //ver o template, botei qq coisa
        void manageCalculator();
        void askAddResult(geometricObject* obj);
        int getMaxId() {return 0;}; // Returns the maximum ID among existing objects in the database, 
        // or 0 if none exist. TO BE DONE (MIGHT NOT BELONG TO THIS CLASS)
        std::vector<geometricObject *> geometricObjects;
};

#endif // MENU_H