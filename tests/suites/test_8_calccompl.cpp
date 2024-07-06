#include "../test.h"

TEST(TestCalcComplements, TestCalcComplementsException1) {
  S21Matrix test_matrix(2, 3);

  EXPECT_ANY_THROW(test_matrix.CalcComplements());
}

TEST(TestCalcComplements, TestCalcComplementsException2) {
  S21Matrix test_matrix(3, 2);

  EXPECT_ANY_THROW(test_matrix.CalcComplements());
}

TEST(TestCalcComplements, TestCalcComplementsException3) {
  S21Matrix test_matrix;

  EXPECT_ANY_THROW(test_matrix.CalcComplements());
}

TEST(TestCalcComplements, TestCalcComplementsOne1) {
  S21Matrix test_matrix(1, 1);

  EXPECT_EQ(test_matrix.getRows(), 1);
  EXPECT_EQ(test_matrix.getCols(), 1);

  const S21Matrix& matrix_before = test_matrix;
  S21Matrix result;

  EXPECT_NO_THROW(result = test_matrix.CalcComplements());
  EXPECT_TRUE(test_matrix == matrix_before);

  EXPECT_EQ(result.getRows(), 1);
  EXPECT_EQ(result.getCols(), 1);
  EXPECT_EQ(result(0, 0), 1.0);
}

TEST(TestCalcComplements, TestCalcComplementsOne2) {
  S21Matrix test_matrix(1, 1);

  EXPECT_EQ(test_matrix.getRows(), 1);
  EXPECT_EQ(test_matrix.getCols(), 1);

  test_matrix.setMatrixElement(0, 0, 5.0);
  S21Matrix matrix_before = test_matrix;
  S21Matrix result;

  EXPECT_NO_THROW(result = test_matrix.CalcComplements());
  EXPECT_TRUE(test_matrix == matrix_before);

  EXPECT_EQ(result.getRows(), 1);
  EXPECT_EQ(result.getCols(), 1);
  EXPECT_EQ(result(0, 0), 1.0);
}

TEST(TestCalcComplements, TestCalcComplements1) {
  S21Matrix matrix1{2, 2};
  EXPECT_EQ(matrix1.getCols(), 2);
  EXPECT_EQ(matrix1.getRows(), 2);

  S21Matrix result_check{2, 2};
  EXPECT_EQ(result_check.getCols(), 2);
  EXPECT_EQ(result_check.getRows(), 2);

  matrix1.setMatrixElement(0, 0, 1);
  matrix1.setMatrixElement(0, 1, 2);
  matrix1.setMatrixElement(1, 0, 3);
  matrix1.setMatrixElement(1, 1, 4);

  result_check.setMatrixElement(0, 0, 4);
  result_check.setMatrixElement(0, 1, -3);
  result_check.setMatrixElement(1, 0, -2);
  result_check.setMatrixElement(1, 1, 1);

  S21Matrix result = matrix1.CalcComplements();

  EXPECT_TRUE(result == result_check);
}

TEST(TestCalcComplements, TestCalcComplementsZero1) {
  S21Matrix matrix1{3, 3};
  EXPECT_EQ(matrix1.getCols(), 3);
  EXPECT_EQ(matrix1.getRows(), 3);

  S21Matrix result_check{3, 3};
  EXPECT_EQ(result_check.getCols(), 3);
  EXPECT_EQ(result_check.getRows(), 3);

  test_helper::CheckMatrix(result_check, 0.0);

  matrix1.setMatrixElement(0, 0, -3.00);
  matrix1.setMatrixElement(0, 1, 6.00);
  matrix1.setMatrixElement(0, 2, -3.00);
  matrix1.setMatrixElement(1, 0, 6.00);
  matrix1.setMatrixElement(1, 1, -12.00);
  matrix1.setMatrixElement(1, 2, 6.00);
  matrix1.setMatrixElement(2, 0, -3.00);
  matrix1.setMatrixElement(2, 1, 6.00);
  matrix1.setMatrixElement(2, 2, -3.00);

  S21Matrix result = matrix1.CalcComplements();

  EXPECT_TRUE(result == result_check);
}