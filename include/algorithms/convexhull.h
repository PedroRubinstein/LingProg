#ifndef CONVEXHULL_H
#define CONVEXHULL_H

#include <vector>
#include "geometricObjects/vector2d.h"
#include "geometricObjects/polygon.h"

/**
 * @brief Classe estática que fornece algoritmos para cálculo do Fecho Convexo.
 */
class ConvexHull {
public:
    /**
     * @brief Calcula o Fecho Convexo utilizando o algoritmo Graham Scan.
     * * Este método ordena os pontos angularmente em relação a um pivô inicial
     * e percorre a lista para construir a envoltória.
     * * @note Complexidade: O(N log N) devido à ordenação.
     * @param points O conjunto de pontos (Vector2D) de entrada.
     * @return Polygon O polígono resultante que representa o fecho convexo.
     */
    static Polygon grahamScan(const std::vector<Vector2D>& points);

    /**
     * @brief Calcula o Fecho Convexo utilizando o algoritmo Monotone Chain (Andrew's Algorithm).
     * * Constrói o fecho superior e inferior separadamente após ordenar os pontos
     * lexicograficamente (por X, depois por Y).
     * * @note Complexidade: O(N log N). Geralmente mais rápido na prática que o Graham Scan.
     * @param points O conjunto de pontos (Vector2D) de entrada.
     * @return Polygon O polígono resultante que representa o fecho convexo.
     */
    static Polygon monotoneChain(const std::vector<Vector2D>& points);
};

#endif
