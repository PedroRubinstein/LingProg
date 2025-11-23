#include <iostream> 
#include "polygon.h"

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
