#include "GeomFunctions.h"
#include <cmath>
#include <assert.h>

bool isEqual(float a, float b) {
    return std::abs(a - b) < EPS;
}

float pointToPlaneDistance(const Point& p, const Plane& plane) {
    return ((plane.norm & Vector(p)) + plane.dist) / plane.norm.getModule();
}

Line getPlanesInterLine(const Plane& p1, const Plane& p2) {
    Vector d = p1.norm * p2.norm;

    assert(d.getModule() != 0);

    float s1 = p1.dist;
    float s2 = p2.dist;

    float n1n2dot = p1.norm & p2.norm;
    float n1normsqr = p1.norm & p1.norm;
    float n2normsqr = p2.norm & p2.norm;

    float a = (s2 * n1n2dot - s1 * n2normsqr) / (- std::pow(n1n2dot, 2) + n1normsqr * n2normsqr);
    float b = (s1 * n1n2dot - s2 * n1normsqr) / (- std::pow(n1n2dot, 2) + n1normsqr * n2normsqr);

    Line intersection {(p1.norm * a  + p2.norm * b).vec_end, d};

    return intersection;
}