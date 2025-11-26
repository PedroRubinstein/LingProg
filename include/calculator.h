#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>
#include "geometricObjects/line.h"
#include "geometricObjects/polygon.h"
#include "geometricObjects/vector2d.h"

class Calculator {
public:
    // Determines if 'point' is LEFT, RIGHT or TOUCHing the directed line 'line'
    static std::string pointLocationTest(const Line& line, const Vector2D& point);

    // Checks if two line segments intersect
    static bool checkIntersection(const Line& seg1, const Line& seg2);

    // Calculates the signed area of a polygon (returns absolute value)
    static double polygonArea(const Polygon& poly);

private:
    // Helper: Cross product of vectors (b-a) and (c-a)
    static long double crossProduct(const Vector2D& a, const Vector2D& b, const Vector2D& c);
    
    // Helper: Checks if point p is on segment seg (assuming collinearity is verified)
    static bool onSegment(const Vector2D& p, const Line& seg);

    // Helper: Returns true if the turn a->b->c is strictly counter-clockwise
    static bool ccw(const Vector2D& a, const Vector2D& b, const Vector2D& c);
};

#endif
