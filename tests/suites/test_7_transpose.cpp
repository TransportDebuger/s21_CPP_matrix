#include "../test.h"

TEST(TestTranspose, TestTransposeException1) {
  S21Matrix matrix1;
  EXPECT_EQ(matrix1.getRows(), 0);
  EXPECT_EQ(matrix1.getCols(), 0);

  EXPECT_ANY_THROW(matrix1.Transpose());
}

TEST(TestTranspose, TestTranspose1) {
  S21Matrix matrix1{95, 99};
  EXPECT_EQ(matrix1.getRows(), 95);
  EXPECT_EQ(matrix1.getCols(), 99);

  S21Matrix result_check{99, 95};
  EXPECT_EQ(result_check.getRows(), 99);
  EXPECT_EQ(result_check.getCols(), 95);

  test_helper::FillMatrix(matrix1, 1.99);
  test_helper::FillMatrix(result_check, 1.99);

  test_helper::CheckMatrix(matrix1, 1.99);
  test_helper::CheckMatrix(result_check, 1.99);

  S21Matrix result = matrix1.Transpose();

  EXPECT_TRUE(result == result_check);
}

TEST(TestTranspose, TestTranspose2) {
  S21Matrix matrix1{1, 4};
  EXPECT_EQ(matrix1.getRows(), 1);
  EXPECT_EQ(matrix1.getCols(), 4);

  S21Matrix check{4, 1};
  EXPECT_EQ(check.getRows(), 4);
  EXPECT_EQ(check.getCols(), 1);

  matrix1.setMatrixElement(0, 0, 1);
  matrix1.setMatrixElement(0, 1, 2);
  matrix1.setMatrixElement(0, 2, 3);
  matrix1.setMatrixElement(0, 3, 4);

  check.setMatrixElement(0, 0, 1);
  check.setMatrixElement(1, 0, 2);
  check.setMatrixElement(2, 0, 3);
  check.setMatrixElement(3, 0, 4);

  S21Matrix result = matrix1.Transpose();

  EXPECT_TRUE(result == check);
}

TEST(TestTranspose, TestTranspose3) {
  S21Matrix matrix1{4, 1};
  EXPECT_EQ(matrix1.getRows(), 4);
  EXPECT_EQ(matrix1.getCols(), 1);

  S21Matrix check{1, 4};
  EXPECT_EQ(check.getRows(), 1);
  EXPECT_EQ(check.getCols(), 4);

  matrix1.setMatrixElement(0, 0, 1);
  matrix1.setMatrixElement(1, 0, 2);
  matrix1.setMatrixElement(2, 0, 3);
  matrix1.setMatrixElement(3, 0, 4);

  check.setMatrixElement(0, 0, 1);
  check.setMatrixElement(0, 1, 2);
  check.setMatrixElement(0, 2, 3);
  check.setMatrixElement(0, 3, 4);

  S21Matrix result = matrix1.Transpose();

  EXPECT_TRUE(result == check);
}