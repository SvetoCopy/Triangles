#include <gtest/gtest.h>
#include "Triangle.h"
#include "Vector.h"
#include "Plane.h"
#include "GeomFunctions.h"
#include <cmath>
#include "Intervals.h"
#include "OctTree.h"

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

TEST(GEOM_TESTs, VectorModule1) {
    Vector3D vec {1, 0, 1};
    
    ASSERT_TRUE(isEqual(vec.getModule(), std::pow(2, 0.5)) == true);
}

TEST(GEOM_TESTs, VectorModule2) {
    Vector3D vec {2, 0, 0};
    
    ASSERT_TRUE(isEqual(vec.getModule(), 2) == true);
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

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}