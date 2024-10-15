#include "Triangle.h"
#include "GeomFunctions.h"

bool Triangle::isDegenerate() const {
    float first_fraq  = (v2.x - v0.x) / (v1.x - v0.x);
    float second_fraq = (v2.y - v0.y) / (v1.y - v0.y);
    float third_fraq  = (v2.z - v0.z) / (v1.z - v0.z);

    return isEqual(first_fraq, second_fraq) && isEqual(second_fraq, third_fraq) && isEqual(first_fraq, third_fraq);
}


