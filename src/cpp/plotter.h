#ifndef PLOTTER_H
#define PLOTTER_H

#include <vector>

#include "geometricObjects/geometricobject.h"
#include "geometricObjects/polygon.h"

class Plotter {
public:
    Plotter();
    ~Plotter();

    void plot(const std::vector<geometricObject*> &objects);
    bool saveFigure(const std::string &filename);
};

#endif // PLOTTER_H
