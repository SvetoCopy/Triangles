#include "Vector.h"
#include <cmath>
#include "GeomFunctions.h"

Vector Vector::operator+(const Vector& vec) const {
    return Vector(vec_end + vec.vec_end);
}

Vector Vector::operator-(const Vector& vec) const {
    return Vector(vec_end - vec.vec_end);
}

Vector Vector::operator*(const Vector& vec) const {
    return Vector(vec_end.y * vec.vec_end.z - vec_end.z * vec.vec_end.y, 
                  vec_end.z * vec.vec_end.x - vec_end.x * vec.vec_end.z, 
                  vec_end.x * vec.vec_end.y - vec_end.y * vec.vec_end.x);
}

float Vector::operator&(const Vector& vec) const {
    return vec_end.x * vec.vec_end.x + vec_end.y * vec.vec_end.y + vec_end.z * vec.vec_end.z;
}

bool Vector::operator==(const Vector& vec) const {
    return vec_end == vec.vec_end;
}

Vector Vector::operator-() const {
    return Vector(-vec_end.x, -vec_end.y, -vec_end.z);
};

float Vector::getModule() const {
    return std::pow(vec_end.x * vec_end.x + vec_end.y * vec_end.y + vec_end.z * vec_end.z, 0.5);
}

Vector Vector::operator*(float factor) const {
    return Vector(vec_end * factor);
}

Vector Vector::operator/(float divider) const {
    return Vector(vec_end / divider);
}

bool Vector::colleniarWith(const Vector& vec) const {
    float coeff = 0;

    if (vec == Vector(Point(0, 0, 0)) || *this == Vector(Point(0, 0, 0)))
        return true;
    
    if (isEqual(vec_end.x, 0)) coeff = 1;
    else coeff = vec.vec_end.x / vec_end.x;

    if (vec.vec_end == (vec_end * coeff))
        return true;

    return false;
}
