#ifndef PLOTTER_H
#define PLOTTER_H

#include "geometricobject.h"
#include "polygon.h"
#include <vector>

class Plotter {
public:
    Plotter();
    ~Plotter();

    void plot(const std::vector<geometricObject*> &objects);
    bool saveFigure(const std::string &filename);
};

#endif // PLOTTER_H
