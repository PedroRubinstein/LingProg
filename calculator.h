#include "point.h"

#ifndef CALCULATOR_H
#define CALCULATOR_H

class Calculator {
public:
    Calculator() = default;
    ~Calculator() = default;

    int getDistanceBetweenPoints(double x1, double y1, double x2, double y2);
private:

};
#endif