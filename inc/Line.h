#pragma once
#include "Point.h"
#include "Vector.h"

class Line {
    // Line = P + tD, where D - vector
public:
    Point p;
    Vector dist;

    Line(const Point& p, const Vector& dist) : p{p}, dist{dist} {};
    bool havePoint(const Point& point);
    Point getPointByParameter(float param);
};