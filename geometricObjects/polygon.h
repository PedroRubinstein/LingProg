
#ifndef POLYGON_H
#define POLYGON_H

#include "point.h"
#include <vector>
#include <string>

class Polygon : public geometricObject {
public:
    Polygon() = default;
    Polygon(const std::vector<Point> &);

    void addVertex(const Point &);
    void setVertices(const std::vector<Point> &pts);
    const std::vector<Point>& getVertices() const;

    // Overrides
    void print() const;
    geometricObject::Type type() const;

private:
    std::vector<Point> m_vertices;
};

#endif // POLYGON_H
