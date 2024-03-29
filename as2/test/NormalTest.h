#include "gtest/gtest.h"
#include "../base/Normal.h"

// ------------------------------------------------------------
// Normal Operations Test
// ------------------------------------------------------------

class NormalTest : public ::testing::Test {
};

TEST_F(NormalTest, Subtraction) {
  Normal v(1, 2, 3);
  EXPECT_EQ(v-v, Normal());
}

TEST_F(NormalTest, DotProduct) {
  Normal v(3, 0, 0);
  EXPECT_FLOAT_EQ(v.dot(v), 9);
}
