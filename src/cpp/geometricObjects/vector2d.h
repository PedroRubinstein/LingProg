#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>
#include "geometricobject.h"

using namespace std;

class Vector2D : public geometricObject {
public:
    Vector2D();
    Vector2D(double x, double y);

    double getX() const;
    double getY() const;
    void setX(double x);
    void setY(double y);

    friend ostream& operator<<(ostream &out, const Vector2D &vector);

    // Overrides
    geometricObject::Type type() const;

private:
    double m_x;
    double m_y;
};

#endif // VECTOR2D_H
