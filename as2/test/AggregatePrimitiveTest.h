#include <Eigen/Dense>

#include "gtest/gtest.h"
#include "../base/AggregatePrimitive.h"
#include "../base/Intersection.h"
#include "../base/GeometricPrimitive.h"

using namespace Eigen;

class AggregatePrimitiveTest : public ::testing::Test {
};

// creates spheres of radius 1 at a location
GeometricPrimitive sphere_factory(float x, float y, float z) {
  Matrix4f mObjtoWorld = MatrixXf::Identity(4, 4);
  mObjtoWorld(0, 3) = x;
  mObjtoWorld(1, 3) = y;
  mObjtoWorld(2, 3) = z;

  Matrix4f mWorldToObj = MatrixXf::Identity(4, 4);
  mWorldToObj(0, 3) = -x;
  mWorldToObj(1, 3) = -y;
  mWorldToObj(2, 3) = -z;

  Transformation objToWorld(mObjtoWorld);
  Transformation worldToObj(mWorldToObj);
  return GeometricPrimitive(new Sphere(1.0f), objToWorld, worldToObj, NULL);
}

TEST_F(AggregatePrimitiveTest, Basic) {
  GeometricPrimitive s1 = sphere_factory(0, 0, 1);
  GeometricPrimitive s2 = sphere_factory(0, 0, 2);

  vector<Primitive*> list;
  // insert primitives in reverse order so that the closest one is
  // at the end of the list
  list.push_back(&s2);
  list.push_back(&s1);

  AggregatePrimitive ap(list);
  
  // create a ray and shoot it down the z coordinate
  Ray ray(Point(0, 0, 4), Vector(0, 0, -4), 0, 4);

  float thit;
  Intersection in;
  EXPECT_TRUE(ap.intersect(ray, &thit, &in));
  EXPECT_EQ(Point(0, 0, 3), in.local.pos);
  EXPECT_EQ(1.0f, thit);
}
