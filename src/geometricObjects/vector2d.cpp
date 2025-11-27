#include <iostream> 
#include <cmath>    
#include <stdexcept>
#include <string>
#include <nlohmann/json.hpp>

#include "vector2d.h"

using json = nlohmann::json;
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

// --- Static Helpers Implementation ---

ld Vector2D::crossProduct(const Vector2D& a, const Vector2D& b, const Vector2D& c) {
    return (b.m_x - a.m_x) * (c.m_y - a.m_y) - 
           (b.m_y - a.m_y) * (c.m_x - a.m_x);
}

ld Vector2D::distSq(const Vector2D& a, const Vector2D& b) {
    ld dx = a.m_x - b.m_x;
    ld dy = a.m_y - b.m_y;
    return dx*dx + dy*dy;
}

bool Vector2D::ccw(const Vector2D& a, const Vector2D& b, const Vector2D& c) {
    return crossProduct(a, b, c) > 0;
}

// -------------------------------------

Vector2D Vector2D::operator+(const Vector2D& other) const {
    return Vector2D(m_x + other.m_x, m_y + other.m_y);
}

Vector2D Vector2D::operator-(const Vector2D& other) const {
    return Vector2D(m_x - other.m_x, m_y - other.m_y);
}

bool Vector2D::operator<(const Vector2D& other) const {
    if (m_x != other.m_x) {
        return m_x < other.m_x;
    }
    return m_y < other.m_y;
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

ld abs(const Vector2D& vec) {
    return sqrt(vec.getX() * vec.getX() + vec.getY() * vec.getY());
}

std::string Vector2D::serialize() const {
    json j;
    j["x"] = m_x;
    j["y"] = m_y;

    return j.dump();
}

void to_json(json& j, const Vector2D& v) {
    j = json{{"x", v.getX()}, {"y", v.getY()}};
}
