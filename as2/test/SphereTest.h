#include "gtest/gtest.h"
#include "../base/Shape.h"
#include "../base/Ray.h"
#include "../base/LocalGeo.h"
#include "../base/Normal.h"

class SphereTest : public ::testing::Test {
};

TEST_F(SphereTest, ValidIntersectTest) {
  // create a sphere with radius 1
  Sphere s(1.0f);

  // shoot a ray down the z-coordinate
  Ray r(Point(0, 0, 2), Vector(0, 0, -2), 0, 2);
  float thit;
  LocalGeo local;
  EXPECT_TRUE(s.intersect(r, &thit, &local));
  EXPECT_FLOAT_EQ(1.0f, thit);
  EXPECT_EQ(Point(0, 0, 1), local.pos);
  EXPECT_EQ(Normal(0, 0, 1), local.normal);
  EXPECT_TRUE(s.intersectP(r));
}

TEST_F(SphereTest, ThitTest1) {
  // create a sphere with radius 1
  Sphere s(1.0f);

  // shoot a ray down the z-coordinate
  Ray r(Point(0, 0, 10), Vector(0, 0, -10), 0, 10);
  float thit;
  LocalGeo local;
  EXPECT_TRUE(s.intersect(r, &thit, &local));
  EXPECT_FLOAT_EQ(9.0f, thit);
  EXPECT_EQ(Point(0, 0, 1), local.pos);
  EXPECT_EQ(Normal(0, 0, 1), local.normal);
  EXPECT_TRUE(s.intersectP(r));
}

TEST_F(SphereTest, ThitTest2) {
  // create a sphere with radius 1
  Sphere s(1.0f);

  // shoot a ray down the z-coordinate
  Ray r(Point(0, 0, 2), Vector(0, 0, -2), -1, 1);
  float thit;
  LocalGeo local;
  EXPECT_TRUE(s.intersect(r, &thit, &local));
  EXPECT_FLOAT_EQ(0.0f, thit);
  EXPECT_EQ(Point(0, 0, 1), local.pos);
  EXPECT_EQ(Normal(0, 0, 1), local.normal);
  EXPECT_TRUE(s.intersectP(r));
}

TEST_F(SphereTest, InvalidIntersectTest) {
  // create a sphere with radius 1
  Sphere s(1.0f);

  // shoot a ray that does not intersect the sphere
  Ray r(Point(0, 0, 2), Vector(0, 0, 1), 0, 2);
  float thit;
  LocalGeo local;
  EXPECT_FALSE(s.intersect(r, &thit, &local));
  EXPECT_FALSE(s.intersectP(r));
}
