#ifndef GEOMETRICOBJECT_H
#define GEOMETRICOBJECT_H

#include <string>

class geometricObject {
public:
    // Makes it easier to identify object types
    enum class Type {
        Unknown,
        Point,
        Polygon,
        Circumference
    };

    geometricObject() = default;
    virtual ~geometricObject() = default;

    void setId(int newId) { id = newId; }
    int getId() const { return id; }

    virtual void print() const = 0;

    // Returns the type of the geometric object
    virtual Type type() const = 0;
private:
    int id = -1; // Unique identifier for the object
};

#endif