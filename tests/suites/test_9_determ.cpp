#include "../test.h"

TEST(TestDeterminant, TestDeterminantException1) {
  S21Matrix test_matrix(2, 3);

  EXPECT_ANY_THROW(test_matrix.Determinant());
}

TEST(TestDeterminant, TestDeterminantException2) {
  S21Matrix test_matrix(3, 2);

  EXPECT_ANY_THROW(test_matrix.Determinant());
}

TEST(TestDeterminant, TestDeterminantException3) {
  S21Matrix test_matrix;

  EXPECT_ANY_THROW(test_matrix.Determinant());
}

TEST(TestDeterminant, TestDeterminant1) {
  S21Matrix matrix1{1, 1};
  EXPECT_EQ(matrix1.getCols(), 1);
  EXPECT_EQ(matrix1.getRows(), 1);

  matrix1.setMatrixElement(0, 0, 0.0);

  double result_check = 0.0;

  double result = matrix1.Determinant();

  EXPECT_NEAR(result_check, result, EQ_PRECISE);
}

TEST(TestDeterminant, TestDeterminant2) {
  S21Matrix matrix1{1, 1};
  EXPECT_EQ(matrix1.getCols(), 1);
  EXPECT_EQ(matrix1.getRows(), 1);

  matrix1.setMatrixElement(0, 0, 1.0);

  double result_check = 1.0;

  double result = matrix1.Determinant();

  EXPECT_NEAR(result_check, result, EQ_PRECISE);
}

TEST(TestDeterminant, TestDeterminant3) {
  S21Matrix matrix1{2, 2};
  EXPECT_EQ(matrix1.getCols(), 2);
  EXPECT_EQ(matrix1.getRows(), 2);

  matrix1.setMatrixElement(0, 0, 1.1);
  matrix1.setMatrixElement(0, 1, 1.2);
  matrix1.setMatrixElement(1, 0, 1.3);
  matrix1.setMatrixElement(1, 1, 1.4);

  double result_check = -0.02;

  double result = matrix1.Determinant();

  EXPECT_NEAR(result_check, result, EQ_PRECISE);
}

TEST(TestDeterminant, TestDeterminant4) {
  S21Matrix matrix1{3, 3};
  EXPECT_EQ(matrix1.getCols(), 3);
  EXPECT_EQ(matrix1.getRows(), 3);

  matrix1.setMatrixElement(0, 0, 1.1);
  matrix1.setMatrixElement(0, 1, 1.2);
  matrix1.setMatrixElement(0, 2, 1.3);
  matrix1.setMatrixElement(1, 0, 1.4);
  matrix1.setMatrixElement(1, 1, 1.5);
  matrix1.setMatrixElement(1, 2, 1.6);
  matrix1.setMatrixElement(2, 0, 1.7);
  matrix1.setMatrixElement(2, 1, 1.8);
  matrix1.setMatrixElement(2, 2, 1.9);

  double result_check = 0;

  double result = matrix1.Determinant();

  EXPECT_NEAR(result_check, result, EQ_PRECISE);
}

TEST(TestDeterminant, TestDeterminant5) {
  S21Matrix matrix1{10, 10};
  EXPECT_EQ(matrix1.getCols(), 10);
  EXPECT_EQ(matrix1.getRows(), 10);

  test_helper::FillMatrix(matrix1, 4.0);

  double result_check = 0;

  double result = matrix1.Determinant();

  EXPECT_NEAR(result_check, result, EQ_PRECISE);
}