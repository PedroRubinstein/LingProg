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
    
    int insert_object(geometricObject* obj);
    bool delete_object(int id);
    
    // NEW: Clears all data from the database
    bool clear_database();

    geometricObject* get_object_by_id(int id);
    std::vector<int> get_all_ids();

    ~DatabaseManager();

private:
    DatabaseManager() = default;
    sqlite3* db = nullptr;
};

#endif // DATABASE_H
