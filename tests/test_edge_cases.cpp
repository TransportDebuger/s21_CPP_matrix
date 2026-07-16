/**
 * @file test_edge_cases.cpp
 * @brief Тесты граничных условий, вырожденных матриц, NaN/Inf и переполнения.
 */

#include <gtest/gtest.h>
#include <limits>
#include <cmath>

#include "s21_matrix+.hpp"

using namespace s21;

using TestTypes = ::testing::Types<float, double, long double>;
TYPED_TEST_SUITE(MatrixEdgeCasesTest, TestTypes);

// ============================================================================
// Пустые матрицы (0×0)
// ============================================================================
TYPED_TEST(MatrixEdgeCasesTest, EmptyMatrix_Initialization) {
  using MatrixType = Matrix<TypeParam>;
  
  // Конструктор по умолчанию
  MatrixType m1;
  EXPECT_EQ(m1.rows(), 0u);
  EXPECT_EQ(m1.cols(), 0u);
  EXPECT_EQ(m1.data(), nullptr);
  
  // Конструктор с нулевой размерностью
  MatrixType m2(0, 5);
  EXPECT_EQ(m2.rows(), 0u);
  EXPECT_EQ(m2.cols(), 0u);
  EXPECT_EQ(m2.data(), nullptr);
  
  MatrixType m3(5, 0);
  EXPECT_EQ(m3.rows(), 0u);
  EXPECT_EQ(m3.cols(), 0u);
  EXPECT_EQ(m3.data(), nullptr);
}

TYPED_TEST(MatrixEdgeCasesTest, EmptyMatrix_Operations) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType empty1;
  MatrixType empty2;
  
  // Сложение пустых матриц
  MatrixType sum = empty1 + empty2;
  EXPECT_EQ(sum.rows(), 0u);
  EXPECT_EQ(sum.cols(), 0u);
  
  // Вычитание пустых матриц
  MatrixType diff = empty1 - empty2;
  EXPECT_EQ(diff.rows(), 0u);
  EXPECT_EQ(diff.cols(), 0u);
  
  // Сравнение пустых матриц
  EXPECT_TRUE(empty1 == empty2);
}

TYPED_TEST(MatrixEdgeCasesTest, EmptyMatrix_ArithmeticWithZero) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType empty;
  MatrixType zero(2, 2);
  
  // Операции с пустой матрицей должны работать
  MatrixType result = empty + empty;
  EXPECT_EQ(result.rows(), 0u);
}

TYPED_TEST(MatrixEdgeCasesTest, EmptyMatrix_Transpose) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType empty;
  MatrixType transposed = empty.transpose();
  
  EXPECT_EQ(transposed.rows(), 0u);
  EXPECT_EQ(transposed.cols(), 0u);
}

// ============================================================================
// Вырожденные матрицы (det ≈ 0)
// ============================================================================
TYPED_TEST(MatrixEdgeCasesTest, SingularMatrix_DeterminantNearZero) {
  using MatrixType = Matrix<TypeParam>;
  
  // Матрица с линейно зависимыми строками
  MatrixType m(3, 3);
  m(0, 0) = TypeParam(1);
  m(0, 1) = TypeParam(2);
  m(0, 2) = TypeParam(3);
  m(1, 0) = TypeParam(4);
  m(1, 1) = TypeParam(5);
  m(1, 2) = TypeParam(6);
  m(2, 0) = TypeParam(7);
  m(2, 1) = TypeParam(8);
  m(2, 2) = TypeParam(9);
  
  TypeParam det = m.determinant();
  EXPECT_NEAR(det, TypeParam(0), MatrixType::kEpsilon);
}

TYPED_TEST(MatrixEdgeCasesTest, SingularMatrix_Inverse_Throws) {
  using MatrixType = Matrix<TypeParam>;
  
  // Матрица с линейно зависимыми строками
  MatrixType m(3, 3);
  m(0, 0) = TypeParam(1);
  m(0, 1) = TypeParam(2);
  m(0, 2) = TypeParam(3);
  m(1, 0) = TypeParam(4);
  m(1, 1) = TypeParam(5);
  m(1, 2) = TypeParam(6);
  m(2, 0) = TypeParam(7);
  m(2, 1) = TypeParam(8);
  m(2, 2) = TypeParam(9);
  
  EXPECT_THROW(m.inverse(), std::logic_error);
}

TYPED_TEST(MatrixEdgeCasesTest, NearlySingularMatrix_Inverse_Throws) {
  using MatrixType = Matrix<TypeParam>;
  
  // Матрица с очень маленьким определителем
  MatrixType m(2, 2);
  m(0, 0) = TypeParam(1);
  m(0, 1) = TypeParam(1);
  m(1, 0) = TypeParam(1);
  m(1, 1) = TypeParam(TypeParam(1) + MatrixType::kEpsilon / TypeParam(10));
  
  TypeParam det = m.determinant();
  EXPECT_NEAR(det, TypeParam(0), MatrixType::kEpsilon);
  
  EXPECT_THROW(m.inverse(), std::logic_error);
}

// ============================================================================
// Невалидные значения FPU (NaN, Inf)
// ============================================================================
TYPED_TEST(MatrixEdgeCasesTest, MatrixWithNaN) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType m(2, 2);
  m(0, 0) = TypeParam(1);
  m(0, 1) = std::numeric_limits<TypeParam>::quiet_NaN();
  m(1, 0) = TypeParam(3);
  m(1, 1) = TypeParam(4);
  
  // Оператор сравнения с NaN должен возвращать false
  MatrixType m2(2, 2);
  m2(0, 0) = TypeParam(1);
  m2(0, 1) = TypeParam(2);
  m2(1, 0) = TypeParam(3);
  m2(1, 1) = TypeParam(4);
  
  EXPECT_FALSE(m == m2);
  EXPECT_FALSE(m2 == m);
}

TYPED_TEST(MatrixEdgeCasesTest, MatrixWithInf) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType m(2, 2);
  m(0, 0) = TypeParam(1);
  m(0, 1) = std::numeric_limits<TypeParam>::infinity();
  m(1, 0) = TypeParam(3);
  m(1, 1) = TypeParam(4);
  
  // Оператор сравнения с Inf должен работать нормально
  MatrixType m2(2, 2);
  m2(0, 0) = TypeParam(1);
  m2(0, 1) = std::numeric_limits<TypeParam>::infinity();
  m2(1, 0) = TypeParam(3);
  m2(1, 1) = TypeParam(4);
  
  EXPECT_TRUE(m == m2);
}

TYPED_TEST(MatrixEdgeCasesTest, Inverse_WithNaN_Throws) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType m(2, 2);
  m(0, 0) = TypeParam(1);
  m(0, 1) = TypeParam(2);
  m(1, 0) = TypeParam(3);
  m(1, 1) = std::numeric_limits<TypeParam>::quiet_NaN();
  
  EXPECT_THROW(m.inverse(), std::logic_error);
}

TYPED_TEST(MatrixEdgeCasesTest, Inverse_WithInf_Throws) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType m(2, 2);
  m(0, 0) = TypeParam(1);
  m(0, 1) = TypeParam(2);
  m(1, 0) = TypeParam(3);
  m(1, 1) = std::numeric_limits<TypeParam>::infinity();
  
  EXPECT_THROW(m.inverse(), std::logic_error);
}

// ============================================================================
// Переполнение size_type
// ============================================================================
TYPED_TEST(MatrixEdgeCasesTest, SizeOverflow_Throws) {
  using MatrixType = Matrix<TypeParam>;
  
  // Попытка создать матрицу с экстремальными размерами
  // rows * cols > std::numeric_limits<size_type>::max()
  const size_type large_size = 
      std::numeric_limits<size_type>::max() / 2 + 1;
  
  EXPECT_THROW(MatrixType(large_size, large_size), std::length_error);
}

TYPED_TEST(MatrixEdgeCasesTest, SizeOverflowWithInitializerList_Throws) {
  using MatrixType = Matrix<TypeParam>;
  
  // Попытка создать матрицу с экстремальными размерами и initializer_list
  const size_type large_size = 
      std::numeric_limits<size_type>::max() / 2 + 1;
  
  std::initializer_list<TypeParam> large_list{};
  EXPECT_THROW(MatrixType(large_size, large_size, large_list), 
               std::length_error);
}

// ============================================================================
// Динамический эпсилон в inverse()
// ============================================================================
TYPED_TEST(MatrixEdgeCasesTest, DynamicEpsilon_Inverse) {
  using MatrixType = Matrix<TypeParam>;
  
  // Матрица с определителем, близким к машинному эпсилону
  // но больше динамического эпсилона (должна быть инвертирована)
  TypeParam epsilon = MatrixType::kEpsilon;
  
  MatrixType m(2, 2);
  m(0, 0) = TypeParam(1);
  m(0, 1) = TypeParam(0);
  m(1, 0) = TypeParam(0);
  m(1, 1) = TypeParam(epsilon * TypeParam(10));  // Больше динамического эпсилона
  
  TypeParam det = m.determinant();
  TypeParam dynamic_epsilon = std::numeric_limits<TypeParam>::epsilon() * 
                              static_cast<TypeParam>(m.rows());
  
  EXPECT_GT(std::abs(det), dynamic_epsilon);
  
  // Должна инвертироваться
  MatrixType inverse = m.inverse();
  EXPECT_EQ(inverse.rows(), 2u);
  EXPECT_EQ(inverse.cols(), 2u);
}

TYPED_TEST(MatrixEdgeCasesTest, DynamicEpsilonThreshold) {
  using MatrixType = Matrix<TypeParam>;
  
  // Матрица с определителем, меньше динамического эпсилона
  TypeParam dynamic_epsilon = std::numeric_limits<TypeParam>::epsilon() * 
                              static_cast<TypeParam>(3);
  
  MatrixType m(3, 3);
  m(0, 0) = TypeParam(1);
  m(0, 1) = TypeParam(0);
  m(0, 2) = TypeParam(0);
  m(1, 0) = TypeParam(0);
  m(1, 1) = TypeParam(1);
  m(1, 2) = TypeParam(0);
  m(2, 0) = TypeParam(0);
  m(2, 1) = TypeParam(0);
  m(2, 2) = TypeParam(dynamic_epsilon / TypeParam(10));
  
  TypeParam det = m.determinant();
  EXPECT_LT(std::abs(det), dynamic_epsilon);
  
  // Должна выбросить исключение
  EXPECT_THROW(m.inverse(), std::logic_error);
}

// ============================================================================
// Граничные случаи для различных операций
// ============================================================================
TYPED_TEST(MatrixEdgeCasesTest, EdgeCases_SingleElementMatrix) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType m(1, 1);
  m(0, 0) = TypeParam(42);
  
  // Детерминант
  EXPECT_EQ(m.determinant(), TypeParam(42));
  
  // Обратная матрица
  MatrixType inv = m.inverse();
  EXPECT_EQ(inv(0, 0), TypeParam(TypeParam(1) / TypeParam(42)));
  
  // Транспонирование
  MatrixType t = m.transpose();
  EXPECT_EQ(t.rows(), 1u);
  EXPECT_EQ(t.cols(), 1u);
  EXPECT_EQ(t(0, 0), TypeParam(42));
}

TYPED_TEST(MatrixEdgeCasesTest, EdgeCases_RectangularMatrixOperations) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType a(2, 3);
  a(0, 0) = TypeParam(1);
  a(0, 1) = TypeParam(2);
  a(0, 2) = TypeParam(3);
  a(1, 0) = TypeParam(4);
  a(1, 1) = TypeParam(5);
  a(1, 2) = TypeParam(6);
  
  MatrixType b(3, 2);
  b(0, 0) = TypeParam(7);
  b(0, 1) = TypeParam(8);
  b(1, 0) = TypeParam(9);
  b(1, 1) = TypeParam(10);
  b(2, 0) = TypeParam(11);
  b(2, 1) = TypeParam(12);
  
  // Умножение
  MatrixType result = a * b;
  EXPECT_EQ(result.rows(), 2u);
  EXPECT_EQ(result.cols(), 2u);
  
  // Обратное умножение (не должно работать)
  EXPECT_THROW(b * a, std::invalid_argument);
}

TYPED_TEST(MatrixEdgeCasesTest, EdgeCases_NegativeValues) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType m(2, 2);
  m(0, 0) = TypeParam(-1);
  m(0, 1) = TypeParam(-2);
  m(1, 0) = TypeParam(-3);
  m(1, 1) = TypeParam(-4);
  
  MatrixType result = m * TypeParam(-1);
  EXPECT_EQ(result(0, 0), TypeParam(1));
  EXPECT_EQ(result(1, 1), TypeParam(4));
}

// ============================================================================
// Тесты для численной устойчивости
// ============================================================================
TYPED_TEST(MatrixEdgeCasesTest, NumericalStability_SmallValues) {
  using MatrixType = Matrix<TypeParam>;
  
  TypeParam small = TypeParam(1e-10);
  
  MatrixType m(2, 2);
  m(0, 0) = small;
  m(0, 1) = TypeParam(0);
  m(1, 0) = TypeParam(0);
  m(1, 1) = small;
  
  TypeParam det = m.determinant();
  EXPECT_NEAR(det, small * small, MatrixType::kEpsilon);
  
  MatrixType inv = m.inverse();
  EXPECT_NEAR(inv(0, 0), TypeParam(1) / small, TypeParam(1e-6));
}

TYPED_TEST(MatrixEdgeCasesTest, NumericalStability_LargeValues) {
  using MatrixType = Matrix<TypeParam>;
  
  TypeParam large = TypeParam(1e10);
  
  MatrixType m(2, 2);
  m(0, 0) = large;
  m(0, 1) = TypeParam(0);
  m(1, 0) = TypeParam(0);
  m(1, 1) = large;
  
  TypeParam det = m.determinant();
  EXPECT_NEAR(det, large * large, std::abs(large * large) * MatrixType::kEpsilon);
}
