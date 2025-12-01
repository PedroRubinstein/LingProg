#ifndef CIRCUMFERENCE_H
#define CIRCUMFERENCE_H

#include <ostream>
#include "geometricobject.h"
#include "vector2d.h"

typedef long double ld;

/**
 * @brief Representa uma circunferência (círculo).
 */
class Circumference : public geometricObject {
public:
    Circumference();
    
    /**
     * @brief Construtor completo.
     * @param center O ponto central.
     * @param radius O raio da circunferência.
     */
    Circumference(const Vector2D &center, double radius);

    void setRadius(double radius);
    void setCenter(const Vector2D &center);

    ld getRadius() const;
    const Vector2D& getCenter() const;

    geometricObject::Type type() const override;

    friend std::ostream& operator<<(std::ostream& out, const Circumference& c);

    std::string serialize() const override;

private:
    Vector2D m_center;
    double m_radius{0.0};
};

#endif
