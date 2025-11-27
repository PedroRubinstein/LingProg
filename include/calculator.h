#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>
#include "geometricObjects/line.h"
#include "geometricObjects/polygon.h"
#include "geometricObjects/vector2d.h"

/**
 * @brief Utilitário para cálculos geométricos diversos.
 */
class Calculator {
public:
    /**
     * @brief Determina a posição relativa de um ponto em relação a uma reta orientada.
     * * Utiliza o produto vetorial para verificar a orientação.
     * * @param line A reta orientada (segmento AB) de referência.
     * @param point O ponto a ser testado.
     * @return std::string "LEFT" se à esquerda, "RIGHT" se à direita, ou "TOUCH" se colinear.
     */
    static std::string pointLocationTest(const Line& line, const Vector2D& point);

    /**
     * @brief Verifica se dois segmentos de reta se interceptam.
     * * Considera interseções próprias (cruzamento) e impróprias (extremidade na reta).
     * * @param seg1 O primeiro segmento de reta.
     * @param seg2 O segundo segmento de reta.
     * @return true Se houver interseção.
     * @return false Caso contrário.
     */
    static bool checkIntersection(const Line& seg1, const Line& seg2);

    /**
     * @brief Calcula a área de um polígono qualquer.
     * * Utiliza a fórmula Shoelace (Fórmula do Laço). O resultado é sempre positivo.
     * * @warning O polígono não deve ser auto-intersectante (complexo).
     * @param poly O polígono de entrada.
     * @return double A área absoluta do polígono.
     */
    static double polygonArea(const Polygon& poly);
};

#endif
