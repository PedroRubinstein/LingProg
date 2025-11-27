#ifndef GEOMETRICOBJECT_H
#define GEOMETRICOBJECT_H

#include <string>
#include <iostream>

/**
 * @brief Classe base abstrata para todos os objetos geométricos.
 * * Define a interface comum para identificação, tipagem e serialização.
 */
class geometricObject {
public:
    /**
     * @brief Enumeração dos tipos de objetos suportados pelo sistema.
     */
    enum class Type {
        Unknown,
        Point,
        Line,
        Vector2D,
        Polygon,
        Circumference
    };

    geometricObject() = default;
    virtual ~geometricObject() = default;

    /**
     * @brief Define o ID do objeto (geralmente sincronizado com o DB).
     * @param newId O novo ID.
     */
    void setId(int newId) { id = newId; }

    /**
     * @brief Obtém o ID atual do objeto.
     * @return int ID do objeto.
     */
    int getId() const { return id; }

    /**
     * @brief Retorna o tipo concreto do objeto.
     * @return Type Enum correspondente (ex: Type::Polygon).
     */
    virtual Type type() const = 0;

    /**
     * @brief Serializa o estado do objeto para uma string JSON.
     * @return std::string Representação JSON do objeto.
     */
    virtual std::string serialize() const = 0;

private:
    int id = -1;
};

#endif
