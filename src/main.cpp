#include "menu.h"
#include "database.h" // <--- Inclua isso

int main() {
    // Inicializa o banco de dados antes de tudo
    if (!DatabaseManager::getInstance().init()) {
        return -1; // Encerra se falhar
    }

    Menu menu;
    menu.showMenu();
    return 0;
}
