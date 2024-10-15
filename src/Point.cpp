#include "Point.h"
#include "GeomFunctions.h"
#include <assert.h>

Point Point::operator+(const Point& p) const {
    return Point(x + p.x, y + p.y, z + p.z);
}

Point Point::operator-(const Point& p) const {
    return Point(x - p.x, y - p.y, z - p.z);
}

bool Point::operator==(const Point& p) const {
    return isEqual(p.x, x) && isEqual(p.y, y) && isEqual(p.z, z);
}

Point Point::operator/(float divider)  const {
    assert(isEqual(divider, 0) == false);

    return Point(x / divider, y / divider, z / divider);
}

Point Point::operator*(float factor)  const {
    return Point(x * factor, y * factor, z * factor);
}