#pragma once

class Interval {
public:
    float t0;
    float t1;

    Interval(float t0, float t1) : t0 {t0}, t1 {t1} {};
    bool overlapWith(Interval interval1);

};