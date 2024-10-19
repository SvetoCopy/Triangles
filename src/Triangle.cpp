#include "Triangle.h"
#include "GeomFunctions.h"

bool Triangle3D::isDegenerate() const {
    float first_fraq  = (v2.x - v0.x) / (v1.x - v0.x);
    float second_fraq = (v2.y - v0.y) / (v1.y - v0.y);
    float third_fraq  = (v2.z - v0.z) / (v1.z - v0.z);

    return isEqual(first_fraq, second_fraq) && isEqual(second_fraq, third_fraq) && isEqual(first_fraq, third_fraq);
}

void Triangle3D::print() {
    v0.print();
    v1.print();
    v2.print();
}


// Triangle2D

void Triangle2D::print() {
    v0.print();
    v1.print();
    v2.print();
}

bool Triangle2D::hasPointInside(const Point2D& point) {
    Vector2D OA = Vector2D(v0 - point);
    Vector2D OB = Vector2D(v1 - point);
    Vector2D OC = Vector2D(v2 - point);

    float p = OA * Vector2D(v1 - v0);
    float q = OB * Vector2D(v2 - v1);
    float r = OC * Vector2D(v0 - v2);

    return (p <= 0 && q <= 0 && r <= 0) || (p >= 0 && q >= 0 && r >= 0);
}
