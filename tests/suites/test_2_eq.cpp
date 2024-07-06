#include "../test.h"

TEST(TestMatrixEquality, TestUnequality1) {
  S21Matrix matrix1{1, 1};
  S21Matrix matrix2{1, 1};

  matrix1.setMatrixElement(0, 0, -1);
  matrix2.setMatrixElement(0, 0, 2);
  EXPECT_FALSE(matrix1 == matrix2);
}

TEST(TestMatrixEquality, TestUnequality2) {
  S21Matrix matrix1{1, 1};
  S21Matrix matrix2{1, 1};

  matrix1.setMatrixElement(0, 0, 1);
  matrix2.setMatrixElement(0, 0, -2);
  EXPECT_FALSE(matrix1 == matrix2);
}

TEST(TestMatrixEquality, TestUnequality3) {
  S21Matrix matrix1{1, 1};
  S21Matrix matrix2{1, 2};

  EXPECT_FALSE(matrix1 == matrix2);
}

TEST(TestMatrixEquality, TestUnequality4) {
  S21Matrix matrix1{1, 2};
  S21Matrix matrix2{1, 1};

  EXPECT_FALSE(matrix1 == matrix2);
}

TEST(TestMatrixEquality, TestUnequality5) {
  S21Matrix matrix1{1, 1};
  S21Matrix matrix2{2, 1};

  EXPECT_FALSE(matrix1 == matrix2);
}

TEST(TestMatrixEquality, TestUnequality6) {
  S21Matrix matrix1{2, 1};
  S21Matrix matrix2{1, 1};

  EXPECT_FALSE(matrix1 == matrix2);
}

TEST(TestMatrixEquality, TestUnequality7) {
  S21Matrix matrix1{2, 2};
  EXPECT_EQ(matrix1.getCols(), 2);
  EXPECT_EQ(matrix1.getRows(), 2);

  S21Matrix matrix2{2, 2};
  EXPECT_EQ(matrix2.getCols(), 2);
  EXPECT_EQ(matrix2.getRows(), 2);

  test_helper::CheckMatrix(matrix1, 0.0);
  test_helper::CheckMatrix(matrix2, 0.0);

  bool result1 = matrix1.EqMatrix(matrix2);
  EXPECT_TRUE(result1);
  EXPECT_TRUE(matrix1 == matrix2);

  test_helper::CheckMatrix(matrix1, 0.0);
  test_helper::CheckMatrix(matrix2, 0.0);

  matrix1.setMatrixElement(0, 0, 1);
  matrix1.setMatrixElement(0, 1, 2);
  matrix1.setMatrixElement(1, 0, 3);
  matrix1.setMatrixElement(1, 1, 4);

  matrix2.setMatrixElement(0, 0, 4);
  matrix2.setMatrixElement(0, 1, 3);
  matrix2.setMatrixElement(1, 0, 2);
  matrix2.setMatrixElement(1, 1, 1);

  bool result2 = matrix1.EqMatrix(matrix2);
  EXPECT_FALSE(result2);
  EXPECT_FALSE(matrix1 == matrix2);
}

TEST(TestMatrixEquality, TestEquality1) {
  S21Matrix matrix1{2, 2};
  EXPECT_EQ(matrix1.getCols(), 2);
  EXPECT_EQ(matrix1.getRows(), 2);

  S21Matrix matrix2{2, 2};
  EXPECT_EQ(matrix2.getCols(), 2);
  EXPECT_EQ(matrix2.getRows(), 2);

  test_helper::CheckMatrix(matrix1, 0.0);
  test_helper::CheckMatrix(matrix2, 0.0);

  bool result1 = matrix1.EqMatrix(matrix2);
  EXPECT_TRUE(result1);
  EXPECT_TRUE(matrix1 == matrix2);

  test_helper::CheckMatrix(matrix1, 0.0);
  test_helper::CheckMatrix(matrix2, 0.0);

  matrix1.setMatrixElement(0, 0, 1);
  matrix1.setMatrixElement(0, 1, 2);
  matrix1.setMatrixElement(1, 0, 3);
  matrix1.setMatrixElement(1, 1, 4);

  matrix2.setMatrixElement(0, 0, 1);
  matrix2.setMatrixElement(0, 1, 2);
  matrix2.setMatrixElement(1, 0, 3);
  matrix2.setMatrixElement(1, 1, 4);

  bool result2 = matrix1.EqMatrix(matrix2);
  EXPECT_TRUE(result2);
  EXPECT_TRUE(matrix1 == matrix2);
}

TEST(TestMatrixEquality, TestEquality2) {
  S21Matrix matrix1{2, 2};
  EXPECT_EQ(matrix1.getCols(), 2);
  EXPECT_EQ(matrix1.getRows(), 2);

  S21Matrix matrix2{2, 2};
  EXPECT_EQ(matrix2.getCols(), 2);
  EXPECT_EQ(matrix2.getRows(), 2);

  test_helper::CheckMatrix(matrix1, 0.0);
  test_helper::CheckMatrix(matrix2, 0.0);

  bool result1 = matrix1.EqMatrix(matrix2);
  EXPECT_TRUE(result1);
  EXPECT_TRUE(matrix1 == matrix2);

  test_helper::CheckMatrix(matrix1, 0.0);
  test_helper::CheckMatrix(matrix2, 0.0);

  test_helper::FillMatrix(matrix1, 2.0);
  test_helper::FillMatrix(matrix2, 2.0);

  bool result2 = matrix1.EqMatrix(matrix2);
  EXPECT_TRUE(result2);
  EXPECT_TRUE(matrix1 == matrix2);

  test_helper::CheckMatrix(matrix1, 2.0);
  test_helper::CheckMatrix(matrix2, 2.0);
}

TEST(TestMatrixEquality, TestEqualityPrecise1) {
  S21Matrix matrix1{1, 1};
  EXPECT_EQ(matrix1.getCols(), 1);
  EXPECT_EQ(matrix1.getRows(), 1);

  S21Matrix matrix2{1, 1};
  EXPECT_EQ(matrix2.getCols(), 1);
  EXPECT_EQ(matrix2.getRows(), 1);

  test_helper::CheckMatrix(matrix1, 0.0);
  test_helper::CheckMatrix(matrix2, 0.0);

  bool result1 = matrix1.EqMatrix(matrix2);
  EXPECT_TRUE(result1);
  EXPECT_TRUE(matrix1 == matrix2);

  test_helper::CheckMatrix(matrix1, 0.0);
  test_helper::CheckMatrix(matrix2, 0.0);

  matrix1.setMatrixElement(0, 0, 2.5);
  matrix2.setMatrixElement(0, 0, 2.5);

  bool result2 = matrix1.EqMatrix(matrix2);
  EXPECT_TRUE(result2);
  EXPECT_TRUE(matrix1 == matrix2);

  test_helper::CheckMatrix(matrix1, 2.5);
  test_helper::CheckMatrix(matrix2, 2.5);

  matrix1.setMatrixElement(0, 0, 2.5000001);
  matrix2.setMatrixElement(0, 0, 2.5);

  bool result3 = matrix1.EqMatrix(matrix2);
  EXPECT_TRUE(result3);
  EXPECT_TRUE(matrix1 == matrix2);

  test_helper::CheckMatrix(matrix1, 2.5);
  test_helper::CheckMatrix(matrix2, 2.5);
}

TEST(TestMatrixEquality, TestEqualityPrecise2) {
  S21Matrix matrix1{2, 2};
  EXPECT_EQ(matrix1.getCols(), 2);
  EXPECT_EQ(matrix1.getRows(), 2);

  S21Matrix matrix2{2, 2};
  EXPECT_EQ(matrix2.getCols(), 2);
  EXPECT_EQ(matrix2.getRows(), 2);

  test_helper::CheckMatrix(matrix1, 0.0);
  test_helper::CheckMatrix(matrix2, 0.0);

  matrix2.setMatrixElement(0, 0, 0.00000001);

  bool result1 = matrix1.EqMatrix(matrix2);
  EXPECT_TRUE(result1);
  EXPECT_TRUE(matrix1 == matrix2);

  test_helper::CheckMatrix(matrix1, 0.0);
  test_helper::CheckMatrix(matrix2, 0.0);

  matrix1.setMatrixElement(0, 0, 0.00000009);

  bool result2 = matrix1.EqMatrix(matrix2);
  EXPECT_TRUE(result2);
  EXPECT_TRUE(matrix1 == matrix2);

  test_helper::CheckMatrix(matrix1, 0.0);
  test_helper::CheckMatrix(matrix2, 0.0);
}
