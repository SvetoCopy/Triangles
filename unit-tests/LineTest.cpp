#include <gtest/gtest.h>
#include "Triangle.h"
#include "Vector.h"
#include "Plane.h"
#include "GeomFunctions.h"
#include <cmath>
#include "Intervals.h"
#include "OctTree.h"

TEST(GEOM_TESTs, PointInLine1) {
    Line3D line {Point3D(0, 1.5, 0), Vector3D(16, -8, 0)};
    Point3D p {Point3D(0, 1.5, 0) + (Vector3D(16, -8, 0) * 3).vec_end};

    ASSERT_TRUE(line.havePoint(p) == true);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}