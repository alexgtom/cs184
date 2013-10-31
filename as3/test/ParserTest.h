#include "gtest/gtest.h"
#include "../base/Parser.h"

class ParserTest : public ::testing::Test {
};

TEST_F(ParserTest, Parse) {
  Parser p;
  vector<BezierPatch> patch_list = p.readFile("../input/test.bez");
  vector<vec3> points1;
  vector<vec3> points0;

  points0.push_back(vec3(0.00, 0.00, 0.00));
  points0.push_back(vec3(0.33, 0.00, 0.00));
  points0.push_back(vec3(0.66, 0.00, 0.00));
  points0.push_back(vec3(1.00, 0.00, 0.00));
  points0.push_back(vec3(0.00, 0.33, 0.00));
  points0.push_back(vec3(0.33, 0.33, 0.00));
  points0.push_back(vec3(0.66, 0.33, 0.00));
  points0.push_back(vec3(1.00, 0.33, 0.00));
  points0.push_back(vec3(0.00, 0.66, 0.00));
  points0.push_back(vec3(0.33, 0.66, 0.00));
  points0.push_back(vec3(0.66, 0.66, 0.00));
  points0.push_back(vec3(1.00, 0.66, 0.00));
  points0.push_back(vec3(0.00, 1.00, 0.00));
  points0.push_back(vec3(0.33, 1.00, 0.00));
  points0.push_back(vec3(0.66, 1.00, 0.00));
  points0.push_back(vec3(1.00, 1.00, 0.00));

  points1.push_back(vec3(0.00, 0.00, 0.00));
  points1.push_back(vec3(0.33, 0.00, 2.00));
  points1.push_back(vec3(0.66, 0.00, 2.00));
  points1.push_back(vec3(1.00, 0.00, 0.00));
  points1.push_back(vec3(0.00, 0.33, 0.00));
  points1.push_back(vec3(0.33, 0.33, 2.00));
  points1.push_back(vec3(0.66, 0.33, 2.00));
  points1.push_back(vec3(1.00, 0.33, 0.00));
  points1.push_back(vec3(0.00, 0.66, 0.00));
  points1.push_back(vec3(0.33, 0.66, 2.00));
  points1.push_back(vec3(0.66, 0.66, 2.00));
  points1.push_back(vec3(1.00, 0.66, 0.00));
  points1.push_back(vec3(0.00, 1.00, 0.00));
  points1.push_back(vec3(0.33, 1.00, 2.00));
  points1.push_back(vec3(0.66, 1.00, 2.00));
  points1.push_back(vec3(1.00, 1.00, 0.00));
  
  EXPECT_EQ(points0, patch_list[0].points);
  EXPECT_EQ(points1, patch_list[1].points);
}
