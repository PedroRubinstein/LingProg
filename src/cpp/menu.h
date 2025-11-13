#ifndef MENU_H
#define MENU_H

#include <vector>

#include "geometricObjects/geometricobject.h"
#include "plotter.h"
#include "calculator.h"

class Menu {
    public:
        Menu() = default;
        ~Menu();
        void showMenu();
    private:
        void processOption(int option);
        int getNumericInput();

        // object management related
        void manageObjects();
        void addObject(geometricObject* obj = nullptr);
        void removeObject();
        void listObjects();
        void saveObjects(); //ver o template, botei qq coisa
        void loadObjects(); //ver o template, botei qq coisa

        // calculator related
        void manageCalculator();

        // plot related
        void managePlotter();

        void askAddResult(geometricObject* obj);
        int getMaxId() {return 0;}; // Returns the maximum ID among existing objects in the database, 
        // or 0 if none exist. TO BE DONE (MIGHT NOT BELONG TO THIS CLASS)
        std::vector<geometricObject *> geometricObjects;
        Plotter plotter;
};

#endif // MENU_H
