#include "gtest/gtest.h"
#include "../base/Parser.h"
#include "../base/BezierPatch.h"
#include <glm/glm.hpp>


using namespace glm;

class bezcurveinterpTest : public ::testing::Test {
};

TEST_F(bezcurveinterpTest, bezcurveinterp) {

  BezierPatch tester = BezierPatch();

  vec3 first = vec3(0, 0, 0);
  vec3 second = vec3(1, 0, 0);
  vec3 third = vec3(2, 0, 0);
  vec3 fourth = vec3(3, 0, 0);
  vec3 curve []= {first, second, third, fourth};
  float u = 0.5f;

  PointDeriv curr = tester.bezcurveinterp(curve, u);

  vec3 expected = vec3(1.5, 0, 0);
  vec3 expected_deriv = vec3(3, 0, 0);
  EXPECT_EQ(expected, curr.point);
  EXPECT_EQ(expected_deriv, curr.derivative);
  
}
