#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <ostream>
#include <stdexcept>
#include <cmath>
#include <string>
#include "geometricobject.h"

typedef long double ld;

/**
 * @brief Representa um ponto ou vetor no espaço bidimensional.
 */
class Vector2D : public geometricObject {
public:
    /**
     * @brief Construtor padrão. Inicializa em (0,0).
     */
    Vector2D();

    /**
     * @brief Construtor com coordenadas.
     * @param x Coordenada X.
     * @param y Coordenada Y.
     */
    Vector2D(ld x, ld y);

    ld getX() const;
    ld getY() const;
    void setX(ld x);
    void setY(ld y);

    geometricObject::Type type() const override;

    // --- Static Geometric Helpers ---

    /**
     * @brief Calcula o produto vetorial (componente Z) de (b-a) e (c-a).
     * * Usado para determinar a orientação de três pontos.
     * @return ld Valor positivo se CCW, negativo se CW, zero se colinear.
     */
    static ld crossProduct(const Vector2D& a, const Vector2D& b, const Vector2D& c);
    
    /**
     * @brief Calcula a distância euclidiana ao quadrado entre dois pontos.
     * * Evita a raiz quadrada para comparações de desempenho.
     */
    static ld distSq(const Vector2D& a, const Vector2D& b);
    
    /**
     * @brief Verifica se a sequência a->b->c forma uma curva estritamente Anti-Horária (CCW).
     * @return true Se a curva for à esquerda.
     */
    static bool ccw(const Vector2D& a, const Vector2D& b, const Vector2D& c);
    
    // --- Operator Overloads ---

    Vector2D operator+(const Vector2D& other) const;
    Vector2D operator-(const Vector2D& other) const;
    bool operator<(const Vector2D& other) const;

    /**
     * @brief Produto Escalar (Dot Product).
     */
    ld operator*(const Vector2D& other) const; 
    
    /**
     * @brief Produto Vetorial 2D (Cross Product).
     */
    ld operator^(const Vector2D& other) const; 

    Vector2D& operator+=(const Vector2D& other);
    Vector2D& operator-=(const Vector2D& other);

    // Operadores com escalares
    template <typename T>
    Vector2D operator*(T scalar) const {
        return Vector2D(m_x * static_cast<ld>(scalar), 
                        m_y * static_cast<ld>(scalar));
    }

    template <typename T>
    Vector2D operator/(T scalar) const {
        const ld d_scalar = static_cast<ld>(scalar);
        if (d_scalar == 0) throw std::runtime_error("Divisão por zero em Vector2D");
        return Vector2D(m_x / d_scalar, m_y / d_scalar);
    }

    template <typename T>
    Vector2D& operator*=(T scalar) {
        const ld d_scalar = static_cast<ld>(scalar);
        m_x *= d_scalar; m_y *= d_scalar;
        return *this;
    }

    template <typename T>
    Vector2D& operator/=(T scalar) {
        const ld d_scalar = static_cast<ld>(scalar);
        if (d_scalar == 0) throw std::runtime_error("Divisão por zero em Vector2D");
        m_x /= d_scalar; m_y /= d_scalar;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream &out, const Vector2D &vector);

    std::string serialize() const override;

    /**
     * @brief Permite que um visitante processe esta instância de Vector2D.
     * @param visitor O visitante que executará a lógica específica para vetores.
     */
    void accept(ShapeVisitor& visitor) override;

private:
    ld m_x;
    ld m_y;
};

/**
 * @brief Permite multiplicação escalar à esquerda (ex: 2.0 * v).
 */
template <typename T>
Vector2D operator*(T scalar, const Vector2D& vec) {
    return vec * scalar; 
}

/**
 * @brief Retorna o módulo (magnitude) do vetor.
 */
ld abs(const Vector2D& vec);

#endif
