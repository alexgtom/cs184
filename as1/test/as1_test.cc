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
  protected:
    virtual void SetUp() {
      pl_x.clear();
      pl_y.clear();
      pl_z.clear();
      pl_r.clear();
      pl_g.clear();
      pl_b.clear();

      dl_x.clear();
      dl_y.clear();
      dl_z.clear();
      dl_r.clear();
      dl_g.clear();
      dl_b.clear();
    }

};

TEST_F(ParseArgsTest, kaTest) {
  const char *args[5] = {"./as0", "-ka", "0.0", "0.5", "1.0"};
  parseArgs(5, const_cast<char **>(args));
  EXPECT_EQ(0.0f, ka_r);
  EXPECT_EQ(0.5f, ka_g);
  EXPECT_EQ(1.0f, ka_b);
}

TEST_F(ParseArgsTest, kdTest) {
  const char *args[5] = {"./as0", "-kd", "0.0", "0.5", "1.0"};
  parseArgs(5, const_cast<char **>(args));
  EXPECT_EQ(0.0f, kd_r);
  EXPECT_EQ(0.5f, kd_g);
  EXPECT_EQ(1.0f, kd_b);
}

TEST_F(ParseArgsTest, ksTest) {
  const char *args[5] = {"./as0", "-ks", "0.0", "0.5", "1.0"};
  parseArgs(5, const_cast<char **>(args));
  EXPECT_EQ(0.0f, ks_r);
  EXPECT_EQ(0.5f, ks_g);
  EXPECT_EQ(1.0f, ks_b);
}

TEST_F(ParseArgsTest, spTest) {
  const char *args[3] = {"./as0", "-sp", "1.0"};
  parseArgs(3, const_cast<char **>(args));
  EXPECT_EQ(1.0f, sp_v);
}

TEST_F(ParseArgsTest, plTest) {
  const char *args[8] = {"./as0", "-pl", "0.0", "0.5", "1.0", "100", "200", "255"};
  parseArgs(8, const_cast<char **>(args));
  EXPECT_EQ(0.0f, pl_x.at(0));
  EXPECT_EQ(0.5f, pl_y.at(0));
  EXPECT_EQ(1.0f, pl_z.at(0));
  EXPECT_EQ(100.0f, pl_r.at(0));
  EXPECT_EQ(200.0f, pl_g.at(0));
  EXPECT_EQ(255.0f, pl_b.at(0));
}

TEST_F(ParseArgsTest, plMultipleTest) {
  const char *args[15] = {"./as0", 
    "-pl", "0.0", "0.5", "1.0", "100", "200", "255",
    "-pl", "0.0", "0.5", "1.0", "100", "200", "255"
  };
  parseArgs(15, const_cast<char **>(args));
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
  const char *args[8] = {"./as0", "-dl", "0.0", "0.5", "1.0", "100", "200", "255"};
  parseArgs(8, const_cast<char **>(args));
  EXPECT_EQ(0.0f, dl_x.at(0));
  EXPECT_EQ(0.5f, dl_y.at(0));
  EXPECT_EQ(1.0f, dl_z.at(0));
  EXPECT_EQ(100.0f, dl_r.at(0));
  EXPECT_EQ(200.0f, dl_g.at(0));
  EXPECT_EQ(255.0f, dl_b.at(0));
}

TEST_F(ParseArgsTest, dlMultipleTest) {
  const char *args[15] = {"./as0", 
    "-dl", "0.0", "0.5", "1.0", "100", "200", "255",
    "-dl", "0.0", "0.5", "1.0", "100", "200", "255"
  };
  parseArgs(15, const_cast<char **>(args));
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
  const char *args[17] = {"./as0", 
    "-dl", "0.0", "0.5", "1.0", "100", "200", "255",
    "-pl", "0.0", "0.5", "1.0", "100", "200", "255",
    "-sp", "1.0"
  };
  parseArgs(17, const_cast<char **>(args));
  EXPECT_EQ(0.0f, dl_x.at(0));
  EXPECT_EQ(0.5f, dl_y.at(0));
  EXPECT_EQ(1.0f, dl_z.at(0));
  EXPECT_EQ(100.0f, dl_r.at(0));
  EXPECT_EQ(200.0f, dl_g.at(0));
  EXPECT_EQ(255.0f, dl_b.at(0));

  EXPECT_EQ(0.0f, pl_x.at(0));
  EXPECT_EQ(0.5f, pl_y.at(0));
  EXPECT_EQ(1.0f, pl_z.at(0));
  EXPECT_EQ(100.0f, pl_r.at(0));
  EXPECT_EQ(200.0f, pl_g.at(0));
  EXPECT_EQ(255.0f, pl_b.at(0));

  EXPECT_EQ(1.0f, sp_v);
}

TEST_F(ParseArgsTest, MultiArgTest2) {
  const char *args[16] = {"./as1",
    "-ka", "0.9", "0.9", "1.0", 
    "-kd", "0.2", "0.2", "0.2", 
    "-pl", "1.0", "1.0", "1.0", "255.0", "255.0", "255.0"
  };
  parseArgs(16, const_cast<char **>(args));
  EXPECT_EQ(0.9f, ka_r);
  EXPECT_EQ(0.9f, ka_g);
  EXPECT_EQ(1.0f, ka_b);

  EXPECT_EQ(0.2f, kd_r);
  EXPECT_EQ(0.2f, kd_g);
  EXPECT_EQ(0.2f, kd_b);

  EXPECT_EQ(1.0f, pl_x.at(0));
  EXPECT_EQ(1.0f, pl_y.at(0));
  EXPECT_EQ(1.0f, pl_z.at(0));
  EXPECT_EQ(255.0f, pl_r.at(0));
  EXPECT_EQ(255.0f, pl_g.at(0));
  EXPECT_EQ(255.0f, pl_b.at(0));
}
// ------------------------------------------------------------
// Math Operations Test
// ------------------------------------------------------------

class MathOpsTest : public ::testing::Test {
};

TEST_F(MathOpsTest, NormalizeVectorTest) {
  float x = 1.0f;
  float y = 2.0f;
  float z = 3.0f;
  normalize_vector(x, y, z);
  EXPECT_FLOAT_EQ(0.26726124f, x);
  EXPECT_FLOAT_EQ(0.53452247f, y);
  EXPECT_FLOAT_EQ(0.80178368f, z);
}

TEST_F(MathOpsTest, MaxNumFromVector) {
  vector<float> v;
  v.push_back(1.0f);
  v.push_back(2.0f);
  v.push_back(3.0f);

  EXPECT_FLOAT_EQ(3.0f, max_num_from_vector(v));
}

// ------------------------------------------------------------
// PixelOpsTest
// ------------------------------------------------------------
class PixelOpsTest : public ::testing::Test {
};

TEST_F(PixelOpsTest, DiffuseTestDefault) {
  kd_r = kd_g = kd_b = 0.0f;
  PixelOps po(1.0f, 0.0f, 0.0f);
  po.diffuseComponent(0.0f, 1.0f, 0.0f, 1.0, 0.0, 0.0);

  // assert all zero arguments work
  EXPECT_FLOAT_EQ(po.r, 0.0f);
  EXPECT_FLOAT_EQ(po.g, 0.0f);
  EXPECT_FLOAT_EQ(po.b, 0.0f);
}

TEST_F(PixelOpsTest, DiffuseTest) {
  // real values
  kd_r = 1.0f;
  kd_g = 0.0f;
  kd_b = 0.0f;

  PixelOps po(1.0f, 0.0f, 0.0f);
  po.diffuseComponent(-2.0f, 0.0f, 0.0f, 1.0, 0.0, 0.0);

  EXPECT_FLOAT_EQ(1.0f, po.r);
  EXPECT_FLOAT_EQ(0.0f, po.g);
  EXPECT_FLOAT_EQ(0.0f, po.b);
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
