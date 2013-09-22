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
// ParseArgsTest
// ------------------------------------------------------------

class ParseArgsTest : public ::testing::Test {
};

TEST_F(ParseArgsTest, kaTest) {
  char *args[5] = {"./as0", "-ka", "0.0", "0.5", "1.0"};
  parseArgs(5, args);
  EXPECT_EQ(0.0f, ka_r);
  EXPECT_EQ(0.5f, ka_g);
  EXPECT_EQ(1.0f, ka_b);
}

TEST_F(ParseArgsTest, kdTest) {
  char *args[5] = {"./as0", "-kd", "0.0", "0.5", "1.0"};
  parseArgs(5, args);
  EXPECT_EQ(0.0f, kd_r);
  EXPECT_EQ(0.5f, kd_g);
  EXPECT_EQ(1.0f, kd_b);
}

TEST_F(ParseArgsTest, ksTest) {
  char *args[5] = {"./as0", "-ks", "0.0", "0.5", "1.0"};
  parseArgs(5, args);
  EXPECT_EQ(0.0f, ks_r);
  EXPECT_EQ(0.5f, ks_g);
  EXPECT_EQ(1.0f, ks_b);
}

TEST_F(ParseArgsTest, spTest) {
  char *args[3] = {"./as0", "-sp", "1.0"};
  parseArgs(3, args);
  EXPECT_EQ(1.0f, sp_v);
}

TEST_F(ParseArgsTest, plTest) {
  char *args[8] = {"./as0", "-pl", "0.0", "0.5", "1.0", "100", "200", "255"};
  parseArgs(8, args);
  EXPECT_EQ(0.0f, pl_x.at(0));
  EXPECT_EQ(0.5f, pl_y.at(0));
  EXPECT_EQ(1.0f, pl_z.at(0));
  EXPECT_EQ(100.0f, pl_r.at(0));
  EXPECT_EQ(200.0f, pl_g.at(0));
  EXPECT_EQ(255.0f, pl_b.at(0));
}

TEST_F(ParseArgsTest, plMultipleTest) {
  char *args[15] = {"./as0", 
    "-pl", "0.0", "0.5", "1.0", "100", "200", "255",
    "-pl", "0.0", "0.5", "1.0", "100", "200", "255"
  };
  parseArgs(15, args);
  EXPECT_EQ(0.0f, pl_x.at(0));
  EXPECT_EQ(0.5f, pl_y.at(0));
  EXPECT_EQ(1.0f, pl_z.at(0));
  EXPECT_EQ(100.0f, pl_r.at(0));
  EXPECT_EQ(200.0f, pl_g.at(0));
  EXPECT_EQ(255.0f, pl_b.at(0));

  EXPECT_EQ(0.0f, pl_x.at(1));
  EXPECT_EQ(0.5f, pl_y.at(1));
  EXPECT_EQ(1.0f, pl_z.at(1));
  EXPECT_EQ(100.0f, pl_r.at(1));
  EXPECT_EQ(200.0f, pl_g.at(1));
  EXPECT_EQ(255.0f, pl_b.at(1));
}

TEST_F(ParseArgsTest, dlTest) {
  char *args[8] = {"./as0", "-dl", "0.0", "0.5", "1.0", "100", "200", "255"};
  parseArgs(8, args);
  EXPECT_EQ(0.0f, dl_x.at(0));
  EXPECT_EQ(0.5f, dl_y.at(0));
  EXPECT_EQ(1.0f, dl_z.at(0));
  EXPECT_EQ(100.0f, dl_r.at(0));
  EXPECT_EQ(200.0f, dl_g.at(0));
  EXPECT_EQ(255.0f, dl_b.at(0));
}

TEST_F(ParseArgsTest, dlMultipleTest) {
  char *args[15] = {"./as0", 
    "-dl", "0.0", "0.5", "1.0", "100", "200", "255",
    "-dl", "0.0", "0.5", "1.0", "100", "200", "255"
  };
  parseArgs(15, args);
  EXPECT_EQ(0.0f, dl_x.at(0));
  EXPECT_EQ(0.5f, dl_y.at(0));
  EXPECT_EQ(1.0f, dl_z.at(0));
  EXPECT_EQ(100.0f, dl_r.at(0));
  EXPECT_EQ(200.0f, dl_g.at(0));
  EXPECT_EQ(255.0f, dl_b.at(0));

  EXPECT_EQ(0.0f, dl_x.at(1));
  EXPECT_EQ(0.5f, dl_y.at(1));
  EXPECT_EQ(1.0f, dl_z.at(1));
  EXPECT_EQ(100.0f, dl_r.at(1));
  EXPECT_EQ(200.0f, dl_g.at(1));
  EXPECT_EQ(255.0f, dl_b.at(1));
}

TEST_F(ParseArgsTest, MultiArgTest) {
  char *args[17] = {"./as0", 
    "-dl", "0.0", "0.5", "1.0", "100", "200", "255",
    "-pl", "0.0", "0.5", "1.0", "100", "200", "255",
    "-sp", "1.0"
  };
  parseArgs(17, args);
  EXPECT_EQ(0.0f, dl_x.at(0));
  EXPECT_EQ(0.5f, dl_y.at(0));
  EXPECT_EQ(1.0f, dl_z.at(0));
  EXPECT_EQ(100.0f, dl_r.at(0));
  EXPECT_EQ(200.0f, dl_g.at(0));
  EXPECT_EQ(255.0f, dl_b.at(0));

  EXPECT_EQ(0.0f, pl_x.at(1));
  EXPECT_EQ(0.5f, pl_y.at(1));
  EXPECT_EQ(1.0f, pl_z.at(1));
  EXPECT_EQ(100.0f, pl_r.at(1));
  EXPECT_EQ(200.0f, pl_g.at(1));
  EXPECT_EQ(255.0f, pl_b.at(1));

  EXPECT_EQ(1.0f, sp_v);
}

// ------------------------------------------------------------
// PixelOpsTest
// ------------------------------------------------------------

class PixelOpsTest : public ::testing::Test {
};

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
