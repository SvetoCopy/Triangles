#include <gtest/gtest.h>
#include "Triangle.h"
#include "Vector.h"
#include "Plane.h"
#include "GeomFunctions.h"
#include <cmath>

TEST(GEOM_TESTs, TriangleDegenerate1) {
    Triangle t {Point(1, 0, 1), Point(1, 0, -1), Point(0, 1, 1)};
    ASSERT_FALSE(t.isDegenerate());
}

TEST(GEOM_TESTs, TriangleDegenerate2) {
    Triangle t {Point(0, 0, 1), Point(0, 0, -1), Point(0, 0, 2)};
    ASSERT_TRUE(t.isDegenerate());
}

TEST(GEOM_TESTs, VectorCross1) {
    Vector vec1 {1, 0, 1};
    Vector vec2 {2, 1, -1};

    Vector vec3 {-1, 3, 1};
    
    ASSERT_TRUE(vec1 * vec2 == vec3);
}

TEST(GEOM_TESTs, VectorCross2) {
    Vector vec1 {0, 2, 0};
    Vector vec2 {1, 0, 1};

    Vector vec3 {2, 0, -2};
    
    ASSERT_TRUE(vec1 * vec2 == vec3);
}

TEST(GEOM_TESTs, VectorCross3) {
    Vector vec1 {3, -3, 1};
    Vector vec2 {4, 9, 2};

    Vector vec3 {-15, -2, 39};
    
    ASSERT_TRUE(vec1 * vec2 == vec3);
}

TEST(GEOM_TESTs, VectorCross4) {
    Vector vec1 {5, 0, 0};
    Vector vec2 {0, 5, 0};

    Vector vec3 {0, 0, 25};
    
    ASSERT_TRUE(vec1 * vec2 == vec3);
}

TEST(GEOM_TESTs, VectorCross5) {
    Vector vec1 {-1, -2, -3};
    Vector vec2 {4, 5, 6};

    Vector vec3 {3, -6, 3};
    
    ASSERT_TRUE(vec1 * vec2 == vec3);
}

TEST(GEOM_TESTs, VectorDot1) {
    Vector vec1 {1, 0, 1};
    Vector vec2 {2, 1, -1};
    
    ASSERT_TRUE(isEqual((vec1 & vec2), 1));
}

TEST(GEOM_TESTs, VectorDot2) {
    Vector vec1 {0, 2, 0};
    Vector vec2 {1, 0, 1};

    ASSERT_TRUE(isEqual((vec1 & vec2), 0));
}

TEST(GEOM_TESTs, VectorDot3) {
    Vector vec1 {3, -3, 1};
    Vector vec2 {4, 9, 2};

    ASSERT_TRUE(isEqual((vec1 & vec2), -13));
}

TEST(GEOM_TESTs, VectorDot4) {
    Vector vec1 {5, 0, 0};
    Vector vec2 {0, 5, 0};

    ASSERT_TRUE(isEqual((vec1 & vec2), 0));
}

TEST(GEOM_TESTs, VectorDot5) {
    Vector vec1 {-1, -2, -3};
    Vector vec2 {4, 5, 6};

    ASSERT_TRUE(isEqual((vec1 & vec2), -32));
}

TEST(GEOM_TESTs, PlaneEqFromPoints1) {
    Point p1 {1, 2, 1};
    Point p2 {-2, 3, 1};
    Point p3 {4, -5, 0};

    Plane plane {p1, p2 ,p3};
    
    ASSERT_TRUE(isEqual(plane.dist, -11) == true);
    ASSERT_TRUE(plane.norm == Vector(-1, -3, 18) || plane.norm ==  (-Vector(-1, -3, 18)) );
}

TEST(GEOM_TESTs, PlaneEqFromPoints2) {
    Point p1 {1, -4, 3};
    Point p2 {9, 1, 0};
    Point p3 {0, 0, -1};

    Plane plane {p1, p2 ,p3};
    std::cout << plane.dist;
    ASSERT_TRUE(isEqual(plane.dist, 37) == true);
    ASSERT_TRUE(plane.norm == Vector(-8, 35, 37) || plane.norm ==  (-Vector(-8, 35, 37)));
}

TEST(GEOM_TESTs, VectorModule1) {
    Vector vec {1, 0, 1};
    
    ASSERT_TRUE(isEqual(vec.getModule(), std::pow(2, 0.5)) == true);
}

TEST(GEOM_TESTs, VectorModule2) {
    Vector vec {2, 0, 0};
    
    ASSERT_TRUE(isEqual(vec.getModule(), 2) == true);
}

TEST(GEOM_TESTs, pointToPlaneDistance1) {
    Point point {0, 3, 6};
    Plane plane {Vector(2, 4, -4), -6};
    
    ASSERT_TRUE(isEqual(pointToPlaneDistance(point, plane), -3) == true);
}

TEST(GEOM_TESTs, PlaneEqual1) {
    Plane plane1 {Vector(4, 8, -8), -12};
    Plane plane2 {Vector(2, 4, -4), -6};
    
    ASSERT_TRUE(plane1 == plane2);
}

TEST(GEOM_TESTs, getPlanesInterLine1) {
    Plane plane1 {Vector(4, 8, -8), -12};
    Plane plane2 {Vector(2, 4, -2), -6};

    Line res {Point(0, 1.5, 0), Vector(16, -8, 0)};
    Line expected = getPlanesInterLine(plane1, plane2);

    ASSERT_TRUE(expected.havePoint(Point(0, 1.5, 0)) == true);
    ASSERT_TRUE(expected.havePoint(res.getPointByParameter(4)) == true);
    ASSERT_TRUE(expected.havePoint(res.getPointByParameter(5)) == true);
}

TEST(GEOM_TESTs, ColleniarVectors1) {
    Vector vec1 {1, 2 ,5};
    Vector vec2 {2, 4, 10};

    ASSERT_TRUE(vec2.colleniarWith(vec1) == true);
}

TEST(GEOM_TESTs, ColleniarVectors2) {
    Vector vec1 {0, 0, 0};
    Vector vec2 {0, 0, 0};

    ASSERT_TRUE(vec2.colleniarWith(vec1) == true);
}

TEST(GEOM_TESTs, PointInLine1) {
    Line line {Point(0, 1.5, 0), Vector(16, -8, 0)};
    Point p {Point(0, 1.5, 0) + (Vector(16, -8, 0) * 3).vec_end};

    ASSERT_TRUE(line.havePoint(p) == true);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}