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
      pl_vector.clear();
      pl_color.clear();

      dl_vector.clear();
      dl_color.clear();
    }

};

TEST_F(ParseArgsTest, kaTest) {
  const char *args[5] = {"./as0", "-ka", "0.0", "0.5", "1.0"};
  parseArgs(5, const_cast<char **>(args));
  EXPECT_EQ(Color(0.0f, 0.5f, 1.0f), ka);
}

TEST_F(ParseArgsTest, kdTest) {
  const char *args[5] = {"./as0", "-kd", "0.0", "0.5", "1.0"};
  parseArgs(5, const_cast<char **>(args));
  EXPECT_EQ(Color(0.0f, 0.5f, 1.0f), kd);
}

TEST_F(ParseArgsTest, ksTest) {
  const char *args[5] = {"./as0", "-ks", "0.0", "0.5", "1.0"};
  parseArgs(5, const_cast<char **>(args));
  EXPECT_EQ(Color(0.0f, 0.5f, 1.0f), ks);
}

TEST_F(ParseArgsTest, spTest) {
  const char *args[3] = {"./as0", "-sp", "1.0"};
  parseArgs(3, const_cast<char **>(args));
  EXPECT_EQ(1.0f, sp_v);
}

TEST_F(ParseArgsTest, plTest) {
  const char *args[8] = {"./as0", "-pl", "0.0", "0.5", "1.0", "100", "200", "255"};
  parseArgs(8, const_cast<char **>(args));
  EXPECT_EQ(Vector(0.0f, 0.5f, 1.0f), pl_vector.at(0));
  EXPECT_EQ(Color(100.0f, 200.0f, 255.0f), pl_color.at(0));
}

TEST_F(ParseArgsTest, plMultipleTest) {
  const char *args[15] = {"./as0", 
    "-pl", "0.0", "0.5", "1.0", "100", "200", "255",
    "-pl", "0.0", "0.5", "1.0", "100", "200", "255"
  };
  parseArgs(15, const_cast<char **>(args));
  EXPECT_EQ(Vector(0.0f, 0.5f, 1.0f), pl_vector.at(0));
  EXPECT_EQ(Color(100.0f, 200.0f, 255.0f), pl_color.at(0));

  EXPECT_EQ(Vector(0.0f, 0.5f, 1.0f), pl_vector.at(1));
  EXPECT_EQ(Color(100.0f, 200.0f, 255.0f), pl_color.at(1));
}

TEST_F(ParseArgsTest, dlTest) {
  const char *args[8] = {"./as0", "-dl", "0.0", "0.5", "1.0", "100", "200", "255"};
  parseArgs(8, const_cast<char **>(args));
  EXPECT_EQ(Vector(0.0f, 0.5f, 1.0f), dl_vector.at(0));
  EXPECT_EQ(Color(100.0f, 200.0f, 255.0f), dl_color.at(0));
}

TEST_F(ParseArgsTest, dlMultipleTest) {
  const char *args[15] = {"./as0", 
    "-dl", "0.0", "0.5", "1.0", "100", "200", "255",
    "-dl", "0.0", "0.5", "1.0", "100", "200", "255"
  };
  parseArgs(15, const_cast<char **>(args));
  EXPECT_EQ(Vector(0.0f, 0.5f, 1.0f), dl_vector.at(0));
  EXPECT_EQ(Color(100.0f, 200.0f, 255.0f), dl_color.at(0));

  EXPECT_EQ(Vector(0.0f, 0.5f, 1.0f), dl_vector.at(1));
  EXPECT_EQ(Color(100.0f, 200.0f, 255.0f), dl_color.at(1));
}

TEST_F(ParseArgsTest, MultiArgTest) {
  const char *args[17] = {"./as0", 
    "-dl", "0.0", "0.5", "1.0", "100", "200", "255",
    "-pl", "0.0", "0.5", "1.0", "100", "200", "255",
    "-sp", "1.0"
  };
  parseArgs(17, const_cast<char **>(args));
  EXPECT_EQ(Vector(0.0f, 0.5f, 1.0f), dl_vector.at(0));
  EXPECT_EQ(Color(100.0f, 200.0f, 255.0f), dl_color.at(0));

  EXPECT_EQ(Vector(0.0f, 0.5f, 1.0f), pl_vector.at(0));
  EXPECT_EQ(Color(100.0f, 200.0f, 255.0f), pl_color.at(0));

  EXPECT_EQ(1.0f, sp_v);
}

TEST_F(ParseArgsTest, MultiArgTest2) {
  const char *args[16] = {"./as1",
    "-ka", "0.9", "0.9", "1.0", 
    "-kd", "0.2", "0.2", "0.2", 
    "-pl", "1.0", "1.0", "1.0", "255.0", "255.0", "255.0"
  };
  parseArgs(16, const_cast<char **>(args));
  EXPECT_EQ(Color(0.9f, 0.9f, 1.0f), ka);

  EXPECT_EQ(Color(0.2f, 0.2f, 0.2f), kd);

  EXPECT_EQ(Vector(1.0f, 1.0f, 1.0f), pl_vector.at(0));
  EXPECT_EQ(Color(255.0f, 255.0f, 255.0f), pl_color.at(0));
}

// ------------------------------------------------------------
// Vector Operations Test
// ------------------------------------------------------------

class VectorTest : public ::testing::Test {
};

TEST_F(VectorTest, Subtraction) {
  Vector v(1, 2, 3);
  EXPECT_EQ(v-v, Vector());
}

TEST_F(VectorTest, DotProduct) {
  Vector v(1, 2, 3);
  EXPECT_FLOAT_EQ(v.dot(v), 14);
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
  kd = Color(0.0f, 0.0f, 0.0f);
  PixelOps po(Vector(0.0f, 1.0f, 0.0f));
  po.diffuseComponent(Vector(0.0f, 1.0f, 0.0f), Color(1.0, 0.0, 0.0));

  // assert all zero arguments work
  EXPECT_EQ(po.c, Color(0.0f, 0.0f, 0.0f));
}

TEST_F(PixelOpsTest, DiffuseTest) {
  // real values
  kd = Color(1.0f, 0.0f, 0.0f);

  PixelOps po(Vector(-2.0f, 0.0f, 0.0f));
  po.diffuseComponent(Vector(-2.0f, 0.0f, 0.0f), Color(1.0, 0.0, 0.0));

  EXPECT_EQ(po.c, Color(1.0f, 0.0f, 0.0f));
}

//TODO: Add tests for specular component


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
