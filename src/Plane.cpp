#include "Plane.h"
#include "GeomFunctions.h"
#include <cmath>

Plane::Plane(const Point& p0, const Point& p1, const Point& p2) {
    Vector vec01 = Vector(p1 - p0);
    Vector vec02 = Vector(p2 - p0);

    norm = vec01 * vec02;
    dist = -(norm & Vector(p0));
}

bool Plane::operator==(const Plane& plane) const {
    float coeff = std::max(plane.dist / dist, dist / plane.dist);
    
    if (!isEqual(std::fmod(coeff, 1.0f), 0)) return false;

    if (plane.norm / coeff == norm || norm / coeff == plane.norm)
        return true;
    return false;
}