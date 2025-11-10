
#ifndef POINT_H
#define POINT_H

#include "geometricobject.h"
#include <string>

class Point : public geometricObject {
public:
    Point();
    Point(double x, double y);

    double getX() const;
    double getY() const;

    double distanceTo(const Point &other) const;

    // Overrides
    void print() const;
    geometricObject::Type type() const;

private:
    double m_x{0.0};
    double m_y{0.0};
};

#endif
