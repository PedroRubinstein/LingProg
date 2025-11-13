#include "geometricobject.h"

#ifndef VECTOR2D_H
#define VECTOR2D_H

class Vector2D : public geometricObject {
public:
    Vector2D();
    Vector2D(double x, double y);

    double getX() const;
    double getY() const;
    void setX(double x);
    void setY(double y);

    // Overrides
    void print() const;
    geometricObject::Type type() const;

private:
    double m_x;
    double m_y;
};

#endif // VECTOR2D_H
