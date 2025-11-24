#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>
#include <iostream>

class DatabaseManager {
public:
    // Método estático para acessar a única instância da classe (Singleton)
    static DatabaseManager& getInstance();

    // Deletar construtores de cópia para evitar duplicidade
    DatabaseManager(const DatabaseManager&) = delete;
    void operator=(const DatabaseManager&) = delete;

    // Inicializa o banco de dados e cria as tabelas se não existirem
    bool init(const std::string& dbPath = "cartesia.db");

    // Retorna a conexão crua com o SQLite (útil para queries futuras)
    sqlite3* getDB() const;

    // Destrutor fecha a conexão
    ~DatabaseManager();

private:
    // Construtor privado para impedir criação direta
    DatabaseManager() = default;
    
    sqlite3* db = nullptr;
};

#endif // DATABASE_H
