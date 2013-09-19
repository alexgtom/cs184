#include "gtest/gtest.h"

// override the main function in the included file below
#define _MAIN  
#include "as1/example_01.cpp"

// The fixture for testing class Foo.
class FooTest : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if its body
  // is empty.

  FooTest() {
    // You can do set-up work for each test here.
  }

  virtual ~FooTest() {
    // You can do clean-up work that doesn't throw exceptions here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  virtual void SetUp() {
    // Code here will be called immediately after the constructor (right
    // before each test).
  }

  virtual void TearDown() {
    // Code here will be called immediately after each test (right
    // before the destructor).
  }

  // Objects declared here can be used by all tests in the test case for Foo.
};

// Tests that the Foo::Bar() method does Abc.
TEST_F(FooTest, MethodBarDoesAbc) {
  EXPECT_EQ(0, 0);
}

// Tests that Foo does Xyz.
TEST_F(FooTest, DoesXyz) {
  // Exercises the Xyz feature of Foo.
}


// ------------------------------------------------------------
// PixelOpsTest
// ------------------------------------------------------------

class PixelOpsTest : public ::testing::Test {
};

// Tests that the Foo::Bar() method does Abc.
TEST_F(PixelOpsTest, ConstructorTest) {
  PixelOps* p = new PixelOps(1, 2, 1.0f, 2.0f, 3.0f);
  EXPECT_EQ(p->x, 1);
  EXPECT_EQ(p->y, 2);
  EXPECT_EQ(p->r, 1.0f);
  EXPECT_EQ(p->g, 2.0f);
  EXPECT_EQ(p->b, 3.0f);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
