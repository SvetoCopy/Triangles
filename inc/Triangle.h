#pragma once
#include "Point.h"
#include "Intervals.h"

const double EPSILON = 0.001;

class Triangle3D {
public:
    Point3D v0;
    Point3D v1;
    Point3D v2;

    int id;

    Triangle3D() {};
    Triangle3D(const Point3D& p0, const Point3D& p1, const Point3D& p2) : v0{p0}, v1{p1}, v2{p2} {};
    Triangle3D(const Point3D& p0, const Point3D& p1, const Point3D& p2, int id) : v0{p0}, v1{p1}, v2{p2}, id{id} {};
    bool isDegenerate() const;
    bool intersectWith(Triangle3D& triang);
    void print();
};

class Triangle2D {
public:
    Point2D v0;
    Point2D v1;
    Point2D v2;

    Triangle2D(const Point2D& p0, const Point2D& p1, const Point2D& p2) : v0{p0}, v1{p1}, v2{p2} {};
    bool hasPointInside(const Point2D& point);
    void repairWinding();
    bool intersectWith(Triangle2D& triang);
    void print();
};

Interval calculateInterval(float v_pr_0, float v_pr_1, float v_pr_2,
                           float dist_v_0, float dist_v_1, float dist_v_2);
Interval calculateTriInterval(float v_pr_0, float v_pr_1, float v_pr_2,
                              float dist_v_0, float dist_v_1, float dist_v_2);