#include "gtest/gtest.h"
#include "../base/Camera.h"
#include "../base/Sampler.h"
#include "../base/Sample.h"

class CameraTest : public ::testing::Test {
};

TEST_F(CameraTest, Subtraction) {
  Sampler sampler(100, 100);
  Camera c(Point(0, 0, 0), Point(0, 1, 0), Vector(0, 1, 1), 45);
  Ray r = c.generateRay(sampler, Sample(0, 0));
  EXPECT_EQ(Point(0, 0, 0), r.pos);
  EXPECT_FLOAT_EQ(-0.26138034, r.dir.x);
  EXPECT_FLOAT_EQ(0.929172, r.dir.y);
  EXPECT_FLOAT_EQ(-0.26138034, r.dir.z);
}

