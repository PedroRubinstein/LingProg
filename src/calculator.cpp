#include "calculator.h"
#include <cmath>
#include <algorithm>
#include <iostream>

using namespace std;

std::string Calculator::pointLocationTest(const Line& line, const Vector2D& point) {
    // UPDATED: Using Vector2D::crossProduct
    long double cp = Vector2D::crossProduct(line.getP1(), line.getP2(), point);
    
    const long double EPS = 1e-9;
    
    if (std::abs(cp) < EPS) return "TOUCH";
    if (cp > 0) return "LEFT";
    return "RIGHT";
}

bool Calculator::checkIntersection(const Line& seg1, const Line& seg2) {
    Vector2D p1 = seg1.getP1();
    Vector2D p2 = seg1.getP2();
    Vector2D p3 = seg2.getP1();
    Vector2D p4 = seg2.getP2();

    // 1. Check if any endpoint of one segment lies on the other segment
    // UPDATED: Using Vector2D::onSegment (passing 3 points instead of point+line)
    if (Vector2D::onSegment(p1, p3, p4) || Vector2D::onSegment(p2, p3, p4) ||
        Vector2D::onSegment(p3, p1, p2) || Vector2D::onSegment(p4, p1, p2)) {
        return true;
    }

    // 2. Check if the segments properly intersect (endpoints on opposite sides)
    // UPDATED: Using Vector2D::ccw
    return Vector2D::ccw(p1, p2, p3) != Vector2D::ccw(p1, p2, p4) &&
           Vector2D::ccw(p3, p4, p1) != Vector2D::ccw(p3, p4, p2);
}

double Calculator::polygonArea(const Polygon& poly) {
    const auto& verts = poly.getVertices();
    if (verts.size() < 3) return 0.0;

    long double area = 0.0;
    for (size_t i = 0; i < verts.size(); ++i) {
        // Shoelace Formula
        const Vector2D& current = verts[i];
        const Vector2D& next = verts[(i + 1) % verts.size()];
        area += (current ^ next);
    }

    return 0.5 * std::abs(area);
}
