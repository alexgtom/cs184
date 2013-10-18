#include "gtest/gtest.h"
#include "../base/Transformation.h"
#include "../base/Vector.h"
#include "../base/Point.h"

class TransformationTest : public ::testing::Test {
};

//
// Creates a matrix that translates objects to different coordinates
Matrix4f translate(float x, float y, float z) {
  Matrix4f m = MatrixXf::Identity(4, 4);
  m(0, 3) = x;
  m(1, 3) = y;
  m(2, 3) = z;
  return m;
}

Matrix4f scale(float x, float y, float z) {
  Matrix4f m = MatrixXf::Identity(4, 4);
  m(0, 3) = 1;
  m(1, 3) = 1;
  m(2, 3) = 1;

  m(0, 0) = z;
  m(1, 1) = y;
  m(2, 2) = z;
  return m;
}

TEST_F(TransformationTest, Point) {
  Transformation t(translate(2, 2, 2));
  EXPECT_EQ(Point(3, 4, 5), t * Point(1, 2, 3));
  EXPECT_EQ(Point(1, 2, 3), t * Point(0, 2, 4, 2));
}

TEST_F(TransformationTest, Vector) {
  Transformation t(scale(2, 2, 2));
  EXPECT_EQ(Vector(2, 4, 6), t * Vector(1, 2, 3));
}

TEST_F(TransformationTest, Normal) {
  Transformation t(scale(2, 2, 2));
  EXPECT_EQ(Normal(0.5, 1, 1.5), t * Normal(1, 2, 3));
}

TEST_F(TransformationTest, Ray) {
  Transformation t(scale(2, 2, 2));
  Ray r = t * Ray(Point(1, 2, 3), Vector(1, 1, 1), 0.0f, 1.0f);

  EXPECT_EQ(Vector(1, 1, 1).norm(), r.dir);
  EXPECT_EQ(Point(3, 5, 7), r.pos);
}

TEST_F(TransformationTest, LocalGeo) {
  Transformation t(scale(2, 2, 2));
  LocalGeo l = t * LocalGeo(Point(1, 2, 3), Normal(1, 2, 3));

  EXPECT_EQ(Normal(0.5, 1, 1.5), l.normal);
  EXPECT_EQ(Point(3, 5, 7), l.pos);
}


