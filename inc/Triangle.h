#pragma once
#include "Point.h"

class Triangle {
public:
    Point v0;
    Point v1;
    Point v2;

    Triangle(const Point& p0, const Point& p1, const Point& p2) : v0{p0}, v1{p1}, v2{p2} {};
    bool isDegenerate() const;
};