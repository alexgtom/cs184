#include "gtest/gtest.h"

// override the main function in the included file below
#include "../base/PixelOps.h"

// ------------------------------------------------------------
// PixelOpsTest
// ------------------------------------------------------------
class PixelOpsTest : public ::testing::Test {
};

TEST_F(PixelOpsTest, DiffuseTestDefault) {
  PixelOps po(Vector(0.0f, 1.0f, 0.0f));
  po.kd = Color(0.0f, 0.0f, 0.0f);
  po.diffuseComponent(Vector(0.0f, 1.0f, 0.0f), Color(1.0, 0.0, 0.0));

  // assert all zero arguments work
  EXPECT_EQ(po.c, Color(0.0f, 0.0f, 0.0f));
}

TEST_F(PixelOpsTest, DiffuseTest) {
  // real values

  PixelOps po(Vector(-2.0f, 0.0f, 0.0f));
  po.kd = Color(1.0f, 0.0f, 0.0f);
  po.diffuseComponent(Vector(-2.0f, 0.0f, 0.0f), Color(1.0, 0.0, 0.0));

  EXPECT_EQ(po.c, Color(1.0f, 0.0f, 0.0f));
}
