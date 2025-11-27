#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include <ostream>   
#include "geometricobject.h"
#include "vector2d.h"

/**
 * @brief Representa um polígono arbitrário definido por uma lista de vértices.
 */
class Polygon : public geometricObject {
public:
    Polygon() = default;
    
    /**
     * @brief Constrói um polígono a partir de um vetor de pontos.
     * @param pts Lista ordenada de vértices.
     */
    Polygon(const std::vector<Vector2D> &pts);

    /**
     * @brief Adiciona um vértice ao final da lista do polígono.
     * @param p O ponto a adicionar.
     */
    void addVertex(const Vector2D &p);
    
    /**
     * @brief Substitui todos os vértices do polígono.
     * @param pts Nova lista de vértices.
     */
    void setVertices(const std::vector<Vector2D> &pts);
    
    /**
     * @brief Retorna a lista de vértices (leitura).
     * @return const std::vector<Vector2D>& Referência para os vértices.
     */
    const std::vector<Vector2D>& getVertices() const;

    /**
     * @brief Calcula a área do polígono usando a fórmula Shoelace.
     * @return double Área absoluta.
     */
    double getArea() const;

    /**
     * @brief Permite que um visitante processe esta instância de Polygon.
     * @param visitor O visitante que executará a lógica específica para polígonos.
     */
    void accept(ShapeVisitor& visitor) override;

    geometricObject::Type type() const override;

    friend std::ostream& operator<<(std::ostream& out, const Polygon& p);
    
    /**
     * @brief Serializa o polígono para JSON.
     * Formato: {"vertices": [{"x":..., "y":...}, ...]}
     */
    std::string serialize() const override;

private:
    std::vector<Vector2D> m_vertices;
};

#endif
