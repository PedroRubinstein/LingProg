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
    // REMOVED: Private helpers crossProduct, onSegment, ccw 
    // Now using Vector2D::static_methods
};

#endif
