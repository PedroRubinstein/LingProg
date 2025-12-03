#include "algorithms/mincircle.h"
#include <algorithm>
#include <cmath>
#include <random>
#include <chrono>

using namespace std;

// Constante de tolerância para comparações de ponto flutuante
const double EPS = 1e-12;

Vector2D MinCircle::getCircumcenter(Vector2D p, Vector2D q, Vector2D r) {
    // Lógica adaptada da referência:
    // pt a = p-r, b = q-r;
    Vector2D a = p - r;
    Vector2D b = q - r;
    
    // pt c = pt(dot(a, p+r)/2, dot(b, q+r)/2);
    // Nota: Vector2D::operator* realiza o produto escalar (dot product)
    double cx = (a * (p + r)) / 2.0;
    double cy = (b * (q + r)) / 2.0;
    Vector2D c(cx, cy);

    // return pt(cross(c, pt(a.y, b.y)), cross(pt(a.x, b.x), c)) / cross(a, b);
    // Nota: Vector2D::operator^ realiza o produto vetorial 2D (cross product)
    double denominator = a ^ b;
    
    if (std::abs(denominator) < EPS) return Vector2D(0, 0); // Proteção para pontos colineares

    // cross(c, pt(a.y, b.y))
    double res_x = c ^ Vector2D(a.getY(), b.getY());
    // cross(pt(a.x, b.x), c)
    double res_y = Vector2D(a.getX(), b.getX()) ^ c;

    return Vector2D(res_x, res_y) / denominator;
}

bool MinCircle::isInside(const Circumference& circ, const Vector2D& p) {
    // Utiliza abs(p - center) para calcular a distância, conforme solicitado
    return abs(p - circ.getCenter()) < circ.getRadius() + EPS;
}

// Em src/algorithms/mincircle.cpp

// ... (includes e código anterior)

Circumference MinCircle::find(const vector<Vector2D>& pts, StepCallback callback) {
    if (pts.empty()) return Circumference(Vector2D(0,0), 0);
    if (pts.size() == 1) return Circumference(pts[0], 0);

    vector<Vector2D> v = pts;
    mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());
    shuffle(v.begin(), v.end(), rng);

    Circumference ret(Vector2D(0, 0), 0);

    // Helper atualizado para passar os pontos ativos
    auto notify = [&](const Circumference& c, const vector<Vector2D>& active) {
        if (callback) callback(c, v, active);
    };

    for (size_t i = 0; i < v.size(); i++) {
        if (!isInside(ret, v[i])) {
            ret = Circumference(v[i], 0);
            notify(ret, {v[i]}); // Destaque: Ponto I

            for (size_t j = 0; j < i; j++) {
                if (!isInside(ret, v[j])) {
                    Vector2D center = (v[i] + v[j]) / 2.0;
                    double radius = abs(v[i] - v[j]) / 2.0;
                    ret = Circumference(center, radius);
                    notify(ret, {v[i], v[j]}); // Destaque: Pontos I, J

                    for (size_t k = 0; k < j; k++) {
                        if (!isInside(ret, v[k])) {
                            Vector2D center3 = getCircumcenter(v[i], v[j], v[k]);
                            double radius3 = abs(center3 - v[i]);
                            ret = Circumference(center3, radius3);
                            notify(ret, {v[i], v[j], v[k]}); // Destaque: Pontos I, J, K
                        }
                    }
                }
            }
        }
    }
    return ret;
}
