#pragma once
#include "Plane.h"
#include "Line.h"

const float EPS = 0.001;

bool isEqual(float a, float b);

Line3D getPlanesInterLine(const Plane& p1, const Plane& p2);
