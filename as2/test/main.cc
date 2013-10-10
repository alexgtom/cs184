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
#include "PointTest.h"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
