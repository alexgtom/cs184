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

