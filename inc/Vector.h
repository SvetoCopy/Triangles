#pragma once
#include "Point.h"

class Vector3D {
public:
    Point3D vec_end;

    Vector3D() : vec_end(0, 0, 0) {};
    Vector3D(const Point3D& vec_end) : vec_end{vec_end} {};
    Vector3D(float x, float y, float z) : vec_end{Point3D(x, y, z)} {};

    float getModule() const;

    bool colleniarWith(const Vector3D& vec) const;

    // cross
    Vector3D operator*(const Vector3D& vec) const;

    // dot
    float operator&(const Vector3D& vec) const;

    bool   operator==(const Vector3D& vec) const;
    Vector3D operator+(const Vector3D& vec)  const;
    Vector3D operator-(const Vector3D& vec)  const;

    Vector3D operator*(float factor)  const;
    Vector3D operator/(float divider)  const;

    Vector3D operator-() const;
    void print();
};

class Vector2D {
public:
    Point2D vec_end;

    Vector2D() : vec_end(0, 0) {};
    Vector2D(const Point2D& vec_end) : vec_end{vec_end} {};
    Vector2D(float x, float y) : vec_end{Point2D(x, y)} {};

    // cross
    float operator*(const Vector2D& vec) const;

    void print();
};