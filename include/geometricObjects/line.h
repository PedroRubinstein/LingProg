#ifndef LINE_H
#define LINE_H

#include <ostream> 
#include "geometricobject.h"
#include "vector2d.h" 

class Line : public geometricObject {
public:
    Line();
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
