#pragma once
#include "Point.h"

class Triangle3D {
public:
    Point3D v0;
    Point3D v1;
    Point3D v2;

    Triangle3D(const Point3D& p0, const Point3D& p1, const Point3D& p2) : v0{p0}, v1{p1}, v2{p2} {};
    bool isDegenerate() const;
    void print();
};

class Triangle2D {
public:
    Point2D v0;
    Point2D v1;
    Point2D v2;

    Triangle2D(const Point2D& p0, const Point2D& p1, const Point2D& p2) : v0{p0}, v1{p1}, v2{p2} {};
    bool hasPointInside(const Point2D& point);
    void print();
};