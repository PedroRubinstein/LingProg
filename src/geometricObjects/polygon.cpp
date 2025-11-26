#include <iostream> 
#include <nlohmann/json.hpp>

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
