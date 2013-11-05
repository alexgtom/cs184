/*
 * This file runs all the tests. Make sure you include the test you want to run
 * below
 */
#include "gtest/gtest.h"

// Tests 
#include "FooTest.h"
#include "VectorTest.h"
#include "SamplerTest.h"
#include "NormalTest.h"
#include "TransformationTest.h"
#include "SphereTest.h"
#include "TriangleTest.h"
#include "PointTest.h"
#include "AggregatePrimitiveTest.h"
#include "LightTest.h"
#include "CameraTest.h"
#include "PixelOpsTest.h"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
