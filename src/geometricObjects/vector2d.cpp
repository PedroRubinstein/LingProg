#include <iostream> 
#include <cmath>    
#include <stdexcept>
#include <string>
#include "vector2d.h"

using namespace std;
typedef long double ld;

Vector2D::Vector2D() : m_x(0.0), m_y(0.0) {}
Vector2D::Vector2D(ld x, ld y) : m_x(x), m_y(y) {}

ld Vector2D::getX() const { return m_x; }
ld Vector2D::getY() const { return m_y; }
void Vector2D::setX(ld x) { m_x = x; }
void Vector2D::setY(ld y) { m_y = y; }

geometricObject::Type Vector2D::type() const {
    return geometricObject::Type::Vector2D;
}

Vector2D Vector2D::operator+(const Vector2D& other) const {
    return Vector2D(m_x + other.m_x, m_y + other.m_y);
}

Vector2D Vector2D::operator-(const Vector2D& other) const {
    return Vector2D(m_x - other.m_x, m_y - other.m_y);
}

ld Vector2D::operator*(const Vector2D& other) const{
    return m_x * other.m_x + m_y * other.m_y;
}

ld Vector2D::operator^(const Vector2D& other) const{
    return m_x * other.m_y - m_y * other.m_x;
}

Vector2D& Vector2D::operator+=(const Vector2D& other) {
    m_x += other.m_x;
    m_y += other.m_y;
    return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& other) {
    m_x -= other.m_x;
    m_y -= other.m_y;
    return *this;
}

std::ostream& operator<<(std::ostream &out, const Vector2D &vector) {
    out << "Vector2D(" << vector.m_x << ", " << vector.m_y << ")";
    return out;
}

ld abs(Vector2D& vec) {
    return sqrt(vec.getX() * vec.getX() + vec.getY() * vec.getY());
}

std::string Vector2D::serialize() const {
    // Format: {"x": 10.5, "y": -5.2}
    return "{\"x\": " + std::to_string(m_x) + ", \"y\": " + std::to_string(m_y) + "}";
}
