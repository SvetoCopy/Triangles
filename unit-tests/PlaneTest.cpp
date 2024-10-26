#include <gtest/gtest.h>
#include "Triangle.h"
#include "Vector.h"
#include "Plane.h"
#include "GeomFunctions.h"
#include <cmath>
#include "Intervals.h"
#include "OctTree.h"


TEST(GEOM_TESTs, PlaneEqFromPoints1) {
    Point3D p1 {1, 2, 1};
    Point3D p2 {-2, 3, 1};
    Point3D p3 {4, -5, 0};

    Plane plane {p1, p2 ,p3};
    
    ASSERT_TRUE(isEqual(plane.dist, -11) == true);
    ASSERT_TRUE(plane.norm == Vector3D(-1, -3, 18) || plane.norm ==  (-Vector3D(-1, -3, 18)) );
}

TEST(GEOM_TESTs, PlaneEqFromPoints2) {
    Point3D p1 {1, -4, 3};
    Point3D p2 {9, 1, 0};
    Point3D p3 {0, 0, -1};

    Plane plane {p1, p2 ,p3};
    std::cout << plane.dist;
    ASSERT_TRUE(isEqual(plane.dist, 37) == true);
    ASSERT_TRUE(plane.norm == Vector3D(-8, 35, 37) || plane.norm ==  (-Vector3D(-8, 35, 37)));
}

TEST(GEOM_TESTs, pointToPlaneDistance1) {
    Point3D point {0, 3, 6};
    Plane plane {Vector3D(2, 4, -4), -6};
    
    ASSERT_TRUE(isEqual(plane.distanceFromPoint(point), -3) == true);
}

TEST(GEOM_TESTs, PlaneEqual1) {
    Plane plane1 {Vector3D(4, 8, -8), -12};
    Plane plane2 {Vector3D(2, 4, -4), -6};
    
    ASSERT_TRUE(plane1 == plane2);
}

TEST(GEOM_TESTs, PlaneParallels1)
{
    Plane plane1 {Vector3D(4, 8, -8), -12};
    Plane plane2 {Vector3D(2, 4, -4), -6};
    
    ASSERT_TRUE(plane1.parallelWith(plane2));
}

TEST(GEOM_TESTs, PlaneParallels2)
{
    Plane plane1 {Vector3D(4, 8, -8), -10};
    Plane plane2 {Vector3D(2, 4, -4), -6};
    
    ASSERT_TRUE(plane1.parallelWith(plane2));
}

TEST(GEOM_TESTs, PlaneParallels3)
{
    Plane plane1 {Vector3D(4, 5, -8), -10};
    Plane plane2 {Vector3D(2, 4, -4), -6};
    
    ASSERT_FALSE(plane1.parallelWith(plane2));
}

TEST(GEOM_TESTs, getPlanesInterLine1) {
    Plane plane1 {Vector3D(4, 8, -8), -12};
    Plane plane2 {Vector3D(2, 4, -2), -6};

    Line3D res {Point3D(0, 1.5, 0), Vector3D(16, -8, 0)};
    Line3D expected = getPlanesInterLine(plane1, plane2);

    ASSERT_TRUE(expected.havePoint(Point3D(0, 1.5, 0)) == true);
    ASSERT_TRUE(expected.havePoint(res.getPointByParameter(4)) == true);
    ASSERT_TRUE(expected.havePoint(res.getPointByParameter(5)) == true);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}