#include <gtest/gtest.h>
#include "Triangle.h"
#include "Vector.h"
#include "Plane.h"
#include "GeomFunctions.h"
#include <cmath>
#include "Intervals.h"
#include "OctTree.h"

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}