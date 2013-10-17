#include "gtest/gtest.h"
#include "../base/Transformation.h"
#include "../base/Vector.h"
#include "../base/Point.h"

class TransformationTest : public ::testing::Test {
};

TEST_F(TransformationTest, OverloadTest) {
  Transformation t;
  Vector v(1, 2, 3);
  Point p(1, 2, 3);
  t * v;
  t * p;
}
