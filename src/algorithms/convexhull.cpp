#include "algorithms/convexhull.h"
#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

Polygon ConvexHull::monotoneChain(const vector<Vector2D>& pts, StepCallback callback) {
    if (pts.size() < 3) return Polygon(pts);
    vector<Vector2D> points = pts;

    // 1. Sort by X, then Y
    std::sort(points.begin(), points.end());

    // Remove duplicates
    auto last = std::unique(points.begin(), points.end(), [](const Vector2D& a, const Vector2D& b){
        return a.getX() == b.getX() && a.getY() == b.getY();
    });
    points.erase(last, points.end());

    if (points.size() < 3) return Polygon(points);

    vector<Vector2D> hull;

    // Helper para chamar o callback de forma segura
    auto notify = [&](const Vector2D& p) {
        if (callback) callback(hull, p);
    };

    // 2. Build Lower Hull
    for (const auto& p : points) {
        notify(p); // Visualiza: Considerando o ponto P

        while (hull.size() >= 2 && Vector2D::crossProduct(hull[hull.size()-2], hull.back(), p) <= 0) {
            hull.pop_back();
            notify(p); // Visualiza: Ponto removido do fecho devido a P
        }
        hull.push_back(p);
        notify(p); // Visualiza: Ponto P adicionado ao fecho
    }

    // 3. Build Upper Hull
    size_t lowerSize = hull.size();
    for (int i = points.size() - 2; i >= 0; --i) {
        const auto& p = points[i];
        notify(p); // Visualiza: Considerando P (caminho inverso)

        while (hull.size() > lowerSize && Vector2D::crossProduct(hull[hull.size()-2], hull.back(), points[i]) <= 0) {
            hull.pop_back();
            notify(p); // Visualiza: Remoção
        }
        hull.push_back(points[i]);
        notify(p); // Visualiza: Adição
    }

    if (!hull.empty()) hull.pop_back();

    return Polygon(hull);
}
