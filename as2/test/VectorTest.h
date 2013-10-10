#include "gtest/gtest.h"
#include "../base/Vector.h"

// ------------------------------------------------------------
// Vector Operations Test
// ------------------------------------------------------------

class VectorTest : public ::testing::Test {
};

TEST_F(VectorTest, Subtraction) {
  Vector v(1, 2, 3);
  EXPECT_EQ(v-v, Vector());
}

TEST_F(VectorTest, DotProduct) {
  Vector v(1, 2, 3);
  EXPECT_FLOAT_EQ(v.dot(v), 14);
}

TEST_F(VectorTest, CrossProduct) {
  Vector v1(1, 2, 3);
  EXPECT_EQ(v1.cross(v1), Vector(0, 0, 0));

  Vector v2(1, 1, 1);
  EXPECT_EQ(v2.cross(Vector(1, 2, 1)), Vector(-1, 0, 1));
}
