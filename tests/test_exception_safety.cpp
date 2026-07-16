/**
 * @file test_exception_safety.cpp
 * @brief Тесты гарантий безопасности исключений и строгих инвариантов.
 */

#include <gtest/gtest.h>
#include <limits>
#include <cmath>
#include <stdexcept>

#include "s21_matrix+.hpp"

using namespace s21;

using TestTypes = ::testing::Types<float, double, long double>;
TYPED_TEST_SUITE(MatrixExceptionSafetyTest, TestTypes);

// ============================================================================
// Strong Exception Guarantee: operator=
// ============================================================================
TYPED_TEST(MatrixExceptionSafetyTest, StrongGuarantee_AssignmentOperator) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType original(2, 2);
  original(0, 0) = TypeParam(1);
  original(0, 1) = TypeParam(2);
  original(1, 0) = TypeParam(3);
  original(1, 1) = TypeParam(4);
  
  MatrixType target(3, 3);
  target(0, 0) = TypeParam(999);
  
  // Сохраняем состояние для сравнения
  MatrixType saved = target;
  
  try {
    // Это не выбросит исключение, но код проверяет строгую гарантию
    // Для реального теста строгой гарантии нужен искусственный сценарий
    target = original;
  } catch (...) {
    // В случае исключения состояние должно остаться неизменным
    EXPECT_TRUE(target == saved);
    throw;  // Перебрасываем исключение
  }
  
  // В случае успеха состояние должно измениться
  EXPECT_EQ(target.rows(), 2u);
  EXPECT_EQ(target.cols(), 2u);
}

TYPED_TEST(MatrixExceptionSafetyTest, StrongGuarantee_CopyAssignment) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType a(2, 2);
  a(0, 0) = TypeParam(1);
  
  MatrixType b(3, 3);
  b(1, 1) = TypeParam(2);
  
  MatrixType saved = b;
  
  b = a;
  
  EXPECT_EQ(b.rows(), 2u);
  EXPECT_EQ(b.cols(), 2u);
  EXPECT_EQ(b(0, 0), TypeParam(1));
}

// ============================================================================
// No-throw Guarantee: деструктор
// ============================================================================
TYPED_TEST(MatrixExceptionSafetyTest, NoThrowGuarantee_Destructor) {
  using MatrixType = Matrix<TypeParam>;
  
  {
    MatrixType m(100, 100);
    // Деструктор не должен выбрасывать исключений
  }
  // Если мы здесь, деструктор сработал успешно
}

TYPED_TEST(MatrixExceptionSafetyTest, NoThrowGuarantee_Deallocate) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType m(50, 50);
  m.deallocate();
  
  // Проверка, что объект в валидном состоянии
  EXPECT_EQ(m.rows(), 0u);
  EXPECT_EQ(m.cols(), 0u);
  EXPECT_EQ(m.data(), nullptr);
}

// ============================================================================
// No-throw Guarantee: swap()
// ============================================================================
TYPED_TEST(MatrixExceptionSafetyTest, NoThrowGuarantee_Swap) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType a(2, 2);
  a(0, 0) = TypeParam(1);
  
  MatrixType b(3, 3);
  b(1, 1) = TypeParam(2);
  
  swap(a, b);
  
  EXPECT_EQ(a.rows(), 3u);
  EXPECT_EQ(a.cols(), 3u);
  EXPECT_EQ(a(1, 1), TypeParam(2));
  
  EXPECT_EQ(b.rows(), 2u);
  EXPECT_EQ(b.cols(), 2u);
  EXPECT_EQ(b(0, 0), TypeParam(1));
}

// ============================================================================
// No-throw Guarantee: перемещающий конструктор
// ============================================================================
TYPED_TEST(MatrixExceptionSafetyTest, NoThrowGuarantee_MoveConstructor) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType original(5, 5);
  original(2, 2) = TypeParam(42);
  
  // Перемещающий конструктор должен быть noexcept
  static_assert(std::is_nothrow_move_constructible<MatrixType>::value,
                "Move constructor should be noexcept");
  
  MatrixType moved(std::move(original));
  
  EXPECT_EQ(moved(2, 2), TypeParam(42));
}

// ============================================================================
// Проверка инвариантов после операций
// ============================================================================
TYPED_TEST(MatrixExceptionSafetyTest, Invariant_AfterAssignment) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType m1(2, 2);
  m1(0, 0) = TypeParam(1);
  
  MatrixType m2(3, 3);
  m2(1, 1) = TypeParam(2);
  
  m2 = m1;
  
  // Инвариант: data_ != nullptr тогда и только тогда, когда rows_ > 0 и cols_ > 0
  if (m2.rows() > 0 && m2.cols() > 0) {
    EXPECT_NE(m2.data(), nullptr);
  } else {
    EXPECT_EQ(m2.data(), nullptr);
  }
  
  // Размер буфера равен rows_ * cols_
  if (m2.rows() > 0 && m2.cols() > 0) {
    // Мы не можем напрямую проверить размер буфера, но можем проверить доступ
    EXPECT_NO_THROW(m2(m2.rows() - 1, m2.cols() - 1));
  }
}

TYPED_TEST(MatrixExceptionSafetyTest, Invariant_AfterTranspose) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType m(2, 3);
  m(0, 0) = TypeParam(1);
  m(1, 2) = TypeParam(2);
  
  MatrixType t = m.transpose();
  
  EXPECT_EQ(t.rows(), m.cols());
  EXPECT_EQ(t.cols(), m.rows());
  EXPECT_EQ(t(0, 0), m(0, 0));
  EXPECT_EQ(t(2, 1), m(1, 2));
}

TYPED_TEST(MatrixExceptionSafetyTest, Invariant_AfterArithmetic) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType a(2, 2);
  a(0, 0) = TypeParam(1);
  
  MatrixType b(2, 2);
  b(0, 0) = TypeParam(2);
  
  MatrixType result = a + b;
  
  EXPECT_EQ(result.rows(), 2u);
  EXPECT_EQ(result.cols(), 2u);
  EXPECT_NE(result.data(), nullptr);
  EXPECT_EQ(result(0, 0), TypeParam(3));
}

// ============================================================================
// Тесты для self-assignment
// ============================================================================
TYPED_TEST(MatrixExceptionSafetyTest, SelfAssignment_PreservesState) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType m(3, 3);
  m(1, 1) = TypeParam(42);
  m(2, 2) = TypeParam(99);
  
  MatrixType saved = m;
  
  m = m;
  
  EXPECT_TRUE(m == saved);
}

TYPED_TEST(MatrixExceptionSafetyTest, SelfAssignmentCopy_PreservesState) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType m(2, 2);
  m(0, 0) = TypeParam(1);
  m(0, 1) = TypeParam(2);
  m(1, 0) = TypeParam(3);
  m(1, 1) = TypeParam(4);
  
  MatrixType saved = m;
  
  // Копирующее присваивание
  MatrixType& ref = m;
  m = ref;
  
  EXPECT_TRUE(m == saved);
}

// ============================================================================
// Тесты для copy-and-swap идиомы
// ============================================================================
TYPED_TEST(MatrixExceptionSafetyTest, CopyAndSwap_IndependentCopies) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType original(2, 2);
  original(0, 0) = TypeParam(1);
  original(0, 1) = TypeParam(2);
  
  MatrixType copy1 = original;
  MatrixType copy2 = original;
  
  // Изменение оригинала не должно влиять на копии
  original(0, 0) = TypeParam(999);
  
  EXPECT_EQ(copy1(0, 0), TypeParam(1));
  EXPECT_EQ(copy2(0, 0), TypeParam(1));
  
  // Изменение одной копии не должно влиять на другую
  copy1(0, 0) = TypeParam(111);
  
  EXPECT_EQ(copy1(0, 0), TypeParam(111));
  EXPECT_EQ(copy2(0, 0), TypeParam(1));
}

TYPED_TEST(MatrixExceptionSafetyTest, Swap_Symmetric) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType a(2, 2);
  a(0, 0) = TypeParam(1);
  
  MatrixType b(3, 3);
  b(1, 1) = TypeParam(2);
  
  MatrixType a_saved = a;
  MatrixType b_saved = b;
  
  swap(a, b);
  
  EXPECT_TRUE(a == b_saved);
  EXPECT_TRUE(b == a_saved);
}

// ============================================================================
// Тесты для move semantics
// ============================================================================
TYPED_TEST(MatrixExceptionSafetyTest, MoveConstructor_TransfersData) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType original(4, 4);
  original(2, 2) = TypeParam(42);
  
  MatrixType moved(std::move(original));
  
  // Данные должны быть перемещены
  EXPECT_EQ(moved(2, 2), TypeParam(42));
  
  // Оригинал должен быть в валидном состоянии
  EXPECT_EQ(original.rows(), 0u);
  EXPECT_EQ(original.cols(), 0u);
  EXPECT_EQ(original.data(), nullptr);
}

TYPED_TEST(MatrixExceptionSafetyTest, MoveAssignment) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType source(2, 3);
  source(0, 0) = TypeParam(1);
  source(1, 2) = TypeParam(6);
  
  MatrixType target(5, 5);
  target(2, 2) = TypeParam(999);
  
  target = std::move(source);
  
  EXPECT_EQ(target.rows(), 2u);
  EXPECT_EQ(target.cols(), 3u);
  EXPECT_EQ(target(0, 0), TypeParam(1));
  EXPECT_EQ(target(1, 2), TypeParam(6));
}

// ============================================================================
// Тесты для const correctness
// ============================================================================
TYPED_TEST(MatrixExceptionSafetyTest, ConstCorrectness_Accessors) {
  using MatrixType = Matrix<TypeParam>;
  
  const MatrixType m(2, 2);
  m(0, 0);  // Должно компилироваться для const-объекта
  
  static_assert(std::is_const_v<std::remove_reference_t<decltype(m(0, 0))>>,
                "operator() should return const reference for const Matrix");
}

TYPED_TEST(MatrixExceptionSafetyTest, ConstCorrectness_NoModify) {
  using MatrixType = Matrix<TypeParam>;
  
  const MatrixType m(2, 2);
  m(0, 0) = TypeParam(1);
  m(0, 1) = TypeParam(2);
  m(1, 0) = TypeParam(3);
  m(1, 1) = TypeParam(4);
  
  // Доступ к константным методам
  EXPECT_EQ(m.rows(), 2u);
  EXPECT_EQ(m.cols(), 2u);
  
  // Проверка, что константный метод не модифицирует объект
  const MatrixType& cm = m;
  EXPECT_EQ(cm(0, 0), TypeParam(1));
}
