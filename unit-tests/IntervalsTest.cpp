#include <gtest/gtest.h>
#include "Triangle.h"
#include "Vector.h"
#include "Plane.h"
#include "GeomFunctions.h"
#include <cmath>
#include "Intervals.h"
#include "OctTree.h"

TEST(IntervalTesting, IntervalsGeneration1) {
    Triangle3D triang0 {Point3D(0, -0.5, 0), Point3D(0, 0.5, 0), Point3D(0, 0, 0.5)};
    Triangle3D triang1 {Point3D(0.25, 0, 0.25), Point3D(-0.25, 0, 0.25), Point3D(0, 0, 1)};

    Plane triang0_plane {triang0.v0, triang0.v1, triang0.v2};
    Plane triang1_plane {triang1.v0, triang1.v1, triang1.v2};

    Line3D line = getPlanesInterLine(triang0_plane, triang1_plane);
    line.dist = Vector3D(0,0 ,1);

    float v_pr_0_0 = line.dist & Vector3D(triang0.v0 - line.p);
    float v_pr_0_1 = line.dist & Vector3D(triang0.v1 - line.p);
    float v_pr_0_2 = line.dist & Vector3D(triang0.v2 - line.p);

    float v_pr_1_0 = line.dist & Vector3D(triang1.v0 - line.p);
    float v_pr_1_1 = line.dist & Vector3D(triang1.v1 - line.p);
    float v_pr_1_2 = line.dist & Vector3D(triang1.v2 - line.p);

    float dist_v_0_0 = triang1_plane.distanceFromPoint(triang0.v0);
    float dist_v_0_1 = triang1_plane.distanceFromPoint(triang0.v1);
    float dist_v_0_2 = triang1_plane.distanceFromPoint(triang0.v2);

    float dist_v_1_0 = triang0_plane.distanceFromPoint(triang1.v0);
    float dist_v_1_1 = triang0_plane.distanceFromPoint(triang1.v1);
    float dist_v_1_2 = triang0_plane.distanceFromPoint(triang1.v2);

    Interval intervals0 = calculateTriInterval(v_pr_0_0, v_pr_0_1, v_pr_0_2, dist_v_0_0, dist_v_0_1, dist_v_0_2);
    Interval intervals1 = calculateTriInterval(v_pr_1_0, v_pr_1_1, v_pr_1_2, dist_v_1_0, dist_v_1_1, dist_v_1_2);

    ASSERT_TRUE(intervals0.t0 == 0);
    ASSERT_TRUE(intervals0.t1 == 0.5);

    ASSERT_TRUE(intervals1.t0 == 0.25);
    ASSERT_TRUE(intervals1.t1 == 1);
}

TEST(IntervalTesting, IntervalsOverlapping1) {

    Interval interval0 {0, 0.5};
    Interval interval1 {0.25, 1};

    ASSERT_TRUE(interval0.overlapWith(interval1));
}

TEST(IntervalTesting, IntervalsOverlapping2) {

    Interval interval0 {0.25, 1};
    Interval interval1 {0, 0.5};

    ASSERT_TRUE(interval0.overlapWith(interval1));
}

TEST(IntervalTesting, IntervalsOverlapping3) {

    Interval interval0 {0.25, 1};
    Interval interval1 {3, 5};

    ASSERT_FALSE(interval0.overlapWith(interval1));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}