/**
 * @file test_matrix_linalg.cpp
 * @brief Тесты линейной алгебры: умножение матриц, transpose, determinant,
 *        calc_complements, inverse.
 */

#include <gtest/gtest.h>
#include <limits>
#include <cmath>

#include "s21_matrix+.hpp"

using namespace s21;

template <typename T>
class MatrixLinearAlgebraTest : public ::testing::Test {};
using TestTypes = ::testing::Types<float, double, long double>;
TYPED_TEST_SUITE(MatrixLinearAlgebraTest, TestTypes);

// ============================================================================
// Матричное умножение operator*, operator*=
// ============================================================================
TYPED_TEST(MatrixLinearAlgebraTest, OperatorMatrixMultiply_Valid) {
  using MatrixType = Matrix<TypeParam>;
  
  // Матрица 2x3 * 3x2 = 2x2
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
  
  MatrixType result = a * b;
  
  EXPECT_EQ(result.rows(), 2u);
  EXPECT_EQ(result.cols(), 2u);
  // result(0,0) = 1*7 + 2*9 + 3*11 = 58
  // result(0,1) = 1*8 + 2*10 + 3*12 = 64
  // result(1,0) = 4*7 + 5*9 + 6*11 = 139
  // result(1,1) = 4*8 + 5*10 + 6*12 = 154
  EXPECT_EQ(result(0, 0), TypeParam(58));
  EXPECT_EQ(result(0, 1), TypeParam(64));
  EXPECT_EQ(result(1, 0), TypeParam(139));
  EXPECT_EQ(result(1, 1), TypeParam(154));
}

TYPED_TEST(MatrixLinearAlgebraTest, OperatorMatrixMultiply_IncompatibleDimensions_Throws) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType a(2, 3);
  MatrixType b(2, 3);
  
  EXPECT_THROW(a * b, std::invalid_argument);
}

TYPED_TEST(MatrixLinearAlgebraTest, OperatorMatrixMultiplyEquals) {
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
  
  a *= b;
  
  EXPECT_EQ(a.rows(), 2u);
  EXPECT_EQ(a.cols(), 2u);
  EXPECT_EQ(a(0, 0), TypeParam(58));
  EXPECT_EQ(a(1, 1), TypeParam(154));
}

TYPED_TEST(MatrixLinearAlgebraTest, OperatorMatrixMultiply_Identity) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType identity(3, 3);
  identity(0, 0) = TypeParam(1);
  identity(1, 1) = TypeParam(1);
  identity(2, 2) = TypeParam(1);
  
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
  
  MatrixType result1 = m * identity;
  MatrixType result2 = identity * m;
  
  EXPECT_TRUE(result1 == m);
  EXPECT_TRUE(result2 == m);
}

// ============================================================================
// transpose()
// ============================================================================
TYPED_TEST(MatrixLinearAlgebraTest, Transpose_SquareMatrix) {
  using MatrixType = Matrix<TypeParam>;
  
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
  
  MatrixType result = m.transpose();
  
  EXPECT_EQ(result.rows(), 3u);
  EXPECT_EQ(result.cols(), 3u);
  EXPECT_EQ(result(0, 0), TypeParam(1));
  EXPECT_EQ(result(0, 1), TypeParam(4));
  EXPECT_EQ(result(1, 0), TypeParam(2));
  EXPECT_EQ(result(2, 2), TypeParam(9));
}

TYPED_TEST(MatrixLinearAlgebraTest, Transpose_RectangularMatrix) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType m(2, 3);
  m(0, 0) = TypeParam(1);
  m(0, 1) = TypeParam(2);
  m(0, 2) = TypeParam(3);
  m(1, 0) = TypeParam(4);
  m(1, 1) = TypeParam(5);
  m(1, 2) = TypeParam(6);
  
  MatrixType result = m.transpose();
  
  EXPECT_EQ(result.rows(), 3u);
  EXPECT_EQ(result.cols(), 2u);
  EXPECT_EQ(result(0, 0), TypeParam(1));
  EXPECT_EQ(result(0, 1), TypeParam(4));
  EXPECT_EQ(result(2, 0), TypeParam(3));
}

TYPED_TEST(MatrixLinearAlgebraTest, Transpose_EmptyMatrix) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType m;
  MatrixType result = m.transpose();
  
  EXPECT_EQ(result.rows(), 0u);
  EXPECT_EQ(result.cols(), 0u);
}

TYPED_TEST(MatrixLinearAlgebraTest, Transpose_TwiceReturnsOriginal) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType m(2, 3);
  m(0, 0) = TypeParam(1);
  m(0, 1) = TypeParam(2);
  m(0, 2) = TypeParam(3);
  m(1, 0) = TypeParam(4);
  m(1, 1) = TypeParam(5);
  m(1, 2) = TypeParam(6);
  
  MatrixType result = m.transpose().transpose();
  
  EXPECT_TRUE(result == m);
}

// ============================================================================
// determinant() - метод Гаусса с частичным выбором главного элемента
// ============================================================================
TYPED_TEST(MatrixLinearAlgebraTest, Determinant_SingleElement) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType m(1, 1);
  m(0, 0) = TypeParam(42);
  
  EXPECT_EQ(m.determinant(), TypeParam(42));
}

TYPED_TEST(MatrixLinearAlgebraTest, Determinant_2x2) {
    using MatrixType = Matrix<TypeParam>;
    MatrixType m(2, 2);
    m(0, 0) = TypeParam(1);
    m(0, 1) = TypeParam(2);
    m(1, 0) = TypeParam(3);
    m(1, 1) = TypeParam(4);
    
    // det = 1*4 - 2*3 = -2
    // Используем EXPECT_NEAR для учета погрешности FPU
    EXPECT_NEAR(m.determinant(), TypeParam(-2), MatrixType::kEpsilon);
}

TYPED_TEST(MatrixLinearAlgebraTest, Determinant_3x3) {
  using MatrixType = Matrix<TypeParam>;
  
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
  
  // det = 0 (строки линейно зависимы)
  EXPECT_NEAR(m.determinant(), TypeParam(0), MatrixType::kEpsilon);
}

TYPED_TEST(MatrixLinearAlgebraTest, Determinant_NonZero) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType m(3, 3);
  m(0, 0) = TypeParam(6);
  m(0, 1) = TypeParam(1);
  m(0, 2) = TypeParam(7);
  m(1, 0) = TypeParam(2);
  m(1, 1) = TypeParam(9);
  m(1, 2) = TypeParam(3);
  m(2, 0) = TypeParam(1);
  m(2, 1) = TypeParam(4);
  m(2, 2) = TypeParam(2);
  
  // det = 6*9*2 + 1*3*1 + 7*2*4 - 7*9*1 - 6*3*4 - 1*2*2 = 108 + 3 + 56 - 63 - 72 - 4 = 28
  EXPECT_NEAR(m.determinant(), TypeParam(28), TypeParam(0.1));
}

TYPED_TEST(MatrixLinearAlgebraTest, Determinant_SingularMatrix) {
  using MatrixType = Matrix<TypeParam>;
  
  // Матрица с нулевым столбцом
  MatrixType m(3, 3);
  m(0, 0) = TypeParam(1);
  m(0, 1) = TypeParam(2);
  m(0, 2) = TypeParam(0);
  m(1, 0) = TypeParam(3);
  m(1, 1) = TypeParam(4);
  m(1, 2) = TypeParam(0);
  m(2, 0) = TypeParam(5);
  m(2, 1) = TypeParam(6);
  m(2, 2) = TypeParam(0);
  
  EXPECT_NEAR(m.determinant(), TypeParam(0), MatrixType::kEpsilon);
}

TYPED_TEST(MatrixLinearAlgebraTest, Determinant_NonSquare_Throws) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType m(2, 3);
  
  EXPECT_THROW((void)m.determinant(), std::invalid_argument);
}

TYPED_TEST(MatrixLinearAlgebraTest, Determinant_Empty_Throws) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType m;
  
  EXPECT_THROW((void)m.determinant(), std::invalid_argument);
}

// ============================================================================
// calc_complements() - матрица алгебраических дополнений
// ============================================================================
TYPED_TEST(MatrixLinearAlgebraTest, CalcComplements_1x1) {
    using MatrixType = Matrix<TypeParam>;
    MatrixType m(1, 1);
    m(0, 0) = TypeParam(42); // Значение не имеет значения для дополнения 1x1
    
    MatrixType result = m.calc_complements();
    
    EXPECT_EQ(result.rows(), 1u);
    EXPECT_EQ(result.cols(), 1u);
    EXPECT_EQ(result(0, 0), TypeParam(1)); // Алгебраическое дополнение 1x1 всегда равно 1
}

TYPED_TEST(MatrixLinearAlgebraTest, CalcComplements_2x2) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType m(2, 2);
  m(0, 0) = TypeParam(1);
  m(0, 1) = TypeParam(2);
  m(1, 0) = TypeParam(3);
  m(1, 1) = TypeParam(4);
  
  MatrixType result = m.calc_complements();
  
  // Cofactor matrix:
  // C(0,0) = (+1) * 4 = 4
  // C(0,1) = (-1) * 3 = -3
  // C(1,0) = (-1) * 2 = -2
  // C(1,1) = (+1) * 1 = 1
  EXPECT_EQ(result(0, 0), TypeParam(4));
  EXPECT_EQ(result(0, 1), TypeParam(-3));
  EXPECT_EQ(result(1, 0), TypeParam(-2));
  EXPECT_EQ(result(1, 1), TypeParam(1));
}

TYPED_TEST(MatrixLinearAlgebraTest, CalcComplements_3x3) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType m(3, 3);
  m(0, 0) = TypeParam(1);
  m(0, 1) = TypeParam(2);
  m(0, 2) = TypeParam(3);
  m(1, 0) = TypeParam(0);
  m(1, 1) = TypeParam(1);
  m(1, 2) = TypeParam(0);
  m(2, 0) = TypeParam(0);
  m(2, 1) = TypeParam(0);
  m(2, 2) = TypeParam(1);
  
  MatrixType result = m.calc_complements();
  
  // Cofactor matrix (upper triangular with 1s on diagonal):
  // C(0,0) = +1, C(0,1) = 0, C(0,2) = 0
  // C(1,0) = 0, C(1,1) = +1, C(1,2) = 0
  // C(2,0) = 0, C(2,1) = 0, C(2,2) = +1
  EXPECT_EQ(result(0, 0), TypeParam(1));
  EXPECT_EQ(result(1, 1), TypeParam(1));
  EXPECT_EQ(result(2, 2), TypeParam(1));
}

TYPED_TEST(MatrixLinearAlgebraTest, CalcComplements_NonSquare_Throws) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType m(2, 3);
  
  EXPECT_THROW((void)m.calc_complements(), std::invalid_argument);
}

TYPED_TEST(MatrixLinearAlgebraTest, CalcComplements_Empty_Throws) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType m;
  
  EXPECT_THROW((void)m.calc_complements(), std::invalid_argument);
}

TYPED_TEST(MatrixLinearAlgebraTest, CalcComplements_SingularMatrix) {
    using MatrixType = Matrix<TypeParam>;
    MatrixType m(3, 3);
    m(0, 0) = TypeParam(1);
    m(0, 1) = TypeParam(2);
    m(0, 2) = TypeParam(3);
    m(1, 0) = TypeParam(2);
    m(1, 1) = TypeParam(4);
    m(1, 2) = TypeParam(6);
    m(2, 0) = TypeParam(3);
    m(2, 1) = TypeParam(6);
    m(2, 2) = TypeParam(9);
    
    // Матрица алгебраических дополнений должна вычислиться
    MatrixType complements = m.calc_complements();
    EXPECT_EQ(complements.rows(), 3u);
    EXPECT_EQ(complements.cols(), 3u);
}

// ============================================================================
// inverse() - обратная матрица
// ============================================================================
TYPED_TEST(MatrixLinearAlgebraTest, Inverse_2x2) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType m(2, 2);
  m(0, 0) = TypeParam(4);
  m(0, 1) = TypeParam(7);
  m(1, 0) = TypeParam(2);
  m(1, 1) = TypeParam(6);
  
  MatrixType inverse = m.inverse();
  
  // Проверка: A * A^(-1) = I
  MatrixType result = m * inverse;
  EXPECT_NEAR(result(0, 0), TypeParam(1), TypeParam(0.001));
  EXPECT_NEAR(result(0, 1), TypeParam(0), TypeParam(0.001));
  EXPECT_NEAR(result(1, 0), TypeParam(0), TypeParam(0.001));
  EXPECT_NEAR(result(1, 1), TypeParam(1), TypeParam(0.001));
}

TYPED_TEST(MatrixLinearAlgebraTest, Inverse_3x3) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType m(3, 3);
  m(0, 0) = TypeParam(1);
  m(0, 1) = TypeParam(0);
  m(0, 2) = TypeParam(2);
  m(1, 0) = TypeParam(2);
  m(1, 1) = TypeParam(1);
  m(1, 2) = TypeParam(6);
  m(2, 0) = TypeParam(3);
  m(2, 1) = TypeParam(1);
  m(2, 2) = TypeParam(14);
  
  MatrixType inverse = m.inverse();
  
  // Проверка: A * A^(-1) = I
  MatrixType result = m * inverse;
  EXPECT_NEAR(result(0, 0), TypeParam(1), TypeParam(0.001));
  EXPECT_NEAR(result(1, 1), TypeParam(1), TypeParam(0.001));
  EXPECT_NEAR(result(2, 2), TypeParam(1), TypeParam(0.001));
  EXPECT_NEAR(result(0, 1), TypeParam(0), TypeParam(0.001));
  EXPECT_NEAR(result(1, 2), TypeParam(0), TypeParam(0.001));
}

TYPED_TEST(MatrixLinearAlgebraTest, Inverse_SingularMatrix_Throws) {
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
  
  EXPECT_THROW((void)m.inverse(), std::logic_error);
}

TYPED_TEST(MatrixLinearAlgebraTest, Inverse_NonSquare_Throws) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType m(2, 3);
  
  EXPECT_THROW((void)m.inverse(), std::invalid_argument);
}

TYPED_TEST(MatrixLinearAlgebraTest, Inverse_Empty_Throws) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType m;
  
  EXPECT_THROW((void)m.inverse(), std::invalid_argument);
}

// ============================================================================
// Связь между операциями
// ============================================================================
TYPED_TEST(MatrixLinearAlgebraTest, Relation_InverseViaAdjugate) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType m(3, 3);
  m(0, 0) = TypeParam(1);
  m(0, 1) = TypeParam(2);
  m(0, 2) = TypeParam(3);
  m(1, 0) = TypeParam(0);
  m(1, 1) = TypeParam(1);
  m(1, 2) = TypeParam(5);
  m(2, 0) = TypeParam(0);
  m(2, 1) = TypeParam(0);
  m(2, 2) = TypeParam(1);
  
  TypeParam det = m.determinant();
  MatrixType adj = m.calc_complements().transpose();
  
  MatrixType inverse = m.inverse();
  
  // A^(-1) = adj(A) / det(A)
  MatrixType expected = adj * (TypeParam(1) / det);
  
  EXPECT_TRUE(inverse == expected);
}

TYPED_TEST(MatrixLinearAlgebraTest, Relation_TransposeOfProduct) {
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
  
  MatrixType result1 = (a * b).transpose();
  MatrixType result2 = b.transpose() * a.transpose();
  
  EXPECT_TRUE(result1 == result2);
}

// ============================================================================
// Тесты для граничных случаев
// ============================================================================
TYPED_TEST(MatrixLinearAlgebraTest, EdgeCases_IdentityMatrixInverse) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType identity(3, 3);
  identity(0, 0) = TypeParam(1);
  identity(1, 1) = TypeParam(1);
  identity(2, 2) = TypeParam(1);
  
  MatrixType inverse = identity.inverse();
  
  EXPECT_TRUE(inverse == identity);
}

TYPED_TEST(MatrixLinearAlgebraTest, EdgeCases_IdentityMatrixDeterminant) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType identity(5, 5);
  for (std::size_t i = 0; i < 5; ++i) {
    identity(i, i) = TypeParam(1);
  }
  
  EXPECT_NEAR(identity.determinant(), TypeParam(1), MatrixType::kEpsilon);
}
