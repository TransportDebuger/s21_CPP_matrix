/**
 * @file test_matrix_arithmetic.cpp
 * @brief Тесты поэлементной арифметики: +, -, *, *=, ==.
 */

#include <gtest/gtest.h>
#include <limits>
#include <cmath>

#include "s21_matrix+.hpp"

using namespace s21;

template <typename T>
class MatrixArithmeticTest : public ::testing::Test {};
using TestTypes = ::testing::Types<float, double, long double>;
TYPED_TEST_SUITE(MatrixArithmeticTest, TestTypes);

// ============================================================================
// operator+ и operator+=
// ============================================================================
TYPED_TEST(MatrixArithmeticTest, OperatorPlus_SameDimensions) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType a(2, 3);
  a(0, 0) = TypeParam(1);
  a(0, 1) = TypeParam(2);
  a(0, 2) = TypeParam(3);
  a(1, 0) = TypeParam(4);
  a(1, 1) = TypeParam(5);
  a(1, 2) = TypeParam(6);
  
  MatrixType b(2, 3);
  b(0, 0) = TypeParam(7);
  b(0, 1) = TypeParam(8);
  b(0, 2) = TypeParam(9);
  b(1, 0) = TypeParam(10);
  b(1, 1) = TypeParam(11);
  b(1, 2) = TypeParam(12);
  
  MatrixType result = a + b;
  
  EXPECT_EQ(result.rows(), 2u);
  EXPECT_EQ(result.cols(), 3u);
  EXPECT_EQ(result(0, 0), TypeParam(8));
  EXPECT_EQ(result(1, 2), TypeParam(18));
}

TYPED_TEST(MatrixArithmeticTest, OperatorPlus_IncompatibleDimensions_Throws) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType a(2, 3);
  MatrixType b(3, 2);
  
  EXPECT_THROW(a + b, std::invalid_argument);
}

TYPED_TEST(MatrixArithmeticTest, OperatorPlusEquals_SameDimensions) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType a(2, 2);
  a(0, 0) = TypeParam(1);
  a(0, 1) = TypeParam(2);
  a(1, 0) = TypeParam(3);
  a(1, 1) = TypeParam(4);
  
  MatrixType b(2, 2);
  b(0, 0) = TypeParam(5);
  b(0, 1) = TypeParam(6);
  b(1, 0) = TypeParam(7);
  b(1, 1) = TypeParam(8);
  
  a += b;
  
  EXPECT_EQ(a.rows(), 2u);
  EXPECT_EQ(a.cols(), 2u);
  EXPECT_EQ(a(0, 0), TypeParam(6));
  EXPECT_EQ(a(1, 1), TypeParam(12));
}

TYPED_TEST(MatrixArithmeticTest, OperatorPlusEquals_IncompatibleDimensions_Throws) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType a(2, 3);
  MatrixType b(3, 2);
  
  EXPECT_THROW(a += b, std::invalid_argument);
}

// ============================================================================
// operator- и operator-=
// ============================================================================
TYPED_TEST(MatrixArithmeticTest, OperatorMinus_SameDimensions) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType a(2, 2);
  a(0, 0) = TypeParam(10);
  a(0, 1) = TypeParam(20);
  a(1, 0) = TypeParam(30);
  a(1, 1) = TypeParam(40);
  
  MatrixType b(2, 2);
  b(0, 0) = TypeParam(1);
  b(0, 1) = TypeParam(2);
  b(1, 0) = TypeParam(3);
  b(1, 1) = TypeParam(4);
  
  MatrixType result = a - b;
  
  EXPECT_EQ(result.rows(), 2u);
  EXPECT_EQ(result.cols(), 2u);
  EXPECT_EQ(result(0, 0), TypeParam(9));
  EXPECT_EQ(result(1, 1), TypeParam(36));
}

TYPED_TEST(MatrixArithmeticTest, OperatorMinus_IncompatibleDimensions_Throws) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType a(2, 3);
  MatrixType b(3, 2);
  
  EXPECT_THROW(a - b, std::invalid_argument);
}

TYPED_TEST(MatrixArithmeticTest, OperatorMinusEquals_SameDimensions) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType a(2, 2);
  a(0, 0) = TypeParam(10);
  a(0, 1) = TypeParam(20);
  a(1, 0) = TypeParam(30);
  a(1, 1) = TypeParam(40);
  
  MatrixType b(2, 2);
  b(0, 0) = TypeParam(1);
  b(0, 1) = TypeParam(2);
  b(1, 0) = TypeParam(3);
  b(1, 1) = TypeParam(4);
  
  a -= b;
  
  EXPECT_EQ(a(0, 0), TypeParam(9));
  EXPECT_EQ(a(1, 1), TypeParam(36));
}

// ============================================================================
// operator* (скаляр) и operator*= (скаляр)
// ============================================================================
TYPED_TEST(MatrixArithmeticTest, OperatorScalarMultiply) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType m(2, 3);
  m(0, 0) = TypeParam(1);
  m(0, 1) = TypeParam(2);
  m(0, 2) = TypeParam(3);
  m(1, 0) = TypeParam(4);
  m(1, 1) = TypeParam(5);
  m(1, 2) = TypeParam(6);
  
  MatrixType result = m * TypeParam(2);
  
  EXPECT_EQ(result.rows(), 2u);
  EXPECT_EQ(result.cols(), 3u);
  EXPECT_EQ(result(0, 0), TypeParam(2));
  EXPECT_EQ(result(1, 2), TypeParam(12));
}

TYPED_TEST(MatrixArithmeticTest, OperatorScalarMultiplyByZero) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType m(2, 2);
  m(0, 0) = TypeParam(42);
  
  MatrixType result = m * TypeParam(0);
  
  EXPECT_EQ(result(0, 0), TypeParam(0));
}

TYPED_TEST(MatrixArithmeticTest, OperatorScalarMultiplyEquals) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType m(2, 2);
  m(0, 0) = TypeParam(3);
  m(1, 1) = TypeParam(4);
  
  m *= TypeParam(5);
  
  EXPECT_EQ(m(0, 0), TypeParam(15));
  EXPECT_EQ(m(1, 1), TypeParam(20));
}

// ============================================================================
// operator== с учетом kEpsilon
// ============================================================================
TYPED_TEST(MatrixArithmeticTest, OperatorEquals_SameMatrices) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType a(2, 2);
  a(0, 0) = TypeParam(1.0);
  a(0, 1) = TypeParam(2.0);
  a(1, 0) = TypeParam(3.0);
  a(1, 1) = TypeParam(4.0);
  
  MatrixType b(2, 2);
  b(0, 0) = TypeParam(1.0);
  b(0, 1) = TypeParam(2.0);
  b(1, 0) = TypeParam(3.0);
  b(1, 1) = TypeParam(4.0);
  
  EXPECT_TRUE(a == b);
}

TYPED_TEST(MatrixArithmeticTest, OperatorEquals_DifferentDimensions) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType a(2, 3);
  MatrixType b(3, 2);
  
  EXPECT_FALSE(a == b);
}

TYPED_TEST(MatrixArithmeticTest, OperatorEquals_WithinEpsilon) {
  using MatrixType = Matrix<TypeParam>;
  
  const TypeParam epsilon = MatrixType::kEpsilon;
  
  MatrixType a(1, 1);
  a(0, 0) = TypeParam(1.0);
  
  MatrixType b(1, 1);
  b(0, 0) = TypeParam(1.0) + epsilon / TypeParam(2);  // В пределах эпсилона
  
  EXPECT_TRUE(a == b);
}

TYPED_TEST(MatrixArithmeticTest, OperatorEquals_BeyondEpsilon) {
  using MatrixType = Matrix<TypeParam>;
  
  const TypeParam epsilon = MatrixType::kEpsilon;
  
  MatrixType a(1, 1);
  a(0, 0) = TypeParam(1.0);
  
  MatrixType b(1, 1);
  b(0, 0) = TypeParam(1.0) + epsilon * TypeParam(2);  // За пределами эпсилона
  
  EXPECT_FALSE(a == b);
}

TYPED_TEST(MatrixArithmeticTest, OperatorEquals_EmptyMatrices) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType a;
  MatrixType b;
  
  EXPECT_TRUE(a == b);
}

TYPED_TEST(MatrixArithmeticTest, OperatorEquals_OneEmpty) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType a;
  MatrixType b(1, 1);
  
  EXPECT_FALSE(a == b);
}

TYPED_TEST(MatrixArithmeticTest, OperatorEquals_WithNaN) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType a(1, 1);
  a(0, 0) = TypeParam(1.0);
  
  MatrixType b(1, 1);
  b(0, 0) = std::numeric_limits<TypeParam>::quiet_NaN();
  
  EXPECT_FALSE(a == b);
  EXPECT_FALSE(b == a);
}

// ============================================================================
// Сравнение размерностей (invalid_argument)
// ============================================================================
TYPED_TEST(MatrixArithmeticTest, SizeMismatch_Throws) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType a(2, 3);
  MatrixType b(3, 2);
  MatrixType c(2, 2);
  
  EXPECT_THROW(a + c, std::invalid_argument);
  EXPECT_THROW(a - c, std::invalid_argument);
  EXPECT_THROW(a += c, std::invalid_argument);
  EXPECT_THROW(a -= c, std::invalid_argument);
}

// ============================================================================
// Тесты для граничных случаев
// ============================================================================
TYPED_TEST(MatrixArithmeticTest, EdgeCases_PaddingMatrixOperations) {
  using MatrixType = Matrix<TypeParam>;
  
  // Сложение с пустой матрицей
  MatrixType a;
  MatrixType b;
  
  EXPECT_TRUE((a + b) == MatrixType());
  
  // Умножение на ноль
  MatrixType m(2, 2);
  m(0, 0) = TypeParam(100);
  MatrixType result = m * TypeParam(0);
  EXPECT_EQ(result(0, 0), TypeParam(0));
}

//тест цепочки операций
TYPED_TEST(MatrixArithmeticTest, ChainedOperations) {
    using MatrixType = Matrix<TypeParam>;
    MatrixType a(2, 2);
    a(0, 0) = TypeParam(1);
    a(1, 1) = TypeParam(2);
    
    MatrixType b(2, 2);
    b(0, 0) = TypeParam(3);
    b(1, 1) = TypeParam(4);
    
    // Цепочка операций
    MatrixType result = (a + b) * TypeParam(2) - a;
    EXPECT_EQ(result.rows(), 2u);
    EXPECT_EQ(result.cols(), 2u);
}