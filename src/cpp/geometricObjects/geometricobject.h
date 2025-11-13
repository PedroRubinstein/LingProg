#ifndef GEOMETRICOBJECT_H
#define GEOMETRICOBJECT_H

#include <string>
#include <iostream>

class geometricObject {
public:
    // Makes it easier to identify object types
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

    // Returns the type of the geometric object
    virtual Type type() const = 0;
private:
    int id = -1; // Unique identifier for the object
};

#endif
