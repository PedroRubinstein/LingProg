#include <iostream> 
#include <nlohmann/json.hpp>
#include <cmath> 
#include "polygon.h"

using json = nlohmann::json;

Polygon::Polygon(const std::vector<Vector2D> &pts)
    : m_vertices(pts) {}

void Polygon::addVertex(const Vector2D &p) {
    m_vertices.push_back(p);
}

void Polygon::setVertices(const std::vector<Vector2D> &pts) {
    m_vertices = pts;
}

const std::vector<Vector2D>& Polygon::getVertices() const {
    return m_vertices;
}

double Polygon::getArea() const {
    if (m_vertices.size() < 3) return 0.0;

    long double area = 0.0;
    for (size_t i = 0; i < m_vertices.size(); ++i) {
        // Shoelace Formula usando operador ^ (cross product) do Vector2D
        const Vector2D& current = m_vertices[i];
        const Vector2D& next = m_vertices[(i + 1) % m_vertices.size()];
        area += (current ^ next);
    }

    return 0.5 * std::abs(area);
}

geometricObject::Type Polygon::type() const { 
    return geometricObject::Type::Polygon; 
}

std::ostream& operator<<(std::ostream& out, const Polygon& p) {
    out << "Polígono(Vértices: ";
    for (const Vector2D &v : p.m_vertices) {
        out << v << '\n';
    }
    out << ")";
    return out;
}

std::string Polygon::serialize() const {
    std::string json = "{\"vertices\": [";
    for (size_t i = 0; i < m_vertices.size(); ++i) {
        json += m_vertices[i].serialize();
        if (i < m_vertices.size() - 1) {
            json += ", ";
        }
    }
    json += "]}";
    return json;
}

void Polygon::accept(ShapeVisitor& visitor) {
    visitor.visit(*this); }
