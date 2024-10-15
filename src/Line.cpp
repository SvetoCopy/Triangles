#include "Line.h"

bool Line::havePoint(const Point& point) {
    Vector vec {p - point};
    return vec.colleniarWith(dist);
}

Point Line::getPointByParameter(float param) {
    return p + (dist * param).vec_end;
}