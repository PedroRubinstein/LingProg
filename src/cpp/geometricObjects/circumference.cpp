#include "circumference.h"
#include <iostream>

Circumference::Circumference() = default;

Circumference::Circumference(const Point &center, double radius)
    : m_center(center), m_radius(radius) {}

void Circumference::setRadius(double radius) {
    m_radius = radius;
}

void Circumference::setCenter(const Point &center) {
    m_center = center;
}

void Circumference::print() const {
    std::cout << "Circunferência(Centro: ";
    m_center.print();
    std::cout << ", Raio: " << m_radius << ")";
}

const Point& Circumference::getCenter() const { return m_center; }
double Circumference::getRadius() const { return m_radius; }

geometricObject::Type Circumference::type() const { return Type::Circumference; }
