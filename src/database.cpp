#include "database.h"
#include <iostream>
#include <nlohmann/json.hpp>

#include "geometricObjects/vector2d.h"
#include "geometricObjects/line.h"
#include "geometricObjects/polygon.h"
#include "geometricObjects/circumference.h"

using json = nlohmann::json;

DatabaseManager& DatabaseManager::getInstance() {
    static DatabaseManager instance;
    return instance;
}

bool DatabaseManager::init(const std::string& dbPath) {
    int rc = sqlite3_open(dbPath.c_str(), &db);
    if (rc) {
        std::cerr << "[DB] Error opening database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    std::string sql = "CREATE TABLE IF NOT EXISTS objects ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "type INTEGER NOT NULL,"
                      "data TEXT NOT NULL,"
                      "created_at DATETIME DEFAULT CURRENT_TIMESTAMP);";

    char* errMsg = nullptr;
    rc = sqlite3_exec(db, sql.c_str(), nullptr, 0, &errMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "[DB] SQL Error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}

int DatabaseManager::insert_object(geometricObject* obj) {
    if (!db || !obj) return -1;

    std::string sql = "INSERT INTO objects (type, data) VALUES (?, ?);";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "[DB] Prepare error: " << sqlite3_errmsg(db) << std::endl;
        return -1;
    }

    sqlite3_bind_int(stmt, 1, static_cast<int>(obj->type()));
    std::string data = obj->serialize();
    sqlite3_bind_text(stmt, 2, data.c_str(), -1, SQLITE_STATIC);

    int id = -1;
    if (sqlite3_step(stmt) == SQLITE_DONE) {
        id = static_cast<int>(sqlite3_last_insert_rowid(db));
        obj->setId(id);
        std::cout << "[DB] Object inserted with ID: " << id << std::endl;
    } else {
        std::cerr << "[DB] Insert error: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
    return id;
}

bool DatabaseManager::delete_object(int id) {
    if (!db) return false;

    std::string sql = "DELETE FROM objects WHERE id = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return false;
    }

    sqlite3_bind_int(stmt, 1, id);

    bool success = false;
    if (sqlite3_step(stmt) == SQLITE_DONE) {
        if (sqlite3_changes(db) > 0) {
            std::cout << "[DB] Object " << id << " deleted." << std::endl;
            success = true;
        } else {
            std::cout << "[DB] ID " << id << " not found." << std::endl;
        }
    }

    sqlite3_finalize(stmt);
    return success;
}

// NEW: Implementation of clear_database
bool DatabaseManager::clear_database() {
    if (!db) return false;
    char* errMsg = nullptr;

    // 1. Delete all records
    int rc = sqlite3_exec(db, "DELETE FROM objects;", nullptr, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "[DB] Error clearing objects: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }

    // 2. Reset Auto-Increment Counter (Optional but good for a "full reset")
    sqlite3_exec(db, "DELETE FROM sqlite_sequence WHERE name='objects';", nullptr, 0, nullptr);
    
    std::cout << "[DB] Database completely reset." << std::endl;
    return true;
}

geometricObject* DatabaseManager::get_object_by_id(int id) {
    if (!db) return nullptr;

    std::string sql = "SELECT type, data FROM objects WHERE id = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return nullptr;
    }

    sqlite3_bind_int(stmt, 1, id);

    geometricObject* obj = nullptr;

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int typeInt = sqlite3_column_int(stmt, 0);
        const unsigned char* dataText = sqlite3_column_text(stmt, 1);
        std::string jsonStr = reinterpret_cast<const char*>(dataText);

        try {
            json j = json::parse(jsonStr);
            auto type = static_cast<geometricObject::Type>(typeInt);

            switch (type) {
                case geometricObject::Type::Vector2D:
                    obj = new Vector2D(j["x"], j["y"]);
                    break;
                case geometricObject::Type::Line:
                    obj = new Line(Vector2D(j["p1"]["x"], j["p1"]["y"]),
                                   Vector2D(j["p2"]["x"], j["p2"]["y"]));
                    break;
                case geometricObject::Type::Circumference:
                    obj = new Circumference(Vector2D(j["center"]["x"], j["center"]["y"]),
                                            j["radius"]);
                    break;
                case geometricObject::Type::Polygon: {
                    std::vector<Vector2D> verts;
                    for (auto& v : j["vertices"]) {
                        verts.emplace_back(v["x"], v["y"]);
                    }
                    obj = new Polygon(verts);
                    break;
                }
                default:
                    std::cerr << "[DB] Unknown object type: " << typeInt << std::endl;
            }
            if (obj) obj->setId(id);
        } catch (json::exception& e) {
            std::cerr << "[DB] JSON Parsing Error for ID " << id << ": " << e.what() << std::endl;
        }
    }

    sqlite3_finalize(stmt);
    return obj;
}

std::vector<int> DatabaseManager::get_all_ids() {
    std::vector<int> ids;
    if (!db) return ids;
    std::string sql = "SELECT id FROM objects ORDER BY id ASC;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            ids.push_back(sqlite3_column_int(stmt, 0));
        }
    }
    sqlite3_finalize(stmt);
    return ids;
}

sqlite3* DatabaseManager::getDB() const { return db; }

DatabaseManager::~DatabaseManager() {
    if (db) {
        sqlite3_close(db);
    }
}
