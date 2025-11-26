#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>
#include <vector>
#include <iostream>
#include "geometricObjects/geometricobject.h"

class DatabaseManager {
public:
    static DatabaseManager& getInstance();

    DatabaseManager(const DatabaseManager&) = delete;
    void operator=(const DatabaseManager&) = delete;

    bool init(const std::string& dbPath = "cartesia.db");
    sqlite3* getDB() const;

    // --- New Persistence Methods ---
    
    // Saves an object and returns its new ID (or -1 on error)
    int insert_object(geometricObject* obj);

    // Removes an object by ID
    bool delete_object(int id);

    // Loads an object by ID (Factory Method: parses JSON to create the C++ object)
    geometricObject* get_object_by_id(int id);

    // Helper to list IDs for the menu
    std::vector<int> get_all_ids();

    ~DatabaseManager();

private:
    DatabaseManager() = default;
    sqlite3* db = nullptr;
};

#endif // DATABASE_H
