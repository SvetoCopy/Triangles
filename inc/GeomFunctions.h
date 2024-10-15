#pragma once
#include "Plane.h"
#include "Line.h"

const float EPS = 0.001;

bool isEqual(float a, float b);

float pointToPlaneDistance(const Point& p, const Plane& plane);

Line getPlanesInterLine(const Plane& p1, const Plane& p2);