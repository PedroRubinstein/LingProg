#ifndef LINE_H
#define LINE_H

#include "geometricobject.h"
#include "point.h"

class Line : public geometricObject {
public:
    Line();
    Line(const Point &p1, const Point &p2);

    const Point& getP1() const;
    const Point& getP2() const;
    void setP1(const Point &p);
    void setP2(const Point &p);

    // Overrides
    void print() const override;
    geometricObject::Type type() const override;

private:
    Point m_p1;
    Point m_p2;
};

#endif // LINE_H
