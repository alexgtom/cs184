#include "gtest/gtest.h"
#include "../base/Shape.h"
#include "../base/Ray.h"
#include "../base/LocalGeo.h"
#include "../base/Normal.h"
#include "../base/Point.h"

class TriangleTest : public ::testing::Test {
};

TEST_F(TriangleTest, ValidIntersectTest) {
  Triangle s(Point(0, 0, 0), Point(1, 0, 0), Point(0, 1, 0));

  // shoot a ray down the z-coordinate
  Ray r(Point(0, 0, 2), Vector(0, 0, -2), 0, 2);
  float thit;
  LocalGeo local;
  EXPECT_TRUE(s.intersect(r, &thit, &local));
  EXPECT_FLOAT_EQ(2.0f, thit);
  EXPECT_EQ(Point(0, 0, 0), local.pos);
  EXPECT_EQ(Normal(0, 0, 1), local.normal);
  EXPECT_TRUE(s.intersectP(r));
}

TEST_F(TriangleTest, ThitTest1) {
  Triangle s(Point(0, 0, 0), Point(1, 0, 0), Point(0, 1, 0));

  // shoot a ray down the z-coordinate
  Ray r(Point(0, 0, 2), Vector(0, 0, -2), -1, 1);
  float thit;
  LocalGeo local;
  EXPECT_TRUE(s.intersect(r, &thit, &local));
  EXPECT_FLOAT_EQ(1.0f, thit);
  EXPECT_EQ(Point(0, 0, 0), local.pos);
  EXPECT_EQ(Normal(0, 0, 1), local.normal);
  EXPECT_TRUE(s.intersectP(r));
}

TEST_F(TriangleTest, InvalidIntersectTest) {
  Triangle s(Point(0, 0, 0), Point(1, 0, 0), Point(0, 1, 0));

  // shoot a ray that does not intersect the sphere
  Ray r(Point(0, 0, 2), Vector(0, 1, 0), 0, 2);
  float thit;
  LocalGeo local;
  EXPECT_FALSE(s.intersect(r, &thit, &local));
  EXPECT_FALSE(s.intersectP(r));
}
