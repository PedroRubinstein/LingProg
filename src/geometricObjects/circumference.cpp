#include <iostream>
#include <istream> // Necessário
#include <nlohmann/json.hpp>
#include "circumference.h"

using json = nlohmann::json;

Circumference::Circumference() = default;

// [MODIFICADO]
Circumference::Circumference(const Vector2D &center, ld radius)
    : m_center(center), m_radius(radius) {}

// [MODIFICADO]
void Circumference::setRadius(ld radius) {
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

// [NOVO]
std::istream& operator>>(std::istream& in, Circumference& c) {
    // Lê o centro (Vector2D) e depois o raio (ld)
    in >> c.m_center >> c.m_radius;
    return in;
}

std::string Circumference::serialize() const {
    json j;
    
    // Serializing mixed types (Object + Double)
    j["center"] = { {"x", m_center.getX()}, {"y", m_center.getY()} };
    j["radius"] = m_radius;

    return j.dump();
}
