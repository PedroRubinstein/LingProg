#include "vector2d.h"
#include <iostream>

Vector2D::Vector2D() : m_x(0.0), m_y(0.0) {}

Vector2D::Vector2D(double x, double y) : m_x(x), m_y(y) {}

double Vector2D::getX() const {
    return m_x;
}

double Vector2D::getY() const {
    return m_y;
}

void Vector2D::setX(double x) {
    m_x = x;
}

void Vector2D::setY(double y) {
    m_y = y;
}

void Vector2D::print() const {
    std::cout << "Vector2D(" << m_x << ", " << m_y << ")" << std::endl;
}

geometricObject::Type Vector2D::type() const {
    return geometricObject::Type::Vector2D;
}
