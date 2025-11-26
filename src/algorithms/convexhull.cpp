#include "algorithms/convexhull.h"
#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

Polygon ConvexHull::grahamScan(const vector<Vector2D>& pts) {
    if (pts.size() < 3) return Polygon(pts);
    vector<Vector2D> points = pts;

    // 1. Find the pivot (bottom-most, then left-most)
    int pivotIdx = 0;
    for (size_t i = 1; i < points.size(); ++i) {
        if (points[i].getY() < points[pivotIdx].getY() || 
           (points[i].getY() == points[pivotIdx].getY() && points[i].getX() < points[pivotIdx].getX())) {
            pivotIdx = i;
        }
    }
    // Move pivot to the front
    std::swap(points[0], points[pivotIdx]);
    Vector2D p0 = points[0];

    // 2. Sort by polar angle with respect to pivot
    std::sort(points.begin() + 1, points.end(), [&](const Vector2D& a, const Vector2D& b) {
        // UPDATED: Using Vector2D::crossProduct and distSq
        long double cp = Vector2D::crossProduct(p0, a, b);
        if (std::abs(cp) < 1e-9) {
            return Vector2D::distSq(p0, a) < Vector2D::distSq(p0, b);
        }
        return cp > 0;
    });

    // 3. Build Hull
    vector<Vector2D> hull;
    hull.push_back(points[0]);
    
    for (size_t i = 1; i < points.size(); ++i) {
        // UPDATED: Using Vector2D::crossProduct
        while (hull.size() >= 2 && Vector2D::crossProduct(hull[hull.size()-2], hull.back(), points[i]) <= 0) {
            hull.pop_back();
        }
        hull.push_back(points[i]);
    }

    return Polygon(hull);
}

Polygon ConvexHull::monotoneChain(const vector<Vector2D>& pts) {
    if (pts.size() < 3) return Polygon(pts);
    vector<Vector2D> points = pts;

    // 1. Sort by X, then Y
    std::sort(points.begin(), points.end(), [](const Vector2D& a, const Vector2D& b) {
        return a.getX() < b.getX() || (a.getX() == b.getX() && a.getY() < b.getY());
    });

    auto last = std::unique(points.begin(), points.end(), [](const Vector2D& a, const Vector2D& b){
        return a.getX() == b.getX() && a.getY() == b.getY();
    });
    points.erase(last, points.end());

    if (points.size() < 3) return Polygon(points);

    vector<Vector2D> hull;

    // 2. Build Lower Hull
    for (const auto& p : points) {
        // UPDATED: Using Vector2D::crossProduct
        while (hull.size() >= 2 && Vector2D::crossProduct(hull[hull.size()-2], hull.back(), p) <= 0) {
            hull.pop_back();
        }
        hull.push_back(p);
    }

    // 3. Build Upper Hull
    size_t lowerSize = hull.size();
    for (int i = points.size() - 2; i >= 0; --i) {
        // UPDATED: Using Vector2D::crossProduct
        while (hull.size() > lowerSize && Vector2D::crossProduct(hull[hull.size()-2], hull.back(), points[i]) <= 0) {
            hull.pop_back();
        }
        hull.push_back(points[i]);
    }

    if (!hull.empty()) hull.pop_back();

    return Polygon(hull);
}
