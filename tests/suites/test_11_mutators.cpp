#include "../test.h"

TEST(TestMutators, TestColsSetException1) {
  S21Matrix matrix1;
  EXPECT_EQ(matrix1.getCols(), 0);
  EXPECT_EQ(matrix1.getRows(), 0);

  EXPECT_ANY_THROW(matrix1.setCols(-1));
}

TEST(TestMutators, TestColsSetException2) {
  S21Matrix matrix1{2, 2};
  EXPECT_EQ(matrix1.getCols(), 2);
  EXPECT_EQ(matrix1.getRows(), 2);

  S21Matrix m_before = matrix1;

  EXPECT_ANY_THROW(matrix1.setCols(-1));
  ASSERT_TRUE(m_before == matrix1);
}

TEST(TestMutators, TestRowsSetException1) {
  S21Matrix matrix1;
  EXPECT_EQ(matrix1.getCols(), 0);
  EXPECT_EQ(matrix1.getRows(), 0);

  EXPECT_ANY_THROW(matrix1.setRows(-1));
}

TEST(TestMutators, TestRowsSetException2) {
  S21Matrix matrix1{2, 2};
  EXPECT_EQ(matrix1.getCols(), 2);
  EXPECT_EQ(matrix1.getRows(), 2);

  S21Matrix m_before = matrix1;

  EXPECT_ANY_THROW(matrix1.setRows(-1));
  ASSERT_TRUE(m_before == matrix1);
}

TEST(TestMutators, TestElementSetException1) {
  S21Matrix matrix1;
  EXPECT_EQ(matrix1.getCols(), 0);
  EXPECT_EQ(matrix1.getRows(), 0);

  EXPECT_ANY_THROW(matrix1.setMatrixElement(1, 1, -1));
}

TEST(TestMutators, TestElementSetException2) {
  S21Matrix matrix1{2, 2};
  EXPECT_EQ(matrix1.getCols(), 2);
  EXPECT_EQ(matrix1.getRows(), 2);

  EXPECT_ANY_THROW(matrix1.setMatrixElement(-1, 1, -1));
}

TEST(TestMutators, TestElementSetException3) {
  S21Matrix matrix1{2, 2};
  EXPECT_EQ(matrix1.getCols(), 2);
  EXPECT_EQ(matrix1.getRows(), 2);

  EXPECT_ANY_THROW(matrix1.setMatrixElement(1, -1, -1));
}

TEST(TestMutators, TestColsSet1) {
  S21Matrix matrix1;
  EXPECT_EQ(matrix1.getCols(), 0);
  EXPECT_EQ(matrix1.getRows(), 0);

  EXPECT_NO_THROW(matrix1.setCols(1));
  EXPECT_EQ(matrix1.getCols(), 1);
}

TEST(TestMutators, TestColsSet2) {
  S21Matrix matrix1{1, 1};
  EXPECT_EQ(matrix1.getCols(), 1);
  EXPECT_EQ(matrix1.getRows(), 1);
  EXPECT_NO_THROW(matrix1.setMatrixElement(0, 0, 1));
  S21Matrix check_matrix{1, 3};
  EXPECT_NO_THROW(check_matrix.setMatrixElement(0, 0, 1));

  EXPECT_NO_THROW(matrix1.setCols(3));
  EXPECT_EQ(matrix1.getCols(), 3);
  ASSERT_TRUE(matrix1 == check_matrix);
}

TEST(TestMutators, TestRowsSet1) {
  S21Matrix matrix1;
  EXPECT_EQ(matrix1.getCols(), 0);
  EXPECT_EQ(matrix1.getRows(), 0);

  EXPECT_NO_THROW(matrix1.setRows(1));
  EXPECT_EQ(matrix1.getRows(), 1);
}

TEST(TestMutators, TestRowsSet2) {
  S21Matrix matrix1{1, 1};
  EXPECT_EQ(matrix1.getCols(), 1);
  EXPECT_EQ(matrix1.getRows(), 1);
  EXPECT_NO_THROW(matrix1.setMatrixElement(0, 0, 1));
  S21Matrix check_matrix{3, 1};
  EXPECT_NO_THROW(check_matrix.setMatrixElement(0, 0, 1));

  EXPECT_NO_THROW(matrix1.setRows(3));
  EXPECT_EQ(matrix1.getRows(), 3);
  ASSERT_TRUE(matrix1 == check_matrix);
}