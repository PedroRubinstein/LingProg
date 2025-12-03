#ifndef MINCIRCLE_H
#define MINCIRCLE_H

#include <vector>
#include <functional> 
#include "geometricObjects/vector2d.h"
#include "geometricObjects/circumference.h"

class MinCircle {
public:
    // Callback atualizado: recebe (Círculo, TodosPontos, PontosDeTeste)
    using StepCallback = std::function<void(const Circumference&, const std::vector<Vector2D>&, const std::vector<Vector2D>&)>;

    /**
     * @brief Calcula o menor círculo que contém todos os pontos fornecidos.
     */
    static Circumference find(const std::vector<Vector2D>& points, StepCallback callback = nullptr);

private:
    static Vector2D getCircumcenter(Vector2D p, Vector2D q, Vector2D r);
    static bool isInside(const Circumference& c, const Vector2D& p);
};

#endif
