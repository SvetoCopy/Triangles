#include <gtest/gtest.h>
#include "Triangle.h"
#include "Vector.h"
#include "Plane.h"
#include "GeomFunctions.h"
#include <cmath>
#include "Intervals.h"
#include "OctTree.h"

TEST(GEOM_TESTs, TriangleDegenerate1) {
    Triangle3D t {Point3D(1, 0, 1), Point3D(1, 0, -1), Point3D(0, 1, 1)};
    ASSERT_FALSE(t.isDegenerate());
}

TEST(GEOM_TESTs, TriangleDegenerate2) {
    Triangle3D t {Point3D(0, 0, 1), Point3D(0, 0, -1), Point3D(0, 0, 2)};
    ASSERT_TRUE(t.isDegenerate());
}

TEST(GEOM_TESTs, VectorCross1) {
    Vector3D vec1 {1, 0, 1};
    Vector3D vec2 {2, 1, -1};

    Vector3D vec3 {-1, 3, 1};
    
    ASSERT_TRUE(vec1 * vec2 == vec3);
}

TEST(GEOM_TESTs, VectorCross2) {
    Vector3D vec1 {0, 2, 0};
    Vector3D vec2 {1, 0, 1};

    Vector3D vec3 {2, 0, -2};
    
    ASSERT_TRUE(vec1 * vec2 == vec3);
}

TEST(GEOM_TESTs, VectorCross3) {
    Vector3D vec1 {3, -3, 1};
    Vector3D vec2 {4, 9, 2};

    Vector3D vec3 {-15, -2, 39};
    
    ASSERT_TRUE(vec1 * vec2 == vec3);
}

TEST(GEOM_TESTs, VectorCross4) {
    Vector3D vec1 {5, 0, 0};
    Vector3D vec2 {0, 5, 0};

    Vector3D vec3 {0, 0, 25};
    
    ASSERT_TRUE(vec1 * vec2 == vec3);
}

TEST(GEOM_TESTs, VectorCross5) {
    Vector3D vec1 {-1, -2, -3};
    Vector3D vec2 {4, 5, 6};

    Vector3D vec3 {3, -6, 3};
    
    ASSERT_TRUE(vec1 * vec2 == vec3);
}

TEST(GEOM_TESTs, VectorDot1) {
    Vector3D vec1 {1, 0, 1};
    Vector3D vec2 {2, 1, -1};
    
    ASSERT_TRUE(isEqual((vec1 & vec2), 1));
}

TEST(GEOM_TESTs, VectorDot2) {
    Vector3D vec1 {0, 2, 0};
    Vector3D vec2 {1, 0, 1};

    ASSERT_TRUE(isEqual((vec1 & vec2), 0));
}

TEST(GEOM_TESTs, VectorDot3) {
    Vector3D vec1 {3, -3, 1};
    Vector3D vec2 {4, 9, 2};

    ASSERT_TRUE(isEqual((vec1 & vec2), -13));
}

TEST(GEOM_TESTs, VectorDot4) {
    Vector3D vec1 {5, 0, 0};
    Vector3D vec2 {0, 5, 0};

    ASSERT_TRUE(isEqual((vec1 & vec2), 0));
}

TEST(GEOM_TESTs, VectorDot5) {
    Vector3D vec1 {-1, -2, -3};
    Vector3D vec2 {4, 5, 6};

    ASSERT_TRUE(isEqual((vec1 & vec2), -32));
}

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

TEST(GEOM_TESTs, VectorModule1) {
    Vector3D vec {1, 0, 1};
    
    ASSERT_TRUE(isEqual(vec.getModule(), std::pow(2, 0.5)) == true);
}

TEST(GEOM_TESTs, VectorModule2) {
    Vector3D vec {2, 0, 0};
    
    ASSERT_TRUE(isEqual(vec.getModule(), 2) == true);
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

TEST(GEOM_TESTs, getPlanesInterLine1) {
    Plane plane1 {Vector3D(4, 8, -8), -12};
    Plane plane2 {Vector3D(2, 4, -2), -6};

    Line3D res {Point3D(0, 1.5, 0), Vector3D(16, -8, 0)};
    Line3D expected = getPlanesInterLine(plane1, plane2);

    ASSERT_TRUE(expected.havePoint(Point3D(0, 1.5, 0)) == true);
    ASSERT_TRUE(expected.havePoint(res.getPointByParameter(4)) == true);
    ASSERT_TRUE(expected.havePoint(res.getPointByParameter(5)) == true);
}

TEST(GEOM_TESTs, ColleniarVectors1) {
    Vector3D vec1 {1, 2 ,5};
    Vector3D vec2 {2, 4, 10};

    ASSERT_TRUE(vec2.colleniarWith(vec1) == true);
}

TEST(GEOM_TESTs, ColleniarVectors2) {
    Vector3D vec1 {0, 0, 0};
    Vector3D vec2 {0, 0, 0};

    ASSERT_TRUE(vec2.colleniarWith(vec1) == true);
}

TEST(GEOM_TESTs, PointInLine1) {
    Line3D line {Point3D(0, 1.5, 0), Vector3D(16, -8, 0)};
    Point3D p {Point3D(0, 1.5, 0) + (Vector3D(16, -8, 0) * 3).vec_end};

    ASSERT_TRUE(line.havePoint(p) == true);
}

TEST(GEOM_TESTs, TriangAndPlaneIntersect1) {
    Plane plane {Vector3D(0, 1, 0), 0};
    Triangle3D t1 {Point3D(0, 0, 1), Point3D(0, 2, 0), Point3D(-1, 0, 0)};

    ASSERT_TRUE(plane.IntersecTypeWithTriangle(t1) == EDGE_ONLY);
}

TEST(GEOM_TESTs, TriangAndPlaneIntersect2) {
    Plane plane {Vector3D(0, 1, 0), 0};
    Triangle3D t2 {Point3D(0, 0, 1), Point3D(0, 1, 0), Point3D(0, 2, 0)};

    ASSERT_TRUE(plane.IntersecTypeWithTriangle(t2) == VERTEX_ONLY);
}

TEST(GEOM_TESTs, TriangAndPlaneIntersect3) {
    Plane plane {Vector3D(0, 1, 0), 0};
    Triangle3D t3 {Point3D(0, -1, 1), Point3D(0, 1, 0), Point3D(0, 2, 0)};

    ASSERT_TRUE(plane.IntersecTypeWithTriangle(t3) == GENERAL_INTERSECTION);
}

TEST(GEOM_TESTs, TriangAndPlaneIntersect4) {
    Plane plane {Vector3D(0, 1, 0), 0};
    Triangle3D t4 {Point3D(0, 2, 0), Point3D(0, 1, 0), Point3D(-1, 1, 0)};

    ASSERT_TRUE(plane.IntersecTypeWithTriangle(t4) == NO_INTERSECTION);
}

TEST(GEOM_TESTs, TriangAndPlaneIntersect5) {
    Plane plane {Vector3D(0, 1, 0), 0};
    Triangle3D t5 {Point3D(0, 0, 0), Point3D(-1, 0, 0), Point3D(0, 0, 1)};

    ASSERT_TRUE(plane.IntersecTypeWithTriangle(t5) == TRIANGLE_ON_PLANE);
}

TEST(GEOM_TESTs, IntervalsGeneration1) {
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

TEST(GEOM_TESTs, IntervalsOverlapping1) {

    Interval interval0 {0, 0.5};
    Interval interval1 {0.25, 1};

    ASSERT_TRUE(interval0.overlapWith(interval1));
}

TEST(GEOM_TESTs, IntervalsOverlapping2) {

    Interval interval0 {0.25, 1};
    Interval interval1 {0, 0.5};

    ASSERT_TRUE(interval0.overlapWith(interval1));
}

TEST(GEOM_TESTs, IntervalsOverlapping3) {

    Interval interval0 {0.25, 1};
    Interval interval1 {3, 5};

    ASSERT_FALSE(interval0.overlapWith(interval1));
}

TEST(GEOM_TESTs, Triangle2DhasPoint2D) {
    Triangle2D tr1 {Point2D(0, 1), Point2D(1, 0), Point2D(0, 0)};
    Point2D point1 {0.1, 0.1};
    Point2D point2 {1, 1};

    ASSERT_TRUE(tr1.hasPointInside(point1));
    ASSERT_FALSE(tr1.hasPointInside(point2));
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