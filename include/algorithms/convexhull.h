#ifndef CONVEXHULL_H
#define CONVEXHULL_H

#include <vector>
#include "geometricObjects/vector2d.h"
#include "geometricObjects/polygon.h"

class ConvexHull {
public:
    // Computes the Convex Hull using the Graham Scan algorithm
    static Polygon grahamScan(const std::vector<Vector2D>& points);

    // Computes the Convex Hull using the Monotone Chain algorithm (Andrew's Algorithm)
    static Polygon monotoneChain(const std::vector<Vector2D>& points);

private:
    // REMOVED: crossProduct and distSq.
    // Now using Vector2D::static_methods
};

#endif
