#pragma once
#include "Point.h"
#include "Vector.h"

class Line3D {
    // Line3D = P + tD, where D - vector
public:
    Point3D p;
    Vector3D dist;

    Line3D(const Point3D& p, const Vector3D& dist) : p{p}, dist{dist} {};
    bool havePoint(const Point3D& point);
    Point3D getPointByParameter(float param);
    void print();
};

class Line2D {
public:
    Point2D p1;
    Point2D p2;

    bool intersectWith(const Line2D& line);

    Line2D(const Point2D& p1, const Point2D& p2) : p1{p1}, p2{p2} {};
    void print();
};