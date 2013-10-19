#include <math.h>

#include "gtest/gtest.h"
#include "../base/Light.h"


class LightTest : public ::testing::Test {
};

TEST_F(LightTest, PointLight) {
  PointLight l(2, 2, 2, 1, 1, 1);
  Ray r;
  Color c;
  Point light_start(1, 1, 1);
  LocalGeo localgeo = LocalGeo(light_start, Normal(1, 1, 1));
  l.generateLightRay(localgeo, &r, &c);
  EXPECT_EQ(Ray(light_start, Vector(1, 1, 1), 0.1, (light_start - l.loc).mag()), r);
}

TEST_F(LightTest, DirectionalLight) {
  DirectionalLight l(2, 2, 2, 1, 1, 1);
  Ray r;
  Color c;
  Point light_start(1, 1, 1);
  LocalGeo localgeo = LocalGeo(light_start, Normal(1, 1, 1));
  l.generateLightRay(localgeo, &r, &c);
  EXPECT_EQ(Ray(light_start, Vector(-2, -2, -2), LIGHT_OFFSET, INFINITY), r);
}

