#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include <ostream> 
#include <istream> // Necessário
#include "geometricobject.h"
#include "vector2d.h"

class Polygon : public geometricObject {
public:
    Polygon() = default;
    Polygon(const std::vector<Vector2D> &pts);

    void addVertex(const Vector2D &p);
    void setVertices(const std::vector<Vector2D> &pts);
    const std::vector<Vector2D>& getVertices() const;
    double getArea() const;

    geometricObject::Type type() const override;

    friend std::ostream& operator<<(std::ostream& out, const Polygon& p);
    // [NOVO]
    friend std::istream& operator>>(std::istream& in, Polygon& p);
    
    std::string serialize() const override;

private:
    std::vector<Vector2D> m_vertices;
};

#endif
