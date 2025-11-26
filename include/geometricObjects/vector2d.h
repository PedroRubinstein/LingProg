#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <ostream>
#include <stdexcept>
#include <cmath>
#include <string>
#include "geometricobject.h"

typedef long double ld;

class Vector2D : public geometricObject {
public:
    Vector2D();
    Vector2D(ld x, ld y);

    ld getX() const;
    ld getY() const;
    void setX(ld x);
    void setY(ld y);

    geometricObject::Type type() const override;

    // --- Static Geometric Helpers (Refactored) ---
    // Returns the cross product (z-component) of vectors (b-a) and (c-a)
    static ld crossProduct(const Vector2D& a, const Vector2D& b, const Vector2D& c);
    
    // Returns squared Euclidean distance between a and b
    static ld distSq(const Vector2D& a, const Vector2D& b);
    
    // Returns true if a->b->c is a strictly Counter-Clockwise turn
    static bool ccw(const Vector2D& a, const Vector2D& b, const Vector2D& c);
    
    // Checks if point p lies on the segment defined by endpoints a and b
    static bool onSegment(const Vector2D& p, const Vector2D& a, const Vector2D& b);
    // ---------------------------------------------

    Vector2D operator+(const Vector2D& other) const;
    Vector2D operator-(const Vector2D& other) const;
    ld operator*(const Vector2D& other) const; // Dot Product
    ld operator^(const Vector2D& other) const; // Cross Product (2D)
    Vector2D& operator+=(const Vector2D& other);
    Vector2D& operator-=(const Vector2D& other);

    template <typename T>
    Vector2D operator*(T scalar) const {
        return Vector2D(m_x * static_cast<ld>(scalar), 
                        m_y * static_cast<ld>(scalar));
    }

    template <typename T>
    Vector2D operator/(T scalar) const {
        const ld d_scalar = static_cast<ld>(scalar);
        if (d_scalar == 0) {
            throw std::runtime_error("Division by zero in Vector2D operator/");
        }
        return Vector2D(m_x / d_scalar, m_y / d_scalar);
    }

    template <typename T>
    Vector2D& operator*=(T scalar) {
        const ld d_scalar = static_cast<ld>(scalar);
        m_x *= d_scalar;
        m_y *= d_scalar;
        return *this;
    }

    template <typename T>
    Vector2D& operator/=(T scalar) {
        const ld d_scalar = static_cast<ld>(scalar);
        if (d_scalar == 0) {
            throw std::runtime_error("Division by zero in Vector2D operator/=");
        }
        m_x /= d_scalar;
        m_y /= d_scalar;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream &out, const Vector2D &vector);

    std::string serialize() const override;

private:
    ld m_x;
    ld m_y;
};

template <typename T>
Vector2D operator*(T scalar, const Vector2D& vec) {
    return vec * scalar; 
}

ld abs(const Vector2D& vec);

#endif
