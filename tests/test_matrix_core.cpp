/**
 * @file test_matrix_core.cpp
 * @brief Тесты базового функционала: конструкторы, деструктор, аксессоры.
 */

#include <gtest/gtest.h>
#include <limits>
#include <cmath>

#include "s21_matrix+.hpp"

using namespace s21;

// Типы для параметризованных тестов
using TestTypes = ::testing::Types<float, double, long double>;
TYPED_TEST_SUITE(MatrixCoreTest, TestTypes);

// ============================================================================
// Конструктор по умолчанию
// ============================================================================
TYPED_TEST(MatrixCoreTest, DefaultConstructor_CreatesEmptyMatrix) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType m;
  
  EXPECT_EQ(m.rows(), 0u);
  EXPECT_EQ(m.cols(), 0u);
  EXPECT_EQ(m.data(), nullptr);
}

// ============================================================================
// Конструктор с размерностями
// ============================================================================
TYPED_TEST(MatrixCoreTest, ConstructorWithDimensions_CreatesZeroedMatrix) {
  using MatrixType = Matrix<TypeParam>;
  
  const size_type rows = 3;
  const size_type cols = 4;
  
  MatrixType m(rows, cols);
  
  EXPECT_EQ(m.rows(), rows);
  EXPECT_EQ(m.cols(), cols);
  ASSERT_NE(m.data(), nullptr);
  
  // Проверка инициализации нулями
  for (size_type i = 0; i < rows; ++i) {
    for (size_type j = 0; j < cols; ++j) {
      EXPECT_EQ(m(i, j), TypeParam(0));
    }
  }
}

TYPED_TEST(MatrixCoreTest, ConstructorWithDimensions_EmptyMatrix) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType m(0, 5);
  
  EXPECT_EQ(m.rows(), 0u);
  EXPECT_EQ(m.cols(), 0u);
  EXPECT_EQ(m.data(), nullptr);
}

TYPED_TEST(MatrixCoreTest, ConstructorWithDimensions_SquareMatrix) {
  using MatrixType = Matrix<TypeParam>;
  
  const size_type dim = 5;
  MatrixType m(dim, dim);
  
  EXPECT_EQ(m.rows(), dim);
  EXPECT_EQ(m.cols(), dim);
}

// ============================================================================
// Конструктор с initializer_list (автовывод размерности)
// ============================================================================
TYPED_TEST(MatrixCoreTest, ConstructorInitializerList_SquareMatrix) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType m{1, 2, 3, 4, 5, 6, 7, 8, 9};
  
  EXPECT_EQ(m.rows(), 3u);
  EXPECT_EQ(m.cols(), 3u);
  
  EXPECT_EQ(m(0, 0), TypeParam(1));
  EXPECT_EQ(m(0, 1), TypeParam(2));
  EXPECT_EQ(m(0, 2), TypeParam(3));
  EXPECT_EQ(m(2, 2), TypeParam(9));
}

TYPED_TEST(MatrixCoreTest, ConstructorInitializerList_SingleElement) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType m{42};
  
  EXPECT_EQ(m.rows(), 1u);
  EXPECT_EQ(m.cols(), 1u);
  EXPECT_EQ(m(0, 0), TypeParam(42));
}

TYPED_TEST(MatrixCoreTest, ConstructorInitializerList_InvalidSize_Throws) {
  using MatrixType = Matrix<TypeParam>;
  
  EXPECT_THROW(MatrixType{1, 2, 3}, std::invalid_argument);
  EXPECT_THROW(MatrixType{1, 2, 3, 4, 5}, std::invalid_argument);
  EXPECT_THROW(MatrixType{}, std::invalid_argument);
}

// ============================================================================
// Конструктор с размерностью и initializer_list
// ============================================================================
TYPED_TEST(MatrixCoreTest, ConstructorDimensionsInitializerList_Valid) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType m(2, 3, {1, 2, 3, 4, 5, 6});
  
  EXPECT_EQ(m.rows(), 2u);
  EXPECT_EQ(m.cols(), 3u);
  
  EXPECT_EQ(m(0, 0), TypeParam(1));
  EXPECT_EQ(m(0, 1), TypeParam(2));
  EXPECT_EQ(m(0, 2), TypeParam(3));
  EXPECT_EQ(m(1, 0), TypeParam(4));
  EXPECT_EQ(m(1, 1), TypeParam(5));
  EXPECT_EQ(m(1, 2), TypeParam(6));
}

TYPED_TEST(MatrixCoreTest, ConstructorDimensionsInitializerList_InvalidSize_Throws) {
  using MatrixType = Matrix<TypeParam>;
  
  EXPECT_THROW(MatrixType(2, 3, {1, 2, 3, 4, 5}), std::invalid_argument);
  EXPECT_THROW(MatrixType(2, 3, {1, 2, 3, 4, 5, 6, 7}), std::invalid_argument);
}

TYPED_TEST(MatrixCoreTest, ConstructorDimensionsInitializerList_EmptyMatrix) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType m(0, 0, {});
  
  EXPECT_EQ(m.rows(), 0u);
  EXPECT_EQ(m.cols(), 0u);
  EXPECT_EQ(m.data(), nullptr);
}

// ============================================================================
// Конструктор копирования (deep copy)
// ============================================================================
TYPED_TEST(MatrixCoreTest, CopyConstructor_CreatesDeepCopy) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType original(2, 2);
  original(0, 0) = TypeParam(1);
  original(0, 1) = TypeParam(2);
  original(1, 0) = TypeParam(3);
  original(1, 1) = TypeParam(4);
  
  MatrixType copy(original);
  
  // Проверка значений
  EXPECT_EQ(copy.rows(), 2u);
  EXPECT_EQ(copy.cols(), 2u);
  EXPECT_EQ(copy(0, 0), TypeParam(1));
  EXPECT_EQ(copy(1, 1), TypeParam(4));
  
  // Проверка, что это независимые объекты (deep copy)
  original(0, 0) = TypeParam(999);
  EXPECT_EQ(copy(0, 0), TypeParam(1));
}

// ============================================================================
// Перемещающий конструктор
// ============================================================================
TYPED_TEST(MatrixCoreTest, MoveConstructor_TransfersOwnership) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType original(3, 3);
  original(1, 1) = TypeParam(42);
  
  MatrixType moved(std::move(original));
  
  EXPECT_EQ(moved.rows(), 3u);
  EXPECT_EQ(moved.cols(), 3u);
  EXPECT_EQ(moved(1, 1), TypeParam(42));
  
  // Исходный объект должен быть в валидном состоянии (пустой)
  EXPECT_EQ(original.rows(), 0u);
  EXPECT_EQ(original.cols(), 0u);
  EXPECT_EQ(original.data(), nullptr);
}

// ============================================================================
// Оператор присваивания (copy-and-swap)
// ============================================================================
TYPED_TEST(MatrixCoreTest, AssignmentOperator_CopyAssignment) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType a(2, 2);
  a(0, 0) = TypeParam(1);
  
  MatrixType b(3, 3);
  b(1, 1) = TypeParam(2);
  
  b = a;
  
  EXPECT_EQ(b.rows(), 2u);
  EXPECT_EQ(b.cols(), 2u);
  EXPECT_EQ(b(0, 0), TypeParam(1));
}

TYPED_TEST(MatrixCoreTest, AssignmentOperator_SelfAssignment) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType m(2, 2);
  m(0, 0) = TypeParam(42);
  
  m = m;
  
  EXPECT_EQ(m.rows(), 2u);
  EXPECT_EQ(m.cols(), 2u);
  EXPECT_EQ(m(0, 0), TypeParam(42));
}

// ============================================================================
// Деструктор
// ============================================================================
TYPED_TEST(MatrixCoreTest, Destructor_DoesNotLeakMemory) {
  using MatrixType = Matrix<TypeParam>;
  
  {
    MatrixType m(100, 100);
    // Матрица создается и будет уничтожена при выходе из области видимости
  }
  // Если здесь нет утечек, тест прошел
}

// ============================================================================
// Аксессоры: rows(), cols()
// ============================================================================
TYPED_TEST(MatrixCoreTest, RowsCols_Accessors) {
  using MatrixType = Matrix<TypeParam>;
  
  EXPECT_EQ(MatrixType().rows(), 0u);
  EXPECT_EQ(MatrixType().cols(), 0u);
  
  MatrixType m1(5, 3);
  EXPECT_EQ(m1.rows(), 5u);
  EXPECT_EQ(m1.cols(), 3u);
  
  MatrixType m2(1, 10);
  EXPECT_EQ(m2.rows(), 1u);
  EXPECT_EQ(m2.cols(), 10u);
}

// ============================================================================
// operator() для чтения и записи
// ============================================================================
TYPED_TEST(MatrixCoreTest, ParenthesesOperator_ReadWrite) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType m(2, 2);
  
  // Запись
  m(0, 0) = TypeParam(1);
  m(0, 1) = TypeParam(2);
  m(1, 0) = TypeParam(3);
  m(1, 1) = TypeParam(4);
  
  // Чтение
  EXPECT_EQ(m(0, 0), TypeParam(1));
  EXPECT_EQ(m(0, 1), TypeParam(2));
  EXPECT_EQ(m(1, 0), TypeParam(3));
  EXPECT_EQ(m(1, 1), TypeParam(4));
}

TYPED_TEST(MatrixCoreTest, ParenthesesOperator_OutOfRange_Throws) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType m(2, 2);
  
  EXPECT_THROW(m(2, 0), std::out_of_range);
  EXPECT_THROW(m(0, 2), std::out_of_range);
  EXPECT_THROW(m(10, 10), std::out_of_range);
}

// ============================================================================
// Инварианты класса
// ============================================================================
TYPED_TEST(MatrixCoreTest, ClassInvariants_DataNullptrWhenEmpty) {
  using MatrixType = Matrix<TypeParam>;
  
  // Пустая матрица
  MatrixType m1;
  EXPECT_EQ(m1.rows(), 0u);
  EXPECT_EQ(m1.cols(), 0u);
  EXPECT_EQ(m1.data(), nullptr);
  
  // Матрица с нулевой размерностью
  MatrixType m2(0, 5);
  EXPECT_EQ(m2.rows(), 0u);
  EXPECT_EQ(m2.cols(), 0u);
  EXPECT_EQ(m2.data(), nullptr);
  
  MatrixType m3(5, 0);
  EXPECT_EQ(m3.rows(), 0u);
  EXPECT_EQ(m3.cols(), 0u);
  EXPECT_EQ(m3.data(), nullptr);
}

TYPED_TEST(MatrixCoreTest, ClassInvariants_DataNotNullWhenNonEmpty) {
  using MatrixType = Matrix<TypeParam>;
  
  MatrixType m(3, 4);
  EXPECT_NE(m.data(), nullptr);
  EXPECT_EQ(m.rows(), 3u);
  EXPECT_EQ(m.cols(), 4u);
}

// ============================================================================
// Тесты для граничных случаев
// ============================================================================
TYPED_TEST(MatrixCoreTest, EdgeCases_LargeMatrix) {
  using MatrixType = Matrix<TypeParam>;
  
  // Проверка работы с крупной матрицей (не слишком крупной, чтобы не исчерпать память)
  const size_type size = 100;
  MatrixType m(size, size);
  
  for (size_type i = 0; i < size; ++i) {
    for (size_type j = 0; j < size; ++j) {
      m(i, j) = static_cast<TypeParam>(i * size + j);
    }
  }
  
  for (size_type i = 0; i < size; ++i) {
    for (size_type j = 0; j < size; ++j) {
      EXPECT_EQ(m(i, j), static_cast<TypeParam>(i * size + j));
    }
  }
}
