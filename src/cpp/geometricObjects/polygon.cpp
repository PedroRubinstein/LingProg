#include "polygon.h"
#include <iostream>

Polygon::Polygon(const std::vector<Point> &pts)
    : m_vertices(pts) {}

void Polygon::addVertex(const Point &p) {
    m_vertices.push_back(p);
}

void Polygon::setVertices(const std::vector<Point> &pts) {
    m_vertices = pts;
}

const std::vector<Point>& Polygon::getVertices() const {
    return m_vertices;
}

void Polygon::print() const {
    std::cout << "Polígono(Vértices: ";
    for (const Point &v : m_vertices) {
        v.print();
        std::cout << " ";
    }
    std::cout << ")";
}

geometricObject::Type Polygon::type() const { return geometricObject::Type::Polygon; }
