#include <iostream>
#include "circumference.h"

Circumference::Circumference() = default;

Circumference::Circumference(const Vector2D &center, double radius)
    : m_center(center), m_radius(radius) {}

void Circumference::setRadius(double radius) {
    m_radius = radius;
}

void Circumference::setCenter(const Vector2D &center) {
    m_center = center;
}

const Vector2D& Circumference::getCenter() const { return m_center; }
ld Circumference::getRadius() const { return m_radius; }

geometricObject::Type Circumference::type() const { 
    return Type::Circumference; 
}

std::ostream& operator<<(std::ostream& out, const Circumference& c) {
    return out << "Circunferência(Centro: " << c.m_center << ", Raio: " << c.m_radius << ")";
}

std::string Circumference::serialize() const {
    // Format: {"center": {...}, "radius": 5.0}
    return "{\"center\": " + m_center.serialize() +
           ", \"radius\": " + std::to_string(m_radius) + "}";
}
