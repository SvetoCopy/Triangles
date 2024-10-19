#include <gtest/gtest.h>
#include "Triangle.h"
#include "Vector.h"
#include "Plane.h"
#include "GeomFunctions.h"
#include <cmath>
#include "Intervals.h"

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
    Triangle3D tr1 {Point3D(0, -0.5, 0), Point3D(0, 0.5, 0), Point3D(0, 0, 0.5)};
    Triangle3D tr2 {Point3D(0.25, 0, 0.25), Point3D(-0.25, 0, 0.25), Point3D(0, 0, 1)};

    Plane plane1 {tr1.v0, tr1.v1, tr1.v2};
    Plane plane2 {tr2.v0, tr2.v1, tr2.v2};

    Line3D intersect_line = getPlanesInterLine(plane1, plane2);
    intersect_line.dist = Vector3D(0,0 ,1);
    Interval intervals {intersect_line, tr1, tr2};

    std::cout << intervals.t0_0 << ' ' << intervals.t0_1 << ' ' << intervals.t1_0 << ' ' << intervals.t1_1 << ' ';

    ASSERT_TRUE(intervals.t0_0 == 0);
    ASSERT_TRUE(intervals.t0_1 == 0.25);
    ASSERT_TRUE(intervals.t1_0 == 0.25);
    ASSERT_TRUE(intervals.t1_1 == 1);
}

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