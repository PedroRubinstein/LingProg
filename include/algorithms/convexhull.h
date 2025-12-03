#ifndef CONVEXHULL_H
#define CONVEXHULL_H

#include <vector>
#include <functional> // [Adicionado] Necessário para std::function
#include "geometricObjects/vector2d.h"
#include "geometricObjects/polygon.h"

/**
 * @brief Classe estática que fornece algoritmos para cálculo do Fecho Convexo.
 */
class ConvexHull {
public:
    // [Adicionado] Callback: recebe o fecho parcial atual e o ponto sendo processado
    using StepCallback = std::function<void(const std::vector<Vector2D>& currentHull, const Vector2D& currentPoint)>;

    /**
     * @brief Calcula o Fecho Convexo utilizando o algoritmo Monotone Chain.
     * @param points O conjunto de pontos de entrada.
     * @param callback Função opcional para visualização passo a passo.
     * @return Polygon O polígono resultante.
     */
    static Polygon monotoneChain(const std::vector<Vector2D>& points, StepCallback callback = nullptr);
};

#endif
