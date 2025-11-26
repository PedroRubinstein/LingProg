#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>
#include <functional> 
#include "geometricObjects/geometricobject.h" 
#include "plotter.h"         
#include "calculator.h"      

class Menu {
public:
    Menu(); 
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

    // Registry structure for Calculator operations
    struct CalculatorOp {
        std::string name;
        std::function<void()> action;
    };
    std::vector<CalculatorOp> calculatorOperations;
    void registerCalculatorOperations();

    void addObject(geometricObject* obj = nullptr);
    void removeObject();
    void listObjects();
    void loadObjects(); // Kept 'load' for syncing/reverting, removed 'save'

    void askAddResult(geometricObject* obj);
    int getMaxId();

    geometricObject* getObjectFromUser(int type);

    std::vector<geometricObject*> geometricObjects;
    Plotter plotter;
};

#endif
