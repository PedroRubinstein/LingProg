#ifndef GEOMETRICOBJECT_H
#define GEOMETRICOBJECT_H

#include <string>
#include <iostream>

class geometricObject {
public:
    enum class Type {
        Unknown,
        Point,
        Line,
        Vector2D,
        Polygon,
        Circumference
    };

    geometricObject() = default;
    virtual ~geometricObject() = default;

    void setId(int newId) { id = newId; }
    int getId() const { return id; }

    virtual Type type() const = 0;
    virtual std::string serialize() const = 0;
private:
    int id = -1;
};

#endif
