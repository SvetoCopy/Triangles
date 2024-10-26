#include "Intervals.h"
#include "Plane.h"

bool Interval::overlapWith(Interval interval1) {
    return std::max(this->t0, interval1.t0) < std::min(this->t1, interval1.t1);
}