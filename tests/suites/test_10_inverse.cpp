#include "../test.h"

TEST(TestInverse, TestInverseException1) {
  S21Matrix test_matrix(2, 3);
  S21Matrix matrix_before = test_matrix;

  EXPECT_ANY_THROW(test_matrix.InverseMatrix());
  EXPECT_TRUE(test_matrix == matrix_before);
}

TEST(TestInverse, TestInverseException2) {
  S21Matrix test_matrix(3, 2);
  S21Matrix matrix_before = test_matrix;

  EXPECT_ANY_THROW(test_matrix.InverseMatrix());
  EXPECT_TRUE(test_matrix == matrix_before);
}

TEST(TestInverse, TestInverseException3) {
  S21Matrix test_matrix;

  EXPECT_ANY_THROW(test_matrix.InverseMatrix());
}

TEST(TestInverse, TestInverseException4) {
  S21Matrix matrix1{1, 1};
  EXPECT_EQ(matrix1.getCols(), 1);
  EXPECT_EQ(matrix1.getRows(), 1);

  matrix1.setMatrixElement(0, 0, 0.0);

  EXPECT_ANY_THROW(matrix1.InverseMatrix());
}

TEST(TestInverse, TestInverseException5) {
  S21Matrix matrix1{3, 3};
  EXPECT_EQ(matrix1.getCols(), 3);
  EXPECT_EQ(matrix1.getRows(), 3);

  matrix1.setMatrixElement(0, 0, 1.1);
  matrix1.setMatrixElement(0, 1, 12);
  matrix1.setMatrixElement(0, 2, 0.0);
  matrix1.setMatrixElement(1, 0, 14);
  matrix1.setMatrixElement(1, 1, 1.5);
  matrix1.setMatrixElement(1, 2, 0.0);
  matrix1.setMatrixElement(2, 0, 1.7);
  matrix1.setMatrixElement(2, 1, 18);
  matrix1.setMatrixElement(2, 2, 0.0);

  EXPECT_ANY_THROW(matrix1.InverseMatrix());
}

TEST(TestInverse, TestInverse1) {
  S21Matrix matrix1{1, 1};
  EXPECT_EQ(matrix1.getCols(), 1);
  EXPECT_EQ(matrix1.getRows(), 1);

  matrix1.setMatrixElement(0, 0, 1.5);
  S21Matrix inv_matrix = matrix1.InverseMatrix();
  S21Matrix check_matrix{1, 1};
  EXPECT_EQ(check_matrix.getCols(), 1);
  EXPECT_EQ(check_matrix.getRows(), 1);

  check_matrix.setMatrixElement(0, 0, 0.66666666);
  S21Matrix check_matrix2{1, 1};
  EXPECT_EQ(check_matrix.getCols(), 1);
  EXPECT_EQ(check_matrix.getRows(), 1);

  check_matrix2.setMatrixElement(0, 0, 1);

  ASSERT_TRUE(inv_matrix == check_matrix);
  ASSERT_TRUE(check_matrix2 == inv_matrix * matrix1);
}

TEST(TestInverse, TestInverse2) {
  S21Matrix matrix1{2, 2};
  EXPECT_EQ(matrix1.getCols(), 2);
  EXPECT_EQ(matrix1.getRows(), 2);

  matrix1.setMatrixElement(0, 0, 1.5);
  matrix1.setMatrixElement(0, 1, 2.5);
  matrix1.setMatrixElement(1, 0, 3.5);
  matrix1.setMatrixElement(1, 1, 2.5);
  S21Matrix inv_matrix = matrix1.InverseMatrix();

  S21Matrix check_matrix{2, 2};
  check_matrix.setMatrixElement(0, 0, -0.5);
  check_matrix.setMatrixElement(0, 1, 0.5);
  check_matrix.setMatrixElement(1, 0, 0.7);
  check_matrix.setMatrixElement(1, 1, -0.3);
  for (int i = 0; i < inv_matrix.getRows(); i++) {
    for (int j = 0; j < inv_matrix.getCols(); j++) {
      ASSERT_NEAR(check_matrix.getMatrixElement(i, j),
                  inv_matrix.getMatrixElement(i, j), EQ_PRECISE);
    }
  }
  S21Matrix check_matrix2{2, 2};
  check_matrix2.setMatrixElement(0, 0, 1.0);
  check_matrix2.setMatrixElement(1, 1, 1.0);
  S21Matrix id_matrix = inv_matrix * matrix1;
  for (int i = 0; i < id_matrix.getRows(); i++) {
    for (int j = 0; j < id_matrix.getCols(); j++) {
      ASSERT_NEAR(check_matrix2.getMatrixElement(i, j),
                  id_matrix.getMatrixElement(i, j), EQ_PRECISE);
    }
  }

  ASSERT_TRUE(check_matrix == inv_matrix);
  ASSERT_TRUE(check_matrix2 == id_matrix);
}

TEST(TestInverse, TestInverse3) {
  S21Matrix matrix1{3, 3};
  EXPECT_EQ(matrix1.getCols(), 3);
  EXPECT_EQ(matrix1.getRows(), 3);

  matrix1.setMatrixElement(0, 0, 1.5);
  matrix1.setMatrixElement(0, 1, 1.5);
  matrix1.setMatrixElement(0, 2, 2.5);
  matrix1.setMatrixElement(1, 0, 3.5);
  matrix1.setMatrixElement(1, 1, 2.5);
  matrix1.setMatrixElement(1, 2, 1.5);
  matrix1.setMatrixElement(2, 0, 2.5);
  matrix1.setMatrixElement(2, 1, 3.5);
  matrix1.setMatrixElement(2, 2, 2.5);

  S21Matrix inv_matrix = matrix1.InverseMatrix();

  S21Matrix check_matrix{3, 3};
  EXPECT_EQ(check_matrix.getCols(), 3);
  EXPECT_EQ(check_matrix.getRows(), 3);

  check_matrix.setMatrixElement(0, 0, 1.0);
  check_matrix.setMatrixElement(1, 1, 1.0);
  check_matrix.setMatrixElement(2, 2, 1.0);

  ASSERT_TRUE(check_matrix == inv_matrix * matrix1);
}