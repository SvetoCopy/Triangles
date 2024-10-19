#pragma once
#include "Triangle.h"
#include "Line.h"

class Interval {
public:
    float t0_0;
    float t0_1;

    float t1_0;
    float t1_1;

    Interval(const Line3D& line, const Triangle3D& triang0, const Triangle3D& triang1);

};