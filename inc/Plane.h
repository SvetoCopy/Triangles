#pragma once
#include "Vector.h"

class Plane {
public:
    Vector norm;
    float dist;

    Plane(const Point& p0, const Point& p1, const Point& p2);
    Plane(const Vector& norm, float dist) : norm{norm}, dist{dist} {};

    float distanceFromPoint(const Point& point);

    bool operator==(const Plane& plane) const;
};