#include "../test.h"

TEST(TestSubstruction, TestSubFunctionException1) {
  S21Matrix matrix1;
  S21Matrix matrix2{2, 3};

  EXPECT_ANY_THROW(matrix1.SubMatrix(matrix2));
  EXPECT_ANY_THROW(matrix2.SubMatrix(matrix1));
}

TEST(TestSubstruction, TestSubFunctionException2) {
  S21Matrix matrix1{2, 2};
  S21Matrix matrix2{2, 3};

  EXPECT_ANY_THROW(matrix1.SubMatrix(matrix2));
  EXPECT_ANY_THROW(matrix2.SubMatrix(matrix1));
}

TEST(TestSubstruction, TestSubFunctionException3) {
  S21Matrix matrix1{2, 2};
  S21Matrix matrix2{3, 2};

  EXPECT_ANY_THROW(matrix1.SubMatrix(matrix2));
  EXPECT_ANY_THROW(matrix2.SubMatrix(matrix1));
}

TEST(TestSubstruction, TestSubFunctionException4) {
  S21Matrix matrix1{2, 2};
  S21Matrix matrix2{2, 3};

  test_helper::FillMatrix(matrix1, 1.0);
  test_helper::FillMatrix(matrix2, 2.0);

  EXPECT_ANY_THROW(matrix1.SubMatrix(matrix2));
  EXPECT_ANY_THROW(matrix2.SubMatrix(matrix1));
}

TEST(TestSubstruction, TestSubOperatorException1) {
  S21Matrix matrix1;
  S21Matrix matrix2{2, 3};

  EXPECT_ANY_THROW(matrix1 - matrix2);
  EXPECT_ANY_THROW(matrix2 - matrix1);
}

TEST(TestSubstruction, TestSubOperatorException2) {
  S21Matrix matrix1{2, 2};
  S21Matrix matrix2{2, 3};

  EXPECT_ANY_THROW(matrix1 - matrix2);
  EXPECT_ANY_THROW(matrix2 - matrix1);
}

TEST(TestSubstruction, TestSubOperatorException3) {
  S21Matrix matrix1{2, 2};
  S21Matrix matrix2{3, 2};

  EXPECT_ANY_THROW(matrix1 - matrix2);
  EXPECT_ANY_THROW(matrix2 - matrix1);
}

TEST(TestSubstruction, TestSubOperatorException4) {
  S21Matrix matrix1{2, 2};
  S21Matrix matrix2{2, 3};

  test_helper::FillMatrix(matrix1, 1.0);
  test_helper::FillMatrix(matrix2, 2.0);

  EXPECT_ANY_THROW(matrix1 - matrix2);
  EXPECT_ANY_THROW(matrix2 - matrix1);
}

TEST(TestSubstruction, TestSubOperatorException5) {
  S21Matrix matrix1{2, 3};
  S21Matrix matrix2{2, 2};

  test_helper::FillMatrix(matrix1, 1.0);
  test_helper::FillMatrix(matrix2, 2.0);

  EXPECT_ANY_THROW(matrix1 -= matrix2);
  EXPECT_ANY_THROW(matrix2 -= matrix1);
}

TEST(TestSubstruction, TestSubOperatorException6) {
  S21Matrix matrix1{2, 2};
  S21Matrix matrix2{3, 2};

  test_helper::FillMatrix(matrix1, 1.0);
  test_helper::FillMatrix(matrix2, 2.0);

  EXPECT_ANY_THROW(matrix1 -= matrix2);
  EXPECT_ANY_THROW(matrix2 -= matrix1);
}

TEST(TestSubstruction, TestFunction1) {
  S21Matrix matrix1{95, 99};
  EXPECT_EQ(matrix1.getRows(), 95);
  EXPECT_EQ(matrix1.getCols(), 99);

  S21Matrix matrix2{95, 99};
  EXPECT_EQ(matrix2.getRows(), 95);
  EXPECT_EQ(matrix2.getCols(), 99);

  test_helper::FillMatrix(matrix1, 2.5);
  test_helper::FillMatrix(matrix2, 3.5);

  matrix1.SubMatrix(matrix2);

  test_helper::CheckMatrix(matrix1, -1.0);

  matrix2.SubMatrix(matrix1);

  test_helper::CheckMatrix(matrix2, 4.5);
}

TEST(TestSubstruction, TestFunction2) {
  S21Matrix matrix1{99, 99};
  EXPECT_EQ(matrix1.getRows(), 99);
  EXPECT_EQ(matrix1.getCols(), 99);

  S21Matrix matrix2{99, 99};
  EXPECT_EQ(matrix2.getRows(), 99);
  EXPECT_EQ(matrix2.getCols(), 99);

  test_helper::FillMatrix(matrix1, 2.5);
  test_helper::FillMatrix(matrix2, 3.5);

  matrix1.SubMatrix(matrix2);

  test_helper::CheckMatrix(matrix1, -1.0);

  matrix2.SubMatrix(matrix1);

  test_helper::CheckMatrix(matrix2, 4.5);
}

TEST(TestSubstruction, TestFunction3) {
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
  check_matrix.setMatrixElement(0, 1, 1.5);
  check_matrix.setMatrixElement(0, 2, 1.5);
  check_matrix.setMatrixElement(1, 0, -4.5);
  check_matrix.setMatrixElement(1, 1, -2.5);
  check_matrix.setMatrixElement(1, 2, -7.5);
  check_matrix.setMatrixElement(2, 0, 1.0);
  check_matrix.setMatrixElement(2, 1, 2.0);
  check_matrix.setMatrixElement(2, 2, 0.0);
  check_matrix.setMatrixElement(3, 0, 4.0);
  check_matrix.setMatrixElement(3, 1, 1.0);
  check_matrix.setMatrixElement(3, 2, -3.0);

  matrix1.SubMatrix(matrix2);

  EXPECT_TRUE(matrix1 == check_matrix);
}

TEST(TestSubstruction, TestFunction4) {
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

  check_matrix.setMatrixElement(0, 0, 131110199.811);
  check_matrix.setMatrixElement(0, 1, 0.0);
  check_matrix.setMatrixElement(1, 0, 673549.54545324);
  check_matrix.setMatrixElement(1, 1, 145678000.588);

  matrix1.SubMatrix(matrix2);

  EXPECT_TRUE(matrix1 == check_matrix);
}

TEST(TestSubstruction, TestOperator1) {
  S21Matrix matrix1{95, 99};
  EXPECT_EQ(matrix1.getRows(), 95);
  EXPECT_EQ(matrix1.getCols(), 99);

  S21Matrix matrix2{95, 99};
  EXPECT_EQ(matrix2.getRows(), 95);
  EXPECT_EQ(matrix2.getCols(), 99);

  test_helper::FillMatrix(matrix1, 2.5);
  test_helper::FillMatrix(matrix2, 3.5);

  S21Matrix result = matrix1 - matrix2;

  test_helper::CheckMatrix(result, -1.0);
}

TEST(TestSubstruction, TestOperator2) {
  S21Matrix matrix1{99, 99};
  EXPECT_EQ(matrix1.getRows(), 99);
  EXPECT_EQ(matrix1.getCols(), 99);

  S21Matrix matrix2{99, 99};
  EXPECT_EQ(matrix2.getRows(), 99);
  EXPECT_EQ(matrix2.getCols(), 99);

  test_helper::FillMatrix(matrix1, 2.5);
  test_helper::FillMatrix(matrix2, 3.5);

  S21Matrix result = matrix1 - matrix2;

  test_helper::CheckMatrix(result, -1.0);
}

TEST(TestSubstruction, TestOperator3) {
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
  check_matrix.setMatrixElement(0, 1, 1.5);
  check_matrix.setMatrixElement(0, 2, 1.5);
  check_matrix.setMatrixElement(1, 0, -4.5);
  check_matrix.setMatrixElement(1, 1, -2.5);
  check_matrix.setMatrixElement(1, 2, -7.5);
  check_matrix.setMatrixElement(2, 0, 1.0);
  check_matrix.setMatrixElement(2, 1, 2.0);
  check_matrix.setMatrixElement(2, 2, 0.0);
  check_matrix.setMatrixElement(3, 0, 4.0);
  check_matrix.setMatrixElement(3, 1, 1.0);
  check_matrix.setMatrixElement(3, 2, -3.0);

  S21Matrix result = matrix1 - matrix2;

  EXPECT_TRUE(result == check_matrix);
}

TEST(TestSubstruction, TestOperator4) {
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

  check_matrix.setMatrixElement(0, 0, 131110199.811);
  check_matrix.setMatrixElement(0, 1, 0.0);
  check_matrix.setMatrixElement(1, 0, 673549.54545324);
  check_matrix.setMatrixElement(1, 1, 145678000.588);

  S21Matrix result = matrix1 - matrix2;

  EXPECT_TRUE(result == check_matrix);
}

TEST(TestSubstruction, TestSubSetOperator1) {
  S21Matrix matrix1{95, 99};
  EXPECT_EQ(matrix1.getRows(), 95);
  EXPECT_EQ(matrix1.getCols(), 99);

  S21Matrix matrix2{95, 99};
  EXPECT_EQ(matrix2.getRows(), 95);
  EXPECT_EQ(matrix2.getCols(), 99);

  test_helper::FillMatrix(matrix1, 2.5);
  test_helper::FillMatrix(matrix2, 3.5);

  matrix1 -= matrix2;

  test_helper::CheckMatrix(matrix1, -1.0);
}

TEST(TestSubstruction, TestSubSetOperator2) {
  S21Matrix matrix1{99, 99};
  EXPECT_EQ(matrix1.getRows(), 99);
  EXPECT_EQ(matrix1.getCols(), 99);

  S21Matrix matrix2{99, 99};
  EXPECT_EQ(matrix2.getRows(), 99);
  EXPECT_EQ(matrix2.getCols(), 99);

  test_helper::FillMatrix(matrix1, 2.5);
  test_helper::FillMatrix(matrix2, 3.5);

  matrix1 -= matrix2;

  test_helper::CheckMatrix(matrix1, -1.0);
}

TEST(TestSubstruction, TestSubSetOperator3) {
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
  check_matrix.setMatrixElement(0, 1, 1.5);
  check_matrix.setMatrixElement(0, 2, 1.5);
  check_matrix.setMatrixElement(1, 0, -4.5);
  check_matrix.setMatrixElement(1, 1, -2.5);
  check_matrix.setMatrixElement(1, 2, -7.5);
  check_matrix.setMatrixElement(2, 0, 1.0);
  check_matrix.setMatrixElement(2, 1, 2.0);
  check_matrix.setMatrixElement(2, 2, 0.0);
  check_matrix.setMatrixElement(3, 0, 4.0);
  check_matrix.setMatrixElement(3, 1, 1.0);
  check_matrix.setMatrixElement(3, 2, -3.0);

  matrix1 -= matrix2;

  EXPECT_TRUE(matrix1 == check_matrix);
}

TEST(TestSubstruction, TestSubSetOperator4) {
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

  check_matrix.setMatrixElement(0, 0, 131110199.811);
  check_matrix.setMatrixElement(0, 1, 0.0);
  check_matrix.setMatrixElement(1, 0, 673549.54545324);
  check_matrix.setMatrixElement(1, 1, 145678000.588);

  matrix1 -= matrix2;

  EXPECT_TRUE(matrix1 == check_matrix);
}