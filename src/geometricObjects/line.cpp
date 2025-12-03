#include <cmath>
#include <iostream> 
#include <nlohmann/json.hpp>

#include "line.h"

using json = nlohmann::json;

Line::Line() : m_p1(0.0, 0.0), m_p2(1.0, 0.0) {}

Line::Line(const Vector2D &p1, const Vector2D &p2) : m_p1(p1), m_p2(p2) {}

const Vector2D& Line::getP1() const { return m_p1; }
const Vector2D& Line::getP2() const { return m_p2; }

void Line::setP1(const Vector2D &p) { m_p1 = p; }
void Line::setP2(const Vector2D &p) { m_p2 = p; }

bool Line::contains(const Vector2D& p) const {
    // Vetores do ponto p até os extremos do segmento
    Vector2D va = m_p1 - p;
    Vector2D vb = m_p2 - p;
    
    const long double EPS = 1e-9;
    
    // (va ^ vb) verifica colinearidade (área do triângulo é zero)
    // (va * vb) <= 0 verifica se p está entre p1 e p2 (vetores opostos)
    return std::abs(va ^ vb) < EPS && (va * vb) <= EPS;
}

std::string Line::pointLocation(const Vector2D& point) const {
    long double cp = Vector2D::crossProduct(m_p1, m_p2, point);
    const long double EPS = 1e-9;
    
    if (std::abs(cp) < EPS) return "COLINEAR";
    if (cp > 0) return "ESQUERDA";
    return "DIREITA";
}

bool Line::intersects(const Line& other) const {
    const Vector2D& p1 = m_p1;
    const Vector2D& p2 = m_p2;
    const Vector2D& p3 = other.getP1();
    const Vector2D& p4 = other.getP2();

    // Verificação de casos limite (ponto sobre o segmento) usando o novo método
    if (other.contains(p1) || other.contains(p2) ||
        this->contains(p3) || this->contains(p4)) {
        return true;
    }

    // Verificação de interseção própria (lados opostos)
    return Vector2D::ccw(p1, p2, p3) != Vector2D::ccw(p1, p2, p4) &&
           Vector2D::ccw(p3, p4, p1) != Vector2D::ccw(p3, p4, p2);
}

geometricObject::Type Line::type() const {
    return geometricObject::Type::Line;
}

std::ostream& operator<<(std::ostream& out, const Line& l) {
    return out << "Segmento(P1: " << l.m_p1 << ", P2: " << l.m_p2 << ")";
}

std::istream& operator>>(std::istream& in, Line& l) {
    // Utiliza o operator>> do Vector2D duas vezes
    in >> l.m_p1 >> l.m_p2;
    return in;
}

std::string Line::serialize() const {
    json j;
    
    // We can construct the nested objects manually
    j["p1"] = { {"x", m_p1.getX()}, {"y", m_p1.getY()} };
    j["p2"] = { {"x", m_p2.getX()}, {"y", m_p2.getY()} };

    return j.dump();
}

