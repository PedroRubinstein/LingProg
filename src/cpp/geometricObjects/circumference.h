#ifndef CIRCUMFERENCE_H
#define CIRCUMFERENCE_H

#include "geometricobject.h"
#include "point.h"
#include <string>

class Circumference : public geometricObject {
public:
    Circumference();
    Circumference(const Point &center, double radius);

    void setRadius(double radius);
    void setCenter(const Point &center);

    double getRadius() const;
    const Point& getCenter() const;

    Type type() const;
    void print() const;

private:
    Point m_center;
    double m_radius{0.0};
};

#endif
