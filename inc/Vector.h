#pragma once
#include "Point.h"

class Vector {
public:
    Point vec_end;

    Vector() : vec_end(0, 0, 0) {};
    Vector(const Point& vec_end) : vec_end{vec_end} {};
    Vector(float x, float y, float z) : vec_end{Point(x, y, z)} {};

    float getModule() const;

    bool colleniarWith(const Vector& vec) const;

    // cross
    Vector operator*(const Vector& vec) const;

    // dot
    float operator&(const Vector& vec) const;

    bool   operator==(const Vector& vec) const;
    Vector operator+(const Vector& vec)  const;
    Vector operator-(const Vector& vec)  const;

    Vector operator*(float factor)  const;
    Vector operator/(float divider)  const;

    Vector operator-() const;
};