#ifndef LINE_H
#define LINE_H

#include <ostream> 
#include "geometricobject.h"
#include "vector2d.h" 

/**
 * @brief Representa um segmento de reta definido por dois pontos.
 */
class Line : public geometricObject {
public:
    /**
     * @brief Construtor padrão (0,0) -> (1,0).
     */
    Line();

    /**
     * @brief Construtor com dois pontos.
     * @param p1 Ponto inicial.
     * @param p2 Ponto final.
     */
    Line(const Vector2D &p1, const Vector2D &p2);

    const Vector2D& getP1() const;
    const Vector2D& getP2() const;
    void setP1(const Vector2D &p);
    void setP2(const Vector2D &p);

    geometricObject::Type type() const override;

    friend std::ostream& operator<<(std::ostream& out, const Line& l);
    std::string serialize() const override;

private:
    Vector2D m_p1;
    Vector2D m_p2;
};

#endif // LINE_H
