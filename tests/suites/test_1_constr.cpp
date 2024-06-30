#include "../test.h"

TEST(TestDefaultCostructor, VariableDeclaration) {
    S21Matrix testMatrix;

    EXPECT_EQ(testMatrix.getRows(), 0);
    EXPECT_EQ(testMatrix.getCols(), 0);
}

// Exception test for parametrized constructor
TEST(TestParamConstructor, TestExceptionNegativeColValue) {
    EXPECT_ANY_THROW(S21Matrix(-1, 1));
}

TEST(TestParamConstructor, TestExceptionNegativeRowValue) {
    EXPECT_ANY_THROW(S21Matrix(1, -1));
}

TEST(TestParamConstructor, TestExceptionNegativeValuesOfDimentions1) {
    EXPECT_ANY_THROW(S21Matrix(-1, -1));
}

TEST(TestParamConstructor, TestExceptionNegativeValuesOfDimentions2) {
    EXPECT_ANY_THROW(S21Matrix(-100, -100));
}

TEST(TestParamConstructor, TestMatrixCreationZeroDimValues1) {
    S21Matrix testMatrix(0, 0);

    EXPECT_EQ(testMatrix.getRows(), 0);
    EXPECT_EQ(testMatrix.getCols(), 0);
}

TEST(TestParamConstructor, TestMatrixCreationZeroDimValues2) {
    S21Matrix testMatrix(0, 100);

    EXPECT_EQ(testMatrix.getRows(), 0);
    EXPECT_EQ(testMatrix.getCols(), 0);
}

TEST(TestParamConstructor, TestMatrixCreationZeroDimValues3) {
    S21Matrix testMatrix(100, 0);

    EXPECT_EQ(testMatrix.getRows(), 0);
    EXPECT_EQ(testMatrix.getCols(), 0);
}

TEST(TestParamConstructor, TestMatrixCreationPositiveValues1) {
    S21Matrix testMatrix(2, 2);
    double val = 1.0;

    testMatrix.setMatrixElement(0, 0, val);
    testMatrix.setMatrixElement(0, 1, val);
    testMatrix.setMatrixElement(1, 0, val);
    testMatrix.setMatrixElement(1, 1, val);

    EXPECT_EQ(testMatrix.getRows(), 2);
    EXPECT_EQ(testMatrix.getCols(), 2);

    for (int i = 0; i < testMatrix.getRows(); i++) {
      for (int j = 0; j < testMatrix.getCols(); j++) {
        ASSERT_NEAR(testMatrix(i, j), 1.0, EQ_PRECISE);
      }
    }
}

TEST(TestParamConstructor, TestMatrixCreationPositiveValues2) {
    S21Matrix testMatrix(2, 2);
    double val = 1.000000099;

    testMatrix.setMatrixElement(0, 0, val);
    testMatrix.setMatrixElement(0, 1, val);
    testMatrix.setMatrixElement(1, 0, val);
    testMatrix.setMatrixElement(1, 1, val);

    EXPECT_EQ(testMatrix.getRows(), 2);
    EXPECT_EQ(testMatrix.getCols(), 2);

    for (int i = 0; i < testMatrix.getRows(); i++) {
      for (int j = 0; j < testMatrix.getCols(); j++) {
        ASSERT_NEAR(testMatrix(i, j), 1.0, EQ_PRECISE);
      }
    }
}