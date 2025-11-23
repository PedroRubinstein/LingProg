#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>
#include "geometricobject.h" 
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

    void pauseForEnter();

    void manageObjects();
    void manageCalculator();
    void manageConvexHull();
    void manageMinCircle();
    void managePlotter();

    void addObject(geometricObject* obj = nullptr);
    void removeObject();
    void listObjects();
    void saveObjects();
    void loadObjects();

    void askAddResult(geometricObject* obj);

    int getMaxId();

    std::vector<geometricObject*> geometricObjects;
    Plotter plotter;
};

#endif 
