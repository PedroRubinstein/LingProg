#include <iostream> 
#include "line.h"

Line::Line() : m_p1(0.0, 0.0), m_p2(1.0, 0.0) {}

Line::Line(const Vector2D &p1, const Vector2D &p2) : m_p1(p1), m_p2(p2) {}

const Vector2D& Line::getP1() const { return m_p1; }
const Vector2D& Line::getP2() const { return m_p2; }

void Line::setP1(const Vector2D &p) { m_p1 = p; }
void Line::setP2(const Vector2D &p) { m_p2 = p; }

geometricObject::Type Line::type() const {
    return geometricObject::Type::Line;
}

std::ostream& operator<<(std::ostream& out, const Line& l) {
    return out << "Reta(P1: " << l.m_p1 << ", P2: " << l.m_p2 << ")";
}

std::string Line::serialize() const {
    // Format: {"p1": {...}, "p2": {...}}
    return "{\"p1\": " + m_p1.serialize() + ", \"p2\": " + m_p2.serialize() + "}";
}
