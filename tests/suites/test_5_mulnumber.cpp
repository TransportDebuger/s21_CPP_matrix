#include "../test.h"

TEST(TestMulNumber, TestFunction1) {
  S21Matrix matrix1{95, 99};
  EXPECT_EQ(matrix1.getRows(), 95);
  EXPECT_EQ(matrix1.getCols(), 99);

  double number = 2.0;

  test_helper::FillMatrix(matrix1, 2.5);

  matrix1.MulNumber(number);

  test_helper::CheckMatrix(matrix1, 2.5 * number);

  matrix1.MulNumber(number);

  test_helper::CheckMatrix(matrix1, 2.5 * number * number);
}

TEST(TestMulNumber, TestFunction2) {
  S21Matrix matrix1{199, 1};
  EXPECT_EQ(matrix1.getRows(), 199);
  EXPECT_EQ(matrix1.getCols(), 1);

  double number = -2.999;

  test_helper::FillMatrix(matrix1, -1.999);

  matrix1.MulNumber(number);

  test_helper::CheckMatrix(matrix1, -1.999 * number);

  matrix1.MulNumber(number);

  test_helper::CheckMatrix(matrix1, -1.999 * number * number);
}

TEST(TestMulNumber, TestFunction3) {
  S21Matrix matrix1{1, 199};
  EXPECT_EQ(matrix1.getRows(), 1);
  EXPECT_EQ(matrix1.getCols(), 199);

  double number = 2.5999;

  test_helper::FillMatrix(matrix1, 1.5999);

  matrix1.MulNumber(number);

  test_helper::CheckMatrix(matrix1, 1.5999 * number);

  matrix1.MulNumber(number);

  test_helper::CheckMatrix(matrix1, 1.5999 * number * number);
}

TEST(TestMulNumber, TestFunction4) {
  S21Matrix matrix1{4, 3};
  EXPECT_EQ(matrix1.getRows(), 4);
  EXPECT_EQ(matrix1.getCols(), 3);

  S21Matrix check_matrix = matrix1;
  EXPECT_EQ(check_matrix.getRows(), 4);
  EXPECT_EQ(check_matrix.getCols(), 3);

  double number = 1.99;

  matrix1.setMatrixElement(0, 0, 1.5);
  matrix1.setMatrixElement(0, 1, 2.5);
  matrix1.setMatrixElement(0, 2, 3.5);
  matrix1.setMatrixElement(1, 0, -1.5);
  matrix1.setMatrixElement(1, 1, -2.5);
  matrix1.setMatrixElement(1, 2, -3.5);
  matrix1.setMatrixElement(2, 0, 0.0);
  matrix1.setMatrixElement(2, 1, 0.0);
  matrix1.setMatrixElement(2, 2, 0.0);
  matrix1.setMatrixElement(3, 0, 1.0);
  matrix1.setMatrixElement(3, 1, 1.0);
  matrix1.setMatrixElement(3, 2, 1.0);

  check_matrix.setMatrixElement(0, 0, 2.985);
  check_matrix.setMatrixElement(0, 1, 4.975);
  check_matrix.setMatrixElement(0, 2, 6.965);
  check_matrix.setMatrixElement(1, 0, -2.985);
  check_matrix.setMatrixElement(1, 1, -4.975);
  check_matrix.setMatrixElement(1, 2, -6.965);
  check_matrix.setMatrixElement(2, 0, 0.0);
  check_matrix.setMatrixElement(2, 1, 0.0);
  check_matrix.setMatrixElement(2, 2, 0.0);
  check_matrix.setMatrixElement(3, 0, 1.99);
  check_matrix.setMatrixElement(3, 1, 1.99);
  check_matrix.setMatrixElement(3, 2, 1.99);

  matrix1.MulNumber(number);

  EXPECT_TRUE(matrix1 == check_matrix);
}

TEST(TestMulNumber, TestOperator1) {
  S21Matrix matrix1{95, 99};
  EXPECT_EQ(matrix1.getRows(), 95);
  EXPECT_EQ(matrix1.getCols(), 99);

  double number = 2.0;

  test_helper::FillMatrix(matrix1, 2.5);

  S21Matrix result = matrix1 * number;

  test_helper::CheckMatrix(result, 2.5 * number);
}

TEST(TestMulNumber, TestOperator2) {
  S21Matrix matrix1{199, 1};
  EXPECT_EQ(matrix1.getRows(), 199);
  EXPECT_EQ(matrix1.getCols(), 1);

  double number = -2.999;

  test_helper::FillMatrix(matrix1, -1.999);

  S21Matrix result = matrix1 * number;

  test_helper::CheckMatrix(result, -1.999 * number);
}

TEST(TestMulNumber, TestOperator3) {
  S21Matrix matrix1{1, 199};
  EXPECT_EQ(matrix1.getRows(), 1);
  EXPECT_EQ(matrix1.getCols(), 199);

  double number = 2.5999;

  test_helper::FillMatrix(matrix1, 1.5999);

  S21Matrix result = matrix1 * number;

  test_helper::CheckMatrix(result, 1.5999 * number);
}

TEST(TestMulNumber, TestOperator4) {
  S21Matrix matrix1{4, 3};
  EXPECT_EQ(matrix1.getRows(), 4);
  EXPECT_EQ(matrix1.getCols(), 3);

  S21Matrix check_matrix = matrix1;
  EXPECT_EQ(check_matrix.getRows(), 4);
  EXPECT_EQ(check_matrix.getCols(), 3);

  double number = 1.99;

  matrix1.setMatrixElement(0, 0, 1.5);
  matrix1.setMatrixElement(0, 1, 2.5);
  matrix1.setMatrixElement(0, 2, 3.5);
  matrix1.setMatrixElement(1, 0, -1.5);
  matrix1.setMatrixElement(1, 1, -2.5);
  matrix1.setMatrixElement(1, 2, -3.5);
  matrix1.setMatrixElement(2, 0, 0.0);
  matrix1.setMatrixElement(2, 1, 0.0);
  matrix1.setMatrixElement(2, 2, 0.0);
  matrix1.setMatrixElement(3, 0, 1.0);
  matrix1.setMatrixElement(3, 1, 1.0);
  matrix1.setMatrixElement(3, 2, 1.0);

  check_matrix.setMatrixElement(0, 0, 2.985);
  check_matrix.setMatrixElement(0, 1, 4.975);
  check_matrix.setMatrixElement(0, 2, 6.965);
  check_matrix.setMatrixElement(1, 0, -2.985);
  check_matrix.setMatrixElement(1, 1, -4.975);
  check_matrix.setMatrixElement(1, 2, -6.965);
  check_matrix.setMatrixElement(2, 0, 0.0);
  check_matrix.setMatrixElement(2, 1, 0.0);
  check_matrix.setMatrixElement(2, 2, 0.0);
  check_matrix.setMatrixElement(3, 0, 1.99);
  check_matrix.setMatrixElement(3, 1, 1.99);
  check_matrix.setMatrixElement(3, 2, 1.99);

  S21Matrix result = matrix1 * number;

  EXPECT_TRUE(result == check_matrix);
}

TEST(TestMulNumber, TestMulNSetOperator1) {
  S21Matrix matrix1{95, 99};
  EXPECT_EQ(matrix1.getRows(), 95);
  EXPECT_EQ(matrix1.getCols(), 99);

  double number = 2.0;

  test_helper::FillMatrix(matrix1, 2.5);

  matrix1 *= number;

  test_helper::CheckMatrix(matrix1, 2.5 * number);
}

TEST(TestMulNumber, TestMulNSetOperator2) {
  S21Matrix matrix1{199, 1};
  EXPECT_EQ(matrix1.getRows(), 199);
  EXPECT_EQ(matrix1.getCols(), 1);

  double number = -2.999;

  test_helper::FillMatrix(matrix1, -1.999);

  matrix1 *= number;

  test_helper::CheckMatrix(matrix1, -1.999 * number);
}

TEST(TestMulNumber, TestMulNSetOperator3) {
  S21Matrix matrix1{1, 199};
  EXPECT_EQ(matrix1.getRows(), 1);
  EXPECT_EQ(matrix1.getCols(), 199);

  double number = 2.5999;

  test_helper::FillMatrix(matrix1, 1.5999);

  matrix1 *= number;

  test_helper::CheckMatrix(matrix1, 1.5999 * number);
}

TEST(TestMulNumber, TestMulNSetOperator4) {
  S21Matrix matrix1{4, 3};
  EXPECT_EQ(matrix1.getRows(), 4);
  EXPECT_EQ(matrix1.getCols(), 3);

  S21Matrix check_matrix = matrix1;
  EXPECT_EQ(check_matrix.getRows(), 4);
  EXPECT_EQ(check_matrix.getCols(), 3);

  double number = 1.99;

  matrix1.setMatrixElement(0, 0, 1.5);
  matrix1.setMatrixElement(0, 1, 2.5);
  matrix1.setMatrixElement(0, 2, 3.5);
  matrix1.setMatrixElement(1, 0, -1.5);
  matrix1.setMatrixElement(1, 1, -2.5);
  matrix1.setMatrixElement(1, 2, -3.5);
  matrix1.setMatrixElement(2, 0, 0.0);
  matrix1.setMatrixElement(2, 1, 0.0);
  matrix1.setMatrixElement(2, 2, 0.0);
  matrix1.setMatrixElement(3, 0, 1.0);
  matrix1.setMatrixElement(3, 1, 1.0);
  matrix1.setMatrixElement(3, 2, 1.0);

  check_matrix.setMatrixElement(0, 0, 2.985);
  check_matrix.setMatrixElement(0, 1, 4.975);
  check_matrix.setMatrixElement(0, 2, 6.965);
  check_matrix.setMatrixElement(1, 0, -2.985);
  check_matrix.setMatrixElement(1, 1, -4.975);
  check_matrix.setMatrixElement(1, 2, -6.965);
  check_matrix.setMatrixElement(2, 0, 0.0);
  check_matrix.setMatrixElement(2, 1, 0.0);
  check_matrix.setMatrixElement(2, 2, 0.0);
  check_matrix.setMatrixElement(3, 0, 1.99);
  check_matrix.setMatrixElement(3, 1, 1.99);
  check_matrix.setMatrixElement(3, 2, 1.99);

  matrix1 *= number;

  EXPECT_TRUE(matrix1 == check_matrix);
}