#ifndef PLOTTER_H
#define PLOTTER_H

#include "geometricobject.h"
#include "polygon.h"
#include <vector>

class Plotter {
public:
    static void plot(const std::vector<geometricObject*> &objects);
};

#endif // PLOTTER_H
