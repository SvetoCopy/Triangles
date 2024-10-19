#pragma once
#include "Vector.h"
#include "Triangle.h"

enum IntersectionType {
    VERTEX_ONLY = 0,
    EDGE_ONLY = 1,
    GENERAL_INTERSECTION = 2,
    TRIANGLE_ON_PLANE = 3,
    NO_INTERSECTION = 4
};

class Plane {
public:
    Vector3D norm;
    float dist;

    Plane(const Triangle3D triangle);
    Plane(const Point3D& p0, const Point3D& p1, const Point3D& p2);
    Plane(const Vector3D& norm, float dist) : norm{norm}, dist{dist} {};

    float distanceFromPoint(const Point3D& point);
    IntersectionType IntersecTypeWithTriangle(const Triangle3D& triang);

    bool operator==(const Plane& plane) const;
};