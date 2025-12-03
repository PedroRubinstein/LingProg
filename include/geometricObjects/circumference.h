#ifndef CIRCUMFERENCE_H
#define CIRCUMFERENCE_H

#include <ostream>
#include <istream> // Necessário
#include "geometricobject.h"
#include "vector2d.h"

// Garantindo que ld é long double
typedef long double ld;

class Circumference : public geometricObject {
public:
    Circumference();
    
    // [MODIFICADO] double -> ld
    Circumference(const Vector2D &center, ld radius);

    // [MODIFICADO] double -> ld
    void setRadius(ld radius);
    void setCenter(const Vector2D &center);

    ld getRadius() const;
    const Vector2D& getCenter() const;

    geometricObject::Type type() const override;

    friend std::ostream& operator<<(std::ostream& out, const Circumference& c);
    // [NOVO]
    friend std::istream& operator>>(std::istream& in, Circumference& c);

    std::string serialize() const override;

private:
    Vector2D m_center;
    ld m_radius{0.0}; // [MODIFICADO] double -> ld
};

#endif
