#include "database.h"
#include <iostream>

// Implementação do Singleton
DatabaseManager& DatabaseManager::getInstance() {
    static DatabaseManager instance;
    return instance;
}

bool DatabaseManager::init(const std::string& dbPath) {
    // 1. Tentar abrir a conexão com o arquivo
    int rc = sqlite3_open(dbPath.c_str(), &db);
    
    if (rc) {
        std::cerr << "[DB] Erro ao abrir banco de dados: " << sqlite3_errmsg(db) << std::endl;
        return false;
    } else {
        std::cout << "[DB] Conectado ao banco de dados: " << dbPath << std::endl;
    }

    // 2. SQL para criar a tabela se ela não existir
    // Schema: ID (Auto), Type (Inteiro do enum), Data (String serializada), Created_At
    std::string sql = "CREATE TABLE IF NOT EXISTS objects ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "type INTEGER NOT NULL,"
                      "data TEXT NOT NULL,"
                      "created_at DATETIME DEFAULT CURRENT_TIMESTAMP);";

    char* errMsg = nullptr;
    rc = sqlite3_exec(db, sql.c_str(), nullptr, 0, &errMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "[DB] Erro SQL: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    } else {
        std::cout << "[DB] Tabela 'objects' verificada/criada com sucesso." << std::endl;
    }

    return true;
}

sqlite3* DatabaseManager::getDB() const {
    return db;
}

DatabaseManager::~DatabaseManager() {
    if (db) {
        sqlite3_close(db);
        std::cout << "[DB] Conexão fechada." << std::endl;
    }
}
