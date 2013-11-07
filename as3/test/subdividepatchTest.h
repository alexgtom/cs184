#include "gtest/gtest.h"
#include "../base/Parser.h"

class subdividepatchTest : public ::testing::Test {
};


TEST_F(subdividepatchTest, subdividepatch) { 
  vector<vec3> points0;

    points0.push_back(vec3(0.00, 0.00, 0.00));
    points0.push_back(vec3(1, 0.00, 0.00));
    points0.push_back(vec3(2, 0.00, 0.00));
    points0.push_back(vec3(3, 0.00, 0.00));
    points0.push_back(vec3(0.00, 1, 0.00));
    points0.push_back(vec3(1, 1, 0.00));
    points0.push_back(vec3(2, 1, 0.00));
    points0.push_back(vec3(3, 1, 0.00));
    points0.push_back(vec3(0.00, 2, 0.00));
    points0.push_back(vec3(1, 2, 0.00));
    points0.push_back(vec3(2, 2, 0.00));
    points0.push_back(vec3(3, 2, 0.00));
    points0.push_back(vec3(0.00, 3, 0.00));
    points0.push_back(vec3(1, 3, 0.00));
    points0.push_back(vec3(2, 3, 0.00));
    points0.push_back(vec3(3, 3, 0.00));

    BezierPatch test = BezierPatch(points0);

  test.subdividepatch();
  
}
  
