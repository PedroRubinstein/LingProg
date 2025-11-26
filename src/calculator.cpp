#include "calculator.h"
#include <cmath>
#include <algorithm>
#include <iostream>

using namespace std;

// Calculates (B-A) x (C-A)
long double Calculator::crossProduct(const Vector2D& a, const Vector2D& b, const Vector2D& c) {
    Vector2D ab = b - a;
    Vector2D ac = c - a;
    return ab ^ ac; // Uses the operator^ overload from Vector2D
}

// Reusable CCW function
bool Calculator::ccw(const Vector2D& a, const Vector2D& b, const Vector2D& c) {
    return crossProduct(a, b, c) > 0;
}

std::string Calculator::pointLocationTest(const Line& line, const Vector2D& point) {
    long double cp = crossProduct(line.getP1(), line.getP2(), point);
    
    // Use epsilon for float point comparisons
    const long double EPS = 1e-9;
    
    if (std::abs(cp) < EPS) return "TOUCH";
    if (cp > 0) return "LEFT";
    return "RIGHT";
}

bool Calculator::onSegment(const Vector2D& p, const Line& seg) {
    Vector2D a = seg.getP1() - p;
    Vector2D b = seg.getP2() - p;
    
    const long double EPS = 1e-9;
    
    // (a ^ b) represents the cross product (collinearity check)
    // (a * b) represents the dot product. If <= 0, the vectors point in opposite directions
    return std::abs(a ^ b) < EPS && (a * b) <= EPS;
}

bool Calculator::checkIntersection(const Line& seg1, const Line& seg2) {
    // 1. Check if any endpoint of one segment lies on the other segment
    // This handles collinear overlaps and "T" intersections
    if (onSegment(seg1.getP1(), seg2) || onSegment(seg1.getP2(), seg2) ||
        onSegment(seg2.getP1(), seg1) || onSegment(seg2.getP2(), seg1)) {
        return true;
    }

    Vector2D p1 = seg1.getP1();
    Vector2D p2 = seg1.getP2();
    Vector2D p3 = seg2.getP1();
    Vector2D p4 = seg2.getP2();

    // 2. Check if the segments properly intersect (endpoints on opposite sides)
    // Logic: (CCW(A,B,C) != CCW(A,B,D)) AND (CCW(C,D,A) != CCW(C,D,B))
    return ccw(p1, p2, p3) != ccw(p1, p2, p4) &&
           ccw(p3, p4, p1) != ccw(p3, p4, p2);
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
