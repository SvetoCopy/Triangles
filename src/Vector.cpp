#include "Vector.h"
#include <cmath>
#include "GeomFunctions.h"

Vector3D Vector3D::operator+(const Vector3D& vec) const {
    return Vector3D(vec_end + vec.vec_end);
}

Vector3D Vector3D::operator-(const Vector3D& vec) const {
    return Vector3D(vec_end - vec.vec_end);
}

Vector3D Vector3D::operator*(const Vector3D& vec) const {
    return Vector3D(vec_end.y * vec.vec_end.z - vec_end.z * vec.vec_end.y, 
                  vec_end.z * vec.vec_end.x - vec_end.x * vec.vec_end.z, 
                  vec_end.x * vec.vec_end.y - vec_end.y * vec.vec_end.x);
}

float Vector3D::operator&(const Vector3D& vec) const {
    return vec_end.x * vec.vec_end.x + vec_end.y * vec.vec_end.y + vec_end.z * vec.vec_end.z;
}

bool Vector3D::operator==(const Vector3D& vec) const {
    return vec_end == vec.vec_end;
}

Vector3D Vector3D::operator-() const {
    return Vector3D(-vec_end.x, -vec_end.y, -vec_end.z);
};

float Vector3D::getModule() const {
    return std::pow(vec_end.x * vec_end.x + vec_end.y * vec_end.y + vec_end.z * vec_end.z, 0.5);
}

Vector3D Vector3D::operator*(float factor) const {
    return Vector3D(vec_end * factor);
}

Vector3D Vector3D::operator/(float divider) const {
    return Vector3D(vec_end / divider);
}

bool Vector3D::colleniarWith(const Vector3D& vec) const {
    float coeff = 0;

    if (vec == Vector3D(Point3D(0, 0, 0)) || *this == Vector3D(Point3D(0, 0, 0)))
        return true;
    
    if (isEqual(vec_end.x, 0)) coeff = 1;
    else coeff = vec.vec_end.x / vec_end.x;

    if (vec.vec_end == (vec_end * coeff))
        return true;

    return false;
}

void Vector3D::print() {
    vec_end.print();
}


// Vector2D

float Vector2D::operator*(const Vector2D& vec) const {
    return vec_end.x * vec.vec_end.y - vec_end.y * vec.vec_end.x;
}
