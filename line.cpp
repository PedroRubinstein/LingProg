#include "line.h"
#include <iostream>

Line::Line() : m_p1(0.0, 0.0), m_p2(1.0, 0.0) {}

Line::Line(const Point &p1, const Point &p2) : m_p1(p1), m_p2(p2) {}

const Point& Line::getP1() const { return m_p1; }
const Point& Line::getP2() const { return m_p2; }

void Line::setP1(const Point &p) { m_p1 = p; }
void Line::setP2(const Point &p) { m_p2 = p; }

void Line::print() const {
    std::cout << "Reta(P1: ";
    m_p1.print();
    std::cout << ", P2: ";
    m_p2.print();
    std::cout << ")";
}

geometricObject::Type Line::type() const {
    return geometricObject::Type::Line;
}
