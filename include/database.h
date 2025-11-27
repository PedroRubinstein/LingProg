#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>
#include <vector>
#include <iostream>
#include "geometricObjects/geometricobject.h"

/**
 * @brief Gerencia a conexão e persistência de dados com SQLite.
 * * Implementa o padrão Singleton para garantir uma única conexão ativa.
 */
class DatabaseManager {
public:
    /**
     * @brief Obtém a instância única do DatabaseManager.
     * @return DatabaseManager& Referência para a instância singleton.
     */
    static DatabaseManager& getInstance();

    // Remove construtores de cópia para garantir unicidade
    DatabaseManager(const DatabaseManager&) = delete;
    void operator=(const DatabaseManager&) = delete;

    /**
     * @brief Inicializa a conexão com o banco de dados e cria tabelas se necessário.
     * @param dbPath Caminho do arquivo .db (padrão: "cartesia.db").
     * @return true Se inicializado com sucesso.
     * @return false Se houve erro ao abrir ou configurar o banco.
     */
    bool init(const std::string& dbPath = "cartesia.db");

    /**
     * @brief Retorna o ponteiro bruto da conexão SQLite.
     * @return sqlite3* Ponteiro para a struct sqlite3.
     */
    sqlite3* getDB() const;

    /**
     * @brief Insere um objeto geométrico no banco de dados.
     * * O objeto é serializado em JSON antes de ser salvo.
     * * @param obj Ponteiro para o objeto a ser salvo. O ID do objeto será atualizado após a inserção.
     * @return int O ID gerado pelo banco, ou -1 em caso de erro.
     */
    int insert_object(geometricObject* obj);

    /**
     * @brief Remove um objeto do banco de dados pelo ID.
     * @param id O identificador único do objeto.
     * @return true Se o objeto foi deletado.
     * @return false Se o erro ocorreu ou ID não existe.
     */
    bool delete_object(int id);
    
    /**
     * @brief Apaga TODOS os registros do banco de dados.
     * * Executa um 'DELETE FROM objects' e reseta a contagem de IDs.
     * @return true Se a limpeza foi bem-sucedida.
     */
    bool clear_database();

    /**
     * @brief Recupera e reconstrói um objeto do banco pelo ID.
     * * @param id O identificador do objeto.
     * @return geometricObject* Ponteiro para o objeto instanciado (caller deve deletar), ou nullptr se não encontrado.
     */
    geometricObject* get_object_by_id(int id);

    /**
     * @brief Lista todos os IDs presentes na tabela de objetos.
     * @return std::vector<int> Lista de IDs ordenados.
     */
    std::vector<int> get_all_ids();

    ~DatabaseManager();

private:
    DatabaseManager() = default;
    sqlite3* db = nullptr;
};

#endif // DATABASE_H
