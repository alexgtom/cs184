#include "gtest/gtest.h"
#include "../base/Point.h"

class PointTest : public ::testing::Test {
};

TEST_F(PointTest, Subtraction) {
  Vector v(1, 2, 3);
  Point p(1, 2, 3);
  EXPECT_EQ(p-v, Point());
}

TEST_F(PointTest, Addition) {
  Point p(0, 0, 0);
  Vector v(1, 1, 1);

  EXPECT_EQ(p+v, Point(1, 1, 1));
}

TEST_F(PointTest, Assignment) {
  Point p(0, 0, 0);
  p = Point(1, 1, 1);

  EXPECT_EQ(p, Point(1, 1, 1));
}

TEST_F(PointTest, FloatConstructor) {
  Point p(0, 0, 0);
  EXPECT_EQ(p, Point(0, 0, 0));
}

TEST_F(PointTest, VectorConstructor) {
  Point p(Vector(0, 0, 0));
  EXPECT_EQ(p, Point(0, 0, 0));
}

TEST_F(PointTest, PointConstructor) {
  Point p(Point(0, 0, 0));
  EXPECT_EQ(p, Point(0, 0, 0));
}

