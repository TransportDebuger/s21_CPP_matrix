#include "../test.h"

TEST(TestMulMatrix, TestMulMatrixFunctionException1) {
  S21Matrix matrix1{3, 2};
  S21Matrix matrix2{3, 2};

  EXPECT_ANY_THROW(matrix1.MulMatrix(matrix2));
  EXPECT_ANY_THROW(matrix2.MulMatrix(matrix1));
}

TEST(TestMulMatrix, TestMulMatrixFunctionException2) {
  S21Matrix matrix1{2, 2};
  S21Matrix matrix2{3, 3};

  EXPECT_ANY_THROW(matrix1.MulMatrix(matrix2));
  EXPECT_ANY_THROW(matrix2.MulMatrix(matrix1));
}

TEST(TestMulMatrix, TestMulMatrixFunctionException3) {
  S21Matrix matrix1;
  S21Matrix matrix2{3, 2};

  EXPECT_ANY_THROW(matrix1.MulMatrix(matrix2));
  EXPECT_ANY_THROW(matrix2.MulMatrix(matrix1));
}

TEST(TestMulMatrix, TestMulMatrixOperatorException1) {
  S21Matrix matrix1{3, 2};
  S21Matrix matrix2{3, 2};

  EXPECT_ANY_THROW(matrix1 * matrix2);
  EXPECT_ANY_THROW(matrix2 * matrix1);
}

TEST(TestMulMatrix, TestMulMatrixOperatorException2) {
  S21Matrix matrix1{3, 3};
  S21Matrix matrix2{2, 2};

  EXPECT_ANY_THROW(matrix1 * matrix2);
  EXPECT_ANY_THROW(matrix2 * matrix1);
}

TEST(TestMulMatrix, TestMulMatrixOperatorException3) {
  S21Matrix matrix1;
  S21Matrix matrix2{3, 2};

  EXPECT_ANY_THROW(matrix1 * matrix2);
  EXPECT_ANY_THROW(matrix2 * matrix1);
}

TEST(TestMulMatrix, TestMulMatrixOperator2Exception1) {
  S21Matrix matrix1{3, 2};
  S21Matrix matrix2{3, 2};

  EXPECT_ANY_THROW(matrix1 *= matrix2);
  EXPECT_ANY_THROW(matrix2 *= matrix1);
}

TEST(TestMulMatrix, TestMulMatrixOperator2Exception2) {
  S21Matrix matrix1{3, 3};
  S21Matrix matrix2{2, 2};

  EXPECT_ANY_THROW(matrix1 *= matrix2);
  EXPECT_ANY_THROW(matrix2 *= matrix1);
}

TEST(TestMulMatrix, TestMulMatrixOperator2Exception3) {
  S21Matrix matrix1;
  S21Matrix matrix2{3, 2};

  EXPECT_ANY_THROW(matrix1 *= matrix2);
  EXPECT_ANY_THROW(matrix2 *= matrix1);
}

TEST(TestMulMatrix, TestMulFunction1) {
  S21Matrix matrix1{2, 3};
  EXPECT_EQ(matrix1.getRows(), 2);
  EXPECT_EQ(matrix1.getCols(), 3);

  S21Matrix matrix2{3, 2};
  EXPECT_EQ(matrix2.getRows(), 3);
  EXPECT_EQ(matrix2.getCols(), 2);

  S21Matrix check_matrix{2, 2};
  EXPECT_EQ(check_matrix.getRows(), 2);
  EXPECT_EQ(check_matrix.getCols(), 2);

  test_helper::FillMatrix(matrix1, 1.0);
  test_helper::FillMatrix(matrix2, 1.0);
  test_helper::FillMatrix(check_matrix, 3.0);

  matrix1.MulMatrix(matrix2);

  EXPECT_EQ(matrix1.getRows(), 2);
  EXPECT_EQ(matrix1.getCols(), 2);

  ASSERT_TRUE(matrix1 == check_matrix);
}

TEST(TestMulMatrix, TestMulFunction2) {
  S21Matrix matrix1{3, 2};
  EXPECT_EQ(matrix1.getRows(), 3);
  EXPECT_EQ(matrix1.getCols(), 2);

  S21Matrix matrix2{2, 3};
  EXPECT_EQ(matrix2.getRows(), 2);
  EXPECT_EQ(matrix2.getCols(), 3);

  S21Matrix check_matrix{3, 3};
  EXPECT_EQ(check_matrix.getRows(), 3);
  EXPECT_EQ(check_matrix.getCols(), 3);

  test_helper::FillMatrix(matrix1, 1.0);
  test_helper::FillMatrix(matrix2, 1.0);
  test_helper::FillMatrix(check_matrix, 2.0);

  matrix1.MulMatrix(matrix2);

  EXPECT_EQ(matrix1.getRows(), 3);
  EXPECT_EQ(matrix1.getCols(), 3);

  ASSERT_TRUE(matrix1 == check_matrix);
}

TEST(TestMulMatrix, TestMulFunction3) {
  S21Matrix matrix1{2, 2};
  EXPECT_EQ(matrix1.getRows(), 2);
  EXPECT_EQ(matrix1.getCols(), 2);

  S21Matrix matrix2{2, 2};
  EXPECT_EQ(matrix2.getRows(), 2);
  EXPECT_EQ(matrix2.getCols(), 2);

  S21Matrix check_matrix{2, 2};
  EXPECT_EQ(check_matrix.getRows(), 2);
  EXPECT_EQ(check_matrix.getCols(), 2);

  matrix1.setMatrixElement(0, 0, 1);
  matrix1.setMatrixElement(0, 1, 2);
  matrix1.setMatrixElement(1, 0, 3);
  matrix1.setMatrixElement(1, 1, 4);

  matrix2.setMatrixElement(0, 0, 2);
  matrix2.setMatrixElement(0, 1, 3);
  matrix2.setMatrixElement(1, 0, 4);
  matrix2.setMatrixElement(1, 1, 5);

  check_matrix.setMatrixElement(0, 0, 10);
  check_matrix.setMatrixElement(0, 1, 13);
  check_matrix.setMatrixElement(1, 0, 22);
  check_matrix.setMatrixElement(1, 1, 29);

  matrix1.MulMatrix(matrix2);

  EXPECT_EQ(matrix1.getRows(), 2);
  EXPECT_EQ(matrix1.getCols(), 2);

  ASSERT_TRUE(matrix1 == check_matrix);
}

TEST(TestMulMatrix, TestMulFunction4) {
  S21Matrix matrix1{2, 2};
  EXPECT_EQ(matrix1.getRows(), 2);
  EXPECT_EQ(matrix1.getCols(), 2);

  S21Matrix matrix2{2, 3};
  EXPECT_EQ(matrix2.getRows(), 2);
  EXPECT_EQ(matrix2.getCols(), 3);

  S21Matrix check_matrix{2, 3};
  EXPECT_EQ(check_matrix.getRows(), 2);
  EXPECT_EQ(check_matrix.getCols(), 3);

  test_helper::FillMatrix(matrix1, 1.0);
  test_helper::FillMatrix(matrix2, 1.0);
  test_helper::FillMatrix(check_matrix, 2.0);

  matrix1.MulMatrix(matrix2);

  EXPECT_EQ(matrix1.getRows(), 2);
  EXPECT_EQ(matrix1.getCols(), 3);

  ASSERT_TRUE(matrix1 == check_matrix);
}

TEST(TestMulMatrix, TestMulOperator1) {
  S21Matrix matrix1{2, 3};
  EXPECT_EQ(matrix1.getRows(), 2);
  EXPECT_EQ(matrix1.getCols(), 3);

  S21Matrix matrix2{3, 2};
  EXPECT_EQ(matrix2.getRows(), 3);
  EXPECT_EQ(matrix2.getCols(), 2);

  S21Matrix check_matrix{2, 2};
  EXPECT_EQ(check_matrix.getRows(), 2);
  EXPECT_EQ(check_matrix.getCols(), 2);

  test_helper::FillMatrix(matrix1, 1.0);
  test_helper::FillMatrix(matrix2, 1.0);
  test_helper::FillMatrix(check_matrix, 3.0);

  S21Matrix result = matrix1 * matrix2;

  EXPECT_EQ(result.getRows(), 2);
  EXPECT_EQ(result.getCols(), 2);

  ASSERT_TRUE(result == check_matrix);
}

TEST(TestMulMatrix, TestMulOperator2) {
  S21Matrix matrix1{3, 2};
  EXPECT_EQ(matrix1.getRows(), 3);
  EXPECT_EQ(matrix1.getCols(), 2);

  S21Matrix matrix2{2, 3};
  EXPECT_EQ(matrix2.getRows(), 2);
  EXPECT_EQ(matrix2.getCols(), 3);

  S21Matrix check_matrix{3, 3};
  EXPECT_EQ(check_matrix.getRows(), 3);
  EXPECT_EQ(check_matrix.getCols(), 3);

  test_helper::FillMatrix(matrix1, 1.0);
  test_helper::FillMatrix(matrix2, 1.0);
  test_helper::FillMatrix(check_matrix, 2.0);

  S21Matrix result = matrix1 * matrix2;

  EXPECT_EQ(result.getRows(), 3);
  EXPECT_EQ(result.getCols(), 3);

  ASSERT_TRUE(result == check_matrix);
}

TEST(TestMulMatrix, TestMulOperator3) {
  S21Matrix matrix1{2, 2};
  EXPECT_EQ(matrix1.getRows(), 2);
  EXPECT_EQ(matrix1.getCols(), 2);

  S21Matrix matrix2{2, 2};
  EXPECT_EQ(matrix2.getRows(), 2);
  EXPECT_EQ(matrix2.getCols(), 2);

  S21Matrix check_matrix{2, 2};
  EXPECT_EQ(check_matrix.getRows(), 2);
  EXPECT_EQ(check_matrix.getCols(), 2);

  matrix1.setMatrixElement(0, 0, 1);
  matrix1.setMatrixElement(0, 1, 2);
  matrix1.setMatrixElement(1, 0, 3);
  matrix1.setMatrixElement(1, 1, 4);

  matrix2.setMatrixElement(0, 0, 2);
  matrix2.setMatrixElement(0, 1, 3);
  matrix2.setMatrixElement(1, 0, 4);
  matrix2.setMatrixElement(1, 1, 5);

  check_matrix.setMatrixElement(0, 0, 10);
  check_matrix.setMatrixElement(0, 1, 13);
  check_matrix.setMatrixElement(1, 0, 22);
  check_matrix.setMatrixElement(1, 1, 29);

  S21Matrix result = matrix1 * matrix2;

  EXPECT_EQ(result.getRows(), 2);
  EXPECT_EQ(result.getCols(), 2);

  ASSERT_TRUE(result == check_matrix);
}

TEST(TestMulMatrix, TestMulOperator4) {
  S21Matrix matrix1{2, 2};
  EXPECT_EQ(matrix1.getRows(), 2);
  EXPECT_EQ(matrix1.getCols(), 2);

  S21Matrix matrix2{2, 3};
  EXPECT_EQ(matrix2.getRows(), 2);
  EXPECT_EQ(matrix2.getCols(), 3);

  S21Matrix check_matrix{2, 3};
  EXPECT_EQ(check_matrix.getRows(), 2);
  EXPECT_EQ(check_matrix.getCols(), 3);

  test_helper::FillMatrix(matrix1, 1.0);
  test_helper::FillMatrix(matrix2, 1.0);
  test_helper::FillMatrix(check_matrix, 2.0);

  S21Matrix result = matrix1 * matrix2;

  EXPECT_EQ(result.getRows(), 2);
  EXPECT_EQ(result.getCols(), 3);

  ASSERT_TRUE(result == check_matrix);
}

TEST(TestMulMatrix, TestMulSetOperator1) {
  S21Matrix matrix1{2, 3};
  EXPECT_EQ(matrix1.getRows(), 2);
  EXPECT_EQ(matrix1.getCols(), 3);

  S21Matrix matrix2{3, 2};
  EXPECT_EQ(matrix2.getRows(), 3);
  EXPECT_EQ(matrix2.getCols(), 2);

  S21Matrix check_matrix{2, 2};
  EXPECT_EQ(check_matrix.getRows(), 2);
  EXPECT_EQ(check_matrix.getCols(), 2);

  test_helper::FillMatrix(matrix1, 1.0);
  test_helper::FillMatrix(matrix2, 1.0);
  test_helper::FillMatrix(check_matrix, 3.0);

  matrix1 *= matrix2;

  EXPECT_EQ(matrix1.getRows(), 2);
  EXPECT_EQ(matrix1.getCols(), 2);

  ASSERT_TRUE(matrix1 == check_matrix);
}

TEST(TestMulMatrix, TestMulSetOperator2) {
  S21Matrix matrix1{3, 2};
  EXPECT_EQ(matrix1.getRows(), 3);
  EXPECT_EQ(matrix1.getCols(), 2);

  S21Matrix matrix2{2, 3};
  EXPECT_EQ(matrix2.getRows(), 2);
  EXPECT_EQ(matrix2.getCols(), 3);

  S21Matrix check_matrix{3, 3};
  EXPECT_EQ(check_matrix.getRows(), 3);
  EXPECT_EQ(check_matrix.getCols(), 3);

  test_helper::FillMatrix(matrix1, 1.0);
  test_helper::FillMatrix(matrix2, 1.0);
  test_helper::FillMatrix(check_matrix, 2.0);

  matrix1 *= matrix2;

  EXPECT_EQ(matrix1.getRows(), 3);
  EXPECT_EQ(matrix1.getCols(), 3);

  ASSERT_TRUE(matrix1 == check_matrix);
}

TEST(TestMulMatrix, TestMulSetOperator3) {
  S21Matrix matrix1{2, 2};
  EXPECT_EQ(matrix1.getRows(), 2);
  EXPECT_EQ(matrix1.getCols(), 2);

  S21Matrix matrix2{2, 2};
  EXPECT_EQ(matrix2.getRows(), 2);
  EXPECT_EQ(matrix2.getCols(), 2);

  S21Matrix check_matrix{2, 2};
  EXPECT_EQ(check_matrix.getRows(), 2);
  EXPECT_EQ(check_matrix.getCols(), 2);

  matrix1.setMatrixElement(0, 0, 1);
  matrix1.setMatrixElement(0, 1, 2);
  matrix1.setMatrixElement(1, 0, 3);
  matrix1.setMatrixElement(1, 1, 4);

  matrix2.setMatrixElement(0, 0, 2);
  matrix2.setMatrixElement(0, 1, 3);
  matrix2.setMatrixElement(1, 0, 4);
  matrix2.setMatrixElement(1, 1, 5);

  check_matrix.setMatrixElement(0, 0, 10);
  check_matrix.setMatrixElement(0, 1, 13);
  check_matrix.setMatrixElement(1, 0, 22);
  check_matrix.setMatrixElement(1, 1, 29);

  matrix1 *= matrix2;

  EXPECT_EQ(matrix1.getRows(), 2);
  EXPECT_EQ(matrix1.getCols(), 2);

  ASSERT_TRUE(matrix1 == check_matrix);
}

TEST(TestMulMatrix, TestMulSetOperator4) {
  S21Matrix matrix1{2, 2};
  EXPECT_EQ(matrix1.getRows(), 2);
  EXPECT_EQ(matrix1.getCols(), 2);

  S21Matrix matrix2{2, 3};
  EXPECT_EQ(matrix2.getRows(), 2);
  EXPECT_EQ(matrix2.getCols(), 3);

  S21Matrix check_matrix{2, 3};
  EXPECT_EQ(check_matrix.getRows(), 2);
  EXPECT_EQ(check_matrix.getCols(), 3);

  test_helper::FillMatrix(matrix1, 1.0);
  test_helper::FillMatrix(matrix2, 1.0);
  test_helper::FillMatrix(check_matrix, 2.0);

  matrix1 *= matrix2;

  EXPECT_EQ(matrix1.getRows(), 2);
  EXPECT_EQ(matrix1.getCols(), 3);

  ASSERT_TRUE(matrix1 == check_matrix);
}