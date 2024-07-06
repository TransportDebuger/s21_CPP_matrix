#include "../test.h"

TEST(TestDefaultCostructor, VariableDeclaration) {
  S21Matrix testMatrix;

  EXPECT_EQ(testMatrix.getRows(), 0);
  EXPECT_EQ(testMatrix.getCols(), 0);
}

// Exception test for parametrized constructor
TEST(TestParametrizedConstructor, TestExceptionNegativeColValue) {
  EXPECT_ANY_THROW(S21Matrix(-1, 1));
}

TEST(TestParametrizedConstructor, TestExceptionNegativeRowValue) {
  EXPECT_ANY_THROW(S21Matrix(1, -1));
}

TEST(TestParametrizedConstructor, TestExceptionNegativeValuesOfDimentions1) {
  EXPECT_ANY_THROW(S21Matrix(-1, -1));
}

TEST(TestParametrizedConstructor, TestExceptionNegativeValuesOfDimentions2) {
  EXPECT_ANY_THROW(S21Matrix(-100, -100));
}

TEST(TestParametrizedConstructor, TestMatrixCreationZeroDimValues1) {
  S21Matrix testMatrix(0, 0);

  EXPECT_EQ(testMatrix.getRows(), 0);
  EXPECT_EQ(testMatrix.getCols(), 0);
}

TEST(TestParametrizedConstructor, TestMatrixCreationZeroDimValues2) {
  S21Matrix testMatrix(0, 100);

  EXPECT_EQ(testMatrix.getRows(), 0);
  EXPECT_EQ(testMatrix.getCols(), 0);
}

TEST(TestParametrizedConstructor, TestMatrixCreationZeroDimValues3) {
  S21Matrix testMatrix(100, 0);

  EXPECT_EQ(testMatrix.getRows(), 0);
  EXPECT_EQ(testMatrix.getCols(), 0);
}

TEST(TestParametrizedConstructor, TestMatrixCreationPositiveValues1) {
  S21Matrix testMatrix(2, 2);
  double val = 1.0;

  testMatrix.setMatrixElement(0, 0, val);
  testMatrix.setMatrixElement(0, 1, val);
  testMatrix.setMatrixElement(1, 0, val);
  testMatrix.setMatrixElement(1, 1, val);

  EXPECT_EQ(testMatrix.getRows(), 2);
  EXPECT_EQ(testMatrix.getCols(), 2);

  test_helper::CheckMatrix(testMatrix, val);
}

TEST(TestParametrizedConstructor, TestMatrixCreationPositiveValues2) {
  S21Matrix testMatrix(2, 2);
  double val = 1.000000099;

  testMatrix.setMatrixElement(0, 0, val);
  testMatrix.setMatrixElement(0, 1, val);
  testMatrix.setMatrixElement(1, 0, val);
  testMatrix.setMatrixElement(1, 1, val);

  EXPECT_EQ(testMatrix.getRows(), 2);
  EXPECT_EQ(testMatrix.getCols(), 2);

  test_helper::CheckMatrix(testMatrix, 1.0);
}

TEST(TestCopyConstructor, TestConstructor1) {
  S21Matrix matrix_check = S21Matrix(2, 2);

  test_helper::FillMatrix(matrix_check, 4.0);

  S21Matrix matrix_copy = matrix_check;

  EXPECT_EQ(matrix_check.getCols(), 2);
  EXPECT_EQ(matrix_check.getRows(), 2);

  EXPECT_EQ(matrix_copy.getCols(), 2);
  EXPECT_EQ(matrix_copy.getRows(), 2);

  test_helper::CheckMatrix(matrix_check, 4.0);
  test_helper::CheckMatrix(matrix_copy, 4.0);
}

TEST(TestCopyConstructor, TestConstructor2) {
  S21Matrix matrix_check = S21Matrix(2, 2);

  test_helper::FillMatrix(matrix_check, 4.0);

  S21Matrix matrix_copy(matrix_check);

  EXPECT_EQ(matrix_check.getCols(), 2);
  EXPECT_EQ(matrix_check.getRows(), 2);

  EXPECT_EQ(matrix_copy.getCols(), 2);
  EXPECT_EQ(matrix_copy.getRows(), 2);

  test_helper::CheckMatrix(matrix_check, 4.0);
  test_helper::CheckMatrix(matrix_copy, 4.0);
}

TEST(TestCopyConstructor, TestConstructor3) {
  S21Matrix matrix_check = S21Matrix(2, 2);

  test_helper::FillMatrix(matrix_check, 4.0);

  S21Matrix matrix_copy{matrix_check};

  EXPECT_EQ(matrix_check.getCols(), 2);
  EXPECT_EQ(matrix_check.getRows(), 2);

  EXPECT_EQ(matrix_copy.getCols(), 2);
  EXPECT_EQ(matrix_copy.getRows(), 2);

  test_helper::CheckMatrix(matrix_check, 4.0);
  test_helper::CheckMatrix(matrix_copy, 4.0);
}

TEST(TestMoveConstructor, TestConstructor1) {
  S21Matrix matrix_check = S21Matrix(2, 2);

  test_helper::FillMatrix(matrix_check, 4.0);
  S21Matrix matrix_move = std::move(matrix_check);

  EXPECT_EQ(matrix_check.getCols(), 0);
  EXPECT_EQ(matrix_check.getRows(), 0);

  EXPECT_EQ(matrix_move.getCols(), 2);
  EXPECT_EQ(matrix_move.getRows(), 2);

  test_helper::CheckMatrix(matrix_check, 4.0);
  test_helper::CheckMatrix(matrix_move, 4.0);
}

TEST(TestMoveConstructor, TestConstructor2) {
  S21Matrix matrix_check = S21Matrix(2, 2);
  S21Matrix matrix_test = S21Matrix(3, 3);

  test_helper::FillMatrix(matrix_check, 4.0);
  test_helper::FillMatrix(matrix_test, 3.0);

  matrix_test = std::move(matrix_check);

  EXPECT_EQ(matrix_check.getCols(), 0);
  EXPECT_EQ(matrix_check.getRows(), 0);

  EXPECT_EQ(matrix_test.getCols(), 2);
  EXPECT_EQ(matrix_test.getRows(), 2);

  test_helper::CheckMatrix(matrix_check, 3.0);
  test_helper::CheckMatrix(matrix_test, 4.0);
}
