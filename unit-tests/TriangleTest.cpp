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

TEST(GEOM_TESTs, TriangleDegenerate1) {
    Triangle3D t {Point3D(1, 0, 1), Point3D(1, 0, -1), Point3D(0, 1, 1)};
    ASSERT_FALSE(t.isDegenerate());
}

TEST(GEOM_TESTs, TriangleDegenerate2) {
    Triangle3D t {Point3D(0, 0, 1), Point3D(0, 0, -1), Point3D(0, 0, 2)};
    ASSERT_TRUE(t.isDegenerate());
}

TEST(GEOM_TESTs, SmallIntersection)
{
    Triangle2D triangle1(Point2D(0, 0), Point2D(5, 0), Point2D(2.5, 5));
    Triangle2D triangle2(Point2D(2, 2), Point2D(6, 0), Point2D(4, 4));

    ASSERT_TRUE(triangle1.intersectWith(triangle2));
}

TEST(GEOM_TESTs, NoIntersection1)
{
    Triangle2D triangle1(Point2D(0, 0), Point2D(5, 0), Point2D(2.5, 5));
    Triangle2D triangle2(Point2D(3.5, 3.5), Point2D(6, 0), Point2D(4, 4));

    ASSERT_FALSE(triangle1.intersectWith(triangle2));
}

TEST(GEOM_TESTs, OneInAnother1)
{
    Triangle2D triangle1(Point2D(0, 0), Point2D(5, 0), Point2D(2.5, 5));
    Triangle2D triangle2(Point2D(2, 2), Point2D(3, 0), Point2D(3, 3));

    ASSERT_TRUE(triangle1.intersectWith(triangle2));
}

TEST(OctTree, BBcontainsTri)
{
    BoundingBox bb {Vector3D(0, -2, 0), Vector3D(0, 2, 2)};
    Triangle3D tri {Point3D(0, -1, 0), Point3D(0, 1, 0), Point3D(0, 0, 1)};
    ASSERT_TRUE(bb.contains(tri));
}

TEST(GENERAL, Tri3DIntersect1) {
    Triangle3D triang0 {Point3D(0, -0.5, 0), Point3D(0, 0.5, 0), Point3D(0, 0, 0.5)};
    Triangle3D triang1 {Point3D(0.25, 0, 0.25), Point3D(-0.25, 0, 0.25), Point3D(0, 0, 1)};

    ASSERT_TRUE(triang0.intersectWith(triang1));
}

TEST(GENERAL, Tri3DIntersect2) {
    Triangle3D triang0(Point3D{3, 4, 5}, Point3D{5, 6, 7}, Point3D{3, 8, 9});
    Triangle3D triang1(Point3D{5, 3, 2}, Point3D{2, -2, 1}, Point3D{2, 2, 0});

    ASSERT_FALSE(triang0.intersectWith(triang1));
}

TEST(GENERAL, Tri3DIntersect3) {
    Triangle3D triang0(Point3D{1, 0, 0}, Point3D{0, 1, 0}, Point3D{0, 0, 1});
    Triangle3D triang1(Point3D{0, 0, 0}, Point3D{1, 1, 1}, Point3D{0, 0, 2});

    ASSERT_TRUE(triang0.intersectWith(triang1));
}

TEST(GENERAL, Tri3DIntersect4) {
    Triangle3D triang0(Point3D(5, 4, 3), Point3D(1, 1, 3), Point3D(2, 4, 3));
    Triangle3D triang1(Point3D(3, 3, 2), Point3D(1, 1, 2), Point3D(1, 1, 0));

    ASSERT_FALSE(triang0.intersectWith(triang1));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}