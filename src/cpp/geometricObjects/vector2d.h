#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <ostream>
#include <stdexcept>
#include <cmath>
#include "geometricobject.h"

using namespace std;
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

    Vector2D operator+(const Vector2D& other) const;
    Vector2D operator-(const Vector2D& other) const;
    ld operator*(const Vector2D& other) const;
    ld operator^(const Vector2D& other) const;
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
