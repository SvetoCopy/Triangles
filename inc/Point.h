#pragma once

class Point {
public:
    float x;
    float y; 
    float z; 

    Point(float x, float y, float z) : x{x}, y{y}, z{z} {};

    Point operator+(const Point& p)  const;
    Point operator-(const Point& p)  const; 
    bool  operator==(const Point& p) const;

    Point operator/(float divider)  const;
    Point operator*(float factor)  const;
};