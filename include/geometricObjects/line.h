#ifndef LINE_H
#define LINE_H

#include <ostream> 
#include "geometricobject.h"
#include "vector2d.h" 

/**
 * @brief Representa um Segmento definido por dois pontos (início e fim).
 * * Diferente de uma reta infinita, este objeto tem comprimento finito.
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

    /**
     * @brief Verifica se um ponto está contido neste segmento de reta.
     * @param p O ponto a testar.
     * @return true Se o ponto estiver sobre o segmento.
     */
    bool contains(const Vector2D& p) const;
    
    /**
     * @brief Verifica a posição relativa de um ponto (Esq/Dir/Colin).
     */
    std::string pointLocation(const Vector2D& point) const;

    /**
     * @brief Verifica se esta linha intercepta outra.
     */
    bool intersects(const Line& other) const;

    geometricObject::Type type() const override;

    friend std::ostream& operator<<(std::ostream& out, const Line& l);
    std::string serialize() const override;

private:
    Vector2D m_p1;
    Vector2D m_p2;
};

#endif // LINE_H
