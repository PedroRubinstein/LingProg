#ifndef GEOMETRICOBJECT_H
#define GEOMETRICOBJECT_H

#include <string>

class geometricObject {
public:
    // Tipo do objeto (útil para identificação em tempo de execução)
    enum class Type {
        Unknown,
        Point,
        Polygon,
        Circumference
    };

    geometricObject() = default;
    virtual ~geometricObject() = default;

    virtual void print() const = 0;

    // Retorna o tipo concreto do objeto
    virtual Type type() const = 0;
};

#endif