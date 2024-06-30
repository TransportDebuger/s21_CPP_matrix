#include "test.h"

// Constructor tests

//Test default constructor

int main(int argc, char *argv[]) {
  //     ::testing::GTEST_FLAG(filter) = "TestMulMatrix.*";

  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}