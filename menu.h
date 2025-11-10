#ifndef MENU_H
#define MENU_H

#include "geometricobject.h"
#include <vector>

class Menu {
    public:
        void processarOpcao(int opcao);
        void exibirMenu();
    private:
        std::vector<geometricObject *> geometricObjects;
};

#endif // MENU_H