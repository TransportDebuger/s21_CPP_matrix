#include "../test.h"

TEST(TestSummarization, TestSumFunctionException1) {
  S21Matrix matrix1;
  S21Matrix matrix2{2, 3};

  EXPECT_ANY_THROW(matrix1.SumMatrix(matrix2));
  EXPECT_ANY_THROW(matrix2.SumMatrix(matrix1));
}

TEST(TestSummarization, TestSumFunctionException2) {
  S21Matrix matrix1{2, 2};
  S21Matrix matrix2{2, 3};

  EXPECT_ANY_THROW(matrix1.SumMatrix(matrix2));
  EXPECT_ANY_THROW(matrix2.SumMatrix(matrix1));
}

TEST(TestSummarization, TestSumFunctionException3) {
  S21Matrix matrix1{2, 2};
  S21Matrix matrix2{3, 2};

  EXPECT_ANY_THROW(matrix1.SumMatrix(matrix2));
  EXPECT_ANY_THROW(matrix2.SumMatrix(matrix1));
}

TEST(TestSummarization, TestSumFunctionException4) {
  S21Matrix matrix1{2, 2};
  S21Matrix matrix2{2, 3};

  test_helper::FillMatrix(matrix1, 1.0);
  test_helper::FillMatrix(matrix2, 2.0);

  EXPECT_ANY_THROW(matrix1.SumMatrix(matrix2));
  EXPECT_ANY_THROW(matrix2.SumMatrix(matrix1));
}

TEST(TestSummarization, TestSumOperatorException1) {
  S21Matrix matrix1;
  S21Matrix matrix2{2, 3};

  EXPECT_ANY_THROW(matrix1 + matrix2);
  EXPECT_ANY_THROW(matrix2 + matrix1);
}

TEST(TestSummarization, TestSumOperatorException2) {
  S21Matrix matrix1{2, 2};
  S21Matrix matrix2{2, 3};

  EXPECT_ANY_THROW(matrix1 + matrix2);
  EXPECT_ANY_THROW(matrix2 + matrix1);
}

TEST(TestSummarization, TestSumOperatorException3) {
  S21Matrix matrix1{2, 2};
  S21Matrix matrix2{3, 2};

  EXPECT_ANY_THROW(matrix1 + matrix2);
  EXPECT_ANY_THROW(matrix2 + matrix1);
}

TEST(TestSummarization, TestSumOperatorException4) {
  S21Matrix matrix1{2, 2};
  S21Matrix matrix2{2, 3};

  test_helper::FillMatrix(matrix1, 1.0);
  test_helper::FillMatrix(matrix2, 2.0);

  EXPECT_ANY_THROW(matrix1 + matrix2);
  EXPECT_ANY_THROW(matrix2 + matrix1);
}

TEST(TestSummarization, TestSumFunction1) {
  S21Matrix matrix1{100, 105};
  EXPECT_EQ(matrix1.getRows(), 100);
  EXPECT_EQ(matrix1.getCols(), 105);

  S21Matrix matrix2{100, 105};
  EXPECT_EQ(matrix2.getRows(), 100);
  EXPECT_EQ(matrix2.getCols(), 105);

  test_helper::FillMatrix(matrix1, 2.2);
  test_helper::FillMatrix(matrix2, 2.8);

  matrix1.SumMatrix(matrix2);

  test_helper::CheckMatrix(matrix1, 5.0);

  matrix2.SumMatrix(matrix1);

  test_helper::CheckMatrix(matrix2, 7.8);
}

TEST(TestSummarization, TestSumFunction2) {
  S21Matrix matrix1{99, 99};
  EXPECT_EQ(matrix1.getRows(), 99);
  EXPECT_EQ(matrix1.getCols(), 99);

  S21Matrix matrix2{99, 99};
  EXPECT_EQ(matrix2.getRows(), 99);
  EXPECT_EQ(matrix2.getCols(), 99);

  test_helper::FillMatrix(matrix1, 2.5);
  test_helper::FillMatrix(matrix2, -2.5);

  matrix1.SumMatrix(matrix2);

  test_helper::CheckMatrix(matrix1, 0.0);

  matrix2.SumMatrix(matrix1);

  test_helper::CheckMatrix(matrix2, -2.5);
}

TEST(TestSummarization, TestSumFunction3) {
  S21Matrix matrix1{4, 3};
  EXPECT_EQ(matrix1.getRows(), 4);
  EXPECT_EQ(matrix1.getCols(), 3);

  S21Matrix matrix2{4, 3};
  EXPECT_EQ(matrix2.getRows(), 4);
  EXPECT_EQ(matrix2.getCols(), 3);

  S21Matrix check_matrix{4, 3};
  EXPECT_EQ(matrix2.getRows(), 4);
  EXPECT_EQ(matrix2.getCols(), 3);

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

  matrix2.setMatrixElement(0, 0, 0.0);
  matrix2.setMatrixElement(0, 1, 1.0);
  matrix2.setMatrixElement(0, 2, 2.0);
  matrix2.setMatrixElement(1, 0, 3.0);
  matrix2.setMatrixElement(1, 1, 0.0);
  matrix2.setMatrixElement(1, 2, 4.0);
  matrix2.setMatrixElement(2, 0, -1.0);
  matrix2.setMatrixElement(2, 1, -2.0);
  matrix2.setMatrixElement(2, 2, 0.0);
  matrix2.setMatrixElement(3, 0, -3.0);
  matrix2.setMatrixElement(3, 1, 0.0);
  matrix2.setMatrixElement(3, 2, 4.0);

  check_matrix.setMatrixElement(0, 0, 1.5);
  check_matrix.setMatrixElement(0, 1, 3.5);
  check_matrix.setMatrixElement(0, 2, 5.5);
  check_matrix.setMatrixElement(1, 0, 1.5);
  check_matrix.setMatrixElement(1, 1, -2.5);
  check_matrix.setMatrixElement(1, 2, 0.5);
  check_matrix.setMatrixElement(2, 0, -1.0);
  check_matrix.setMatrixElement(2, 1, -2.0);
  check_matrix.setMatrixElement(2, 2, 0.0);
  check_matrix.setMatrixElement(3, 0, -2.0);
  check_matrix.setMatrixElement(3, 1, 1.0);
  check_matrix.setMatrixElement(3, 2, 5.0);

  matrix1.SumMatrix(matrix2);

  EXPECT_TRUE(matrix1 == check_matrix);
}

TEST(TestSummarization, TestSumFunction4) {
  S21Matrix matrix1{2, 2};
  EXPECT_EQ(matrix1.getRows(), 2);
  EXPECT_EQ(matrix1.getCols(), 2);

  S21Matrix matrix2{2, 2};
  EXPECT_EQ(matrix2.getRows(), 2);
  EXPECT_EQ(matrix2.getCols(), 2);

  S21Matrix check_matrix{2, 2};
  EXPECT_EQ(matrix2.getRows(), 2);
  EXPECT_EQ(matrix2.getCols(), 2);

  matrix1.setMatrixElement(0, 0, 145678000.588);
  matrix1.setMatrixElement(0, 1, -4542);
  matrix1.setMatrixElement(1, 0, 673552.54545324);
  matrix1.setMatrixElement(1, 1, 145678000.588);

  matrix2.setMatrixElement(0, 0, 14567800.777);
  matrix2.setMatrixElement(0, 1, -4542);
  matrix2.setMatrixElement(1, 0, 3.0);
  matrix2.setMatrixElement(1, 1, 0.0);

  check_matrix.setMatrixElement(0, 0, 160245801.365);
  check_matrix.setMatrixElement(0, 1, -9084);
  check_matrix.setMatrixElement(1, 0, 673555.54545324);
  check_matrix.setMatrixElement(1, 1, 145678000.588);

  matrix1.SumMatrix(matrix2);

  EXPECT_TRUE(matrix1 == check_matrix);
}

TEST(TestSummarization, TestSumOperator1) {
  S21Matrix matrix1{95, 99};
  EXPECT_EQ(matrix1.getRows(), 95);
  EXPECT_EQ(matrix1.getCols(), 99);

  S21Matrix matrix2{95, 99};
  EXPECT_EQ(matrix2.getRows(), 95);
  EXPECT_EQ(matrix2.getCols(), 99);

  test_helper::FillMatrix(matrix1, 2.5);
  test_helper::FillMatrix(matrix2, 3.5);

  S21Matrix result = matrix1 + matrix2;

  EXPECT_EQ(result.getRows(), 95);
  EXPECT_EQ(result.getCols(), 99);
  test_helper::CheckMatrix(result, 2.5 + 3.5);
}

TEST(TestSummarization, TestSumOperator2) {
  S21Matrix matrix1{99, 99};
  EXPECT_EQ(matrix1.getRows(), 99);
  EXPECT_EQ(matrix1.getCols(), 99);

  S21Matrix matrix2{99, 99};
  EXPECT_EQ(matrix2.getRows(), 99);
  EXPECT_EQ(matrix2.getCols(), 99);

  test_helper::FillMatrix(matrix1, 2.5);
  test_helper::FillMatrix(matrix2, -2.5);

  S21Matrix result = matrix1 + matrix2;

  EXPECT_EQ(result.getRows(), 99);
  EXPECT_EQ(result.getCols(), 99);
  test_helper::CheckMatrix(result, 0.0);
}

TEST(TestSummarization, TestSumOperator3) {
  S21Matrix matrix1{4, 3};
  EXPECT_EQ(matrix1.getRows(), 4);
  EXPECT_EQ(matrix1.getCols(), 3);

  S21Matrix matrix2{4, 3};
  EXPECT_EQ(matrix2.getRows(), 4);
  EXPECT_EQ(matrix2.getCols(), 3);

  S21Matrix check_matrix{4, 3};
  EXPECT_EQ(matrix2.getRows(), 4);
  EXPECT_EQ(matrix2.getCols(), 3);

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

  matrix2.setMatrixElement(0, 0, 0.0);
  matrix2.setMatrixElement(0, 1, 1.0);
  matrix2.setMatrixElement(0, 2, 2.0);
  matrix2.setMatrixElement(1, 0, 3.0);
  matrix2.setMatrixElement(1, 1, 0.0);
  matrix2.setMatrixElement(1, 2, 4.0);
  matrix2.setMatrixElement(2, 0, -1.0);
  matrix2.setMatrixElement(2, 1, -2.0);
  matrix2.setMatrixElement(2, 2, 0.0);
  matrix2.setMatrixElement(3, 0, -3.0);
  matrix2.setMatrixElement(3, 1, 0.0);
  matrix2.setMatrixElement(3, 2, 4.0);

  check_matrix.setMatrixElement(0, 0, 1.5);
  check_matrix.setMatrixElement(0, 1, 3.5);
  check_matrix.setMatrixElement(0, 2, 5.5);
  check_matrix.setMatrixElement(1, 0, 1.5);
  check_matrix.setMatrixElement(1, 1, -2.5);
  check_matrix.setMatrixElement(1, 2, 0.5);
  check_matrix.setMatrixElement(2, 0, -1.0);
  check_matrix.setMatrixElement(2, 1, -2.0);
  check_matrix.setMatrixElement(2, 2, 0.0);
  check_matrix.setMatrixElement(3, 0, -2.0);
  check_matrix.setMatrixElement(3, 1, 1.0);
  check_matrix.setMatrixElement(3, 2, 5.0);

  S21Matrix result = matrix1 + matrix2;

  EXPECT_EQ(result.getRows(), 4);
  EXPECT_EQ(result.getCols(), 3);

  EXPECT_TRUE(result == check_matrix);
}

TEST(TestSummarization, TestSumOperator4) {
  S21Matrix matrix1{2, 2};
  EXPECT_EQ(matrix1.getRows(), 2);
  EXPECT_EQ(matrix1.getCols(), 2);

  S21Matrix matrix2{2, 2};
  EXPECT_EQ(matrix2.getRows(), 2);
  EXPECT_EQ(matrix2.getCols(), 2);

  S21Matrix check_matrix{2, 2};
  EXPECT_EQ(matrix2.getRows(), 2);
  EXPECT_EQ(matrix2.getCols(), 2);

  matrix1.setMatrixElement(0, 0, 145678000.588);
  matrix1.setMatrixElement(0, 1, -4542);
  matrix1.setMatrixElement(1, 0, 673552.54545324);
  matrix1.setMatrixElement(1, 1, 145678000.588);

  matrix2.setMatrixElement(0, 0, 14567800.777);
  matrix2.setMatrixElement(0, 1, -4542);
  matrix2.setMatrixElement(1, 0, 3.0);
  matrix2.setMatrixElement(1, 1, 0.0);

  check_matrix.setMatrixElement(0, 0, 160245801.365);
  check_matrix.setMatrixElement(0, 1, -9084);
  check_matrix.setMatrixElement(1, 0, 673555.54545324);
  check_matrix.setMatrixElement(1, 1, 145678000.588);

  S21Matrix result = matrix1 + matrix2;

  EXPECT_EQ(result.getRows(), 2);
  EXPECT_EQ(result.getCols(), 2);

  EXPECT_TRUE(result == check_matrix);
}

TEST(TestSummarization, TestSumOperator5) {
  S21Matrix matrix1{95, 99};
  EXPECT_EQ(matrix1.getRows(), 95);
  EXPECT_EQ(matrix1.getCols(), 99);

  S21Matrix matrix2{95, 99};
  EXPECT_EQ(matrix2.getRows(), 95);
  EXPECT_EQ(matrix2.getCols(), 99);

  test_helper::FillMatrix(matrix1, 2.5);
  test_helper::FillMatrix(matrix2, 3.5);

  S21Matrix result{95, 99};

  result += matrix1;

  EXPECT_EQ(result.getRows(), 95);
  EXPECT_EQ(result.getCols(), 99);
  test_helper::CheckMatrix(result, 2.5);

  result += matrix2;

  EXPECT_EQ(result.getRows(), 95);
  EXPECT_EQ(result.getCols(), 99);
  test_helper::CheckMatrix(result, 2.5 + 3.5);
}

TEST(TestSummarization, TestSumSetOperator1) {
  S21Matrix matrix1{95, 99};
  EXPECT_EQ(matrix1.getRows(), 95);
  EXPECT_EQ(matrix1.getCols(), 99);

  S21Matrix matrix2{95, 99};
  EXPECT_EQ(matrix2.getRows(), 95);
  EXPECT_EQ(matrix2.getCols(), 99);

  test_helper::FillMatrix(matrix1, 2.5);
  test_helper::FillMatrix(matrix2, 3.5);

  matrix1 += matrix2;

  test_helper::CheckMatrix(matrix1, 6.0);

  matrix2 += matrix1;

  test_helper::CheckMatrix(matrix2, 9.5);

  matrix1 += matrix1;

  test_helper::CheckMatrix(matrix1, 12.0);
}