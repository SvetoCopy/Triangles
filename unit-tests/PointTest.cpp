#include <gtest/gtest.h>
#include "Triangle.h"
#include "Vector.h"
#include "Plane.h"
#include "GeomFunctions.h"
#include <cmath>
#include "Intervals.h"
#include "OctTree.h"

TEST(GEOM_TESTs, Triangle2DhasPoint2D) {
    Triangle2D tr1 {Point2D(0, 1), Point2D(1, 0), Point2D(0, 0)};
    Point2D point1 {0.1, 0.1};
    Point2D point2 {1, 1};

    ASSERT_TRUE(tr1.hasPointInside(point1));
    ASSERT_FALSE(tr1.hasPointInside(point2));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}