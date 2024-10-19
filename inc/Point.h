#pragma once
#include <iostream>

class Point3D {
public:
    float x;
    float y; 
    float z; 

    Point3D(float x, float y, float z) : x{x}, y{y}, z{z} {};

    Point3D operator+(const Point3D& p)  const;
    Point3D operator-(const Point3D& p)  const; 
    bool  operator==(const Point3D& p) const;

    Point3D operator/(float divider)  const;
    Point3D operator*(float factor)  const;

    void print();
};

class Point2D {
public:
    float x;
    float y; 

    Point2D(float x, float y) : x{x}, y{y} {};

    Point2D operator+(const Point2D& p)  const;
    Point2D operator-(const Point2D& p)  const; 
    bool  operator==(const Point2D& p) const;

    Point2D operator/(float divider)  const;
    Point2D operator*(float factor)  const;

    void print();
};