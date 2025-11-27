#include "algorithms/convexhull.h"
#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

Polygon ConvexHull::monotoneChain(const vector<Vector2D>& pts) {
    if (pts.size() < 3) return Polygon(pts);
    vector<Vector2D> points = pts;

    // 1. Sort by X, then Y
    std::sort(points.begin(), points.end());

    auto last = std::unique(points.begin(), points.end(), [](const Vector2D& a, const Vector2D& b){
        return a.getX() == b.getX() && a.getY() == b.getY();
    });
    points.erase(last, points.end());

    if (points.size() < 3) return Polygon(points);

    vector<Vector2D> hull;

    // 2. Build Lower Hull
    for (const auto& p : points) {
        while (hull.size() >= 2 && Vector2D::crossProduct(hull[hull.size()-2], hull.back(), p) <= 0) {
            hull.pop_back();
        }
        hull.push_back(p);
    }

    // 3. Build Upper Hull
    size_t lowerSize = hull.size();
    for (int i = points.size() - 2; i >= 0; --i) {
        while (hull.size() > lowerSize && Vector2D::crossProduct(hull[hull.size()-2], hull.back(), points[i]) <= 0) {
            hull.pop_back();
        }
        hull.push_back(points[i]);
    }

    if (!hull.empty()) hull.pop_back();

    return Polygon(hull);
}
