#include "test_helper.h"

void test_helper::CheckMatrix(S21Matrix& matrix, double value) {
  for (int i = 0; i < matrix.getRows(); ++i) {
    for (int j = 0; j < matrix.getCols(); ++j) {
      ASSERT_NEAR(matrix.getMatrixElement(i, j), value, EQ_PRECISE);
    }
  }
}

void test_helper::FillMatrix(S21Matrix& matrix, double value) {
  for (int i = 0; i < matrix.getRows(); ++i) {
    for (int j = 0; j < matrix.getCols(); ++j) {
      matrix.setMatrixElement(i, j, value);
    }
  }
}