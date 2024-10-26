#include "Plane.h"
#include "GeomFunctions.h"
#include <cmath>

Plane::Plane(const Point3D& p0, const Point3D& p1, const Point3D& p2) {
    Vector3D vec01 = Vector3D(p1 - p0);
    Vector3D vec02 = Vector3D(p2 - p0);

    norm = vec01 * vec02;
    dist = -(norm & Vector3D(p0));
}

Plane::Plane(const Triangle3D triangle) {
    *this = Plane(triangle.v0, triangle.v1, triangle.v2);
}

bool Plane::parallelWith(const Plane& plane) const {
    float coeff = plane.norm.vec_end.x / norm.vec_end.x;
    return (norm * coeff == plane.norm);
}

bool Plane::operator==(const Plane& plane) const {
    float coeff = std::max(plane.dist / dist, dist / plane.dist);
    
    if (!isEqual(std::fmod(coeff, 1.0f), 0)) return false;

    if (plane.norm / coeff == norm || norm / coeff == plane.norm)
        return true;
    return false;
}

float Plane::distanceFromPoint(const Point3D& point) {
    return ((norm & Vector3D(point)) + dist) / norm.getModule();
}

IntersectionType Plane::IntersecTypeWithTriangle(const Triangle3D& triang) {
    float dist0 = distanceFromPoint(triang.v0);
    float dist1 = distanceFromPoint(triang.v1);
    float dist2 = distanceFromPoint(triang.v2);

    if (isEqual(dist0 * dist1 * dist2, 0)) {
        if (isEqual(dist0 + dist1 + dist2, 0))
            return TRIANGLE_ON_PLANE;

        if (isEqual(dist0, 0) && isEqual(dist1, 0) ||
            isEqual(dist0, 0) && isEqual(dist2, 0) ||
            isEqual(dist1, 0) && isEqual(dist2, 0))
            return EDGE_ONLY;

        return VERTEX_ONLY;
    }
    
    if ((dist0 > 0 && dist1 > 0 && dist2 > 0) ||
        (dist0 < 0 && dist1 < 0 && dist2 < 0))
        return NO_INTERSECTION;

    return GENERAL_INTERSECTION;
}