#include "point.h"
#include <iostream>
#include <cmath>

Point::Point() : m_x(0.0), m_y(0.0) {}

Point::Point(double x, double y)
    : m_x(x), m_y(y) {}

double Point::getX() const { return m_x; }
double Point::getY() const { return m_y; }

double Point::distanceTo(const Point &other) const {
    const double dx = m_x - other.m_x;
    const double dy = m_y - other.m_y;
    return std::sqrt(dx*dx + dy*dy);
}

void Point::print() const {
    std::cout << "Ponto(" << m_x << ", " << m_y << ")";
}

geometricObject::Type Point::type() const { return geometricObject::Type::Point; }
