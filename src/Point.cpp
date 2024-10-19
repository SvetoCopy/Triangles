#include "Point.h"
#include "GeomFunctions.h"
#include <assert.h>

Point3D Point3D::operator+(const Point3D& p) const {
    return Point3D(x + p.x, y + p.y, z + p.z);
}

Point3D Point3D::operator-(const Point3D& p) const {
    return Point3D(x - p.x, y - p.y, z - p.z);
}

bool Point3D::operator==(const Point3D& p) const {
    return isEqual(p.x, x) && isEqual(p.y, y) && isEqual(p.z, z);
}

Point3D Point3D::operator/(float divider)  const {
    assert(isEqual(divider, 0) == false);

    return Point3D(x / divider, y / divider, z / divider);
}

Point3D Point3D::operator*(float factor)  const {
    return Point3D(x * factor, y * factor, z * factor);
}

void Point3D::print() {
    std::cout << x << ' ' << y << ' ' << z << '\n';
}


// Point 2D
Point2D Point2D::operator+(const Point2D& p) const {
    return Point2D(x + p.x, y + p.y);
}

Point2D Point2D::operator-(const Point2D& p) const {
    return Point2D(x - p.x, y - p.y);
}

bool Point2D::operator==(const Point2D& p) const {
    return isEqual(p.x, x) && isEqual(p.y, y);
}

Point2D Point2D::operator/(float divider)  const {
    assert(isEqual(divider, 0) == false);

    return Point2D(x / divider, y / divider);
}

Point2D Point2D::operator*(float factor)  const {
    return Point2D(x * factor, y * factor);
}

void Point2D::print() {
    std::cout << x << ' ' << y << '\n';
}