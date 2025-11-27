#ifndef MINCIRCLE_H
#define MINCIRCLE_H

#include <vector>
#include "geometricObjects/vector2d.h"
#include "geometricObjects/circumference.h"

/**
 * @brief Implementação iterativa do Algoritmo de Welzl para Círculo Mínimo.
 * * Adaptado para utilizar a infraestrutura existente (Vector2D, Circumference).
 * * Complexidade esperada: O(N).
 */
class MinCircle {
public:
    /**
     * @brief Calcula o menor círculo que contém todos os pontos fornecidos.
     * @param points Lista de pontos de entrada.
     * @return Circumference O círculo mínimo calculado.
     */
    static Circumference find(const std::vector<Vector2D>& points);

private:
    /**
     * @brief Calcula o circuncentro (centro do círculo que passa por 3 pontos).
     * * Baseado na lógica de interseção de mediatrizes usando produto vetorial.
     */
    static Vector2D getCircumcenter(Vector2D p, Vector2D q, Vector2D r);
    
    /**
     * @brief Verifica se um ponto está dentro (ou na borda) da circunferência.
     */
    static bool isInside(const Circumference& c, const Vector2D& p);
};

#endif
