#include "menu.h"
#include "database.h"
#include <Python.h> // Required for Py_Initialize

int main() {
    // 1. Initialize Database
    if (!DatabaseManager::getInstance().init()) {
        return -1;
    }

    // 2. Initialize Python (Once for the entire application lifecycle)
    Py_Initialize();
    PyRun_SimpleString("import sys, os");
    // Ensure the scripts directory is in the Python path
    // Assumption: Running from project root
    PyRun_SimpleString("sys.path.insert(0, os.path.abspath('scripts'))");

    // 3. Run Application
    Menu menu;
    menu.showMenu();

    // 4. Cleanup Python
    Py_Finalize();

    return 0;
}
