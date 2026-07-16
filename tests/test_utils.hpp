/**
 * @file test_utils.hpp
 * @brief Вспомогательные функции для unit-тестов.
 */

#ifndef TEST_UTILS_HPP
#define TEST_UTILS_HPP

#include <gtest/gtest.h>
#include <cmath>
#include <limits>

namespace s21_test_utils {

/**
 * @brief Сравнение двух значений с учетом эпсилона.
 *
 * @tparam T Тип сравниваемых значений.
 * @param expected Ожидаемое значение.
 * @param actual Фактическое значение.
 * @param epsilon Допустимая погрешность.
 * @return true Если значения равны в пределах эпсилона.
 * @return false Если значения отличаются более чем на эпсилон.
 */
template <typename T>
bool NearlyEqual(T expected, T actual, T epsilon) {
  if (std::isnan(expected) || std::isnan(actual)) {
    return false;
  }
  if (std::isinf(expected) || std::isinf(actual)) {
    return expected == actual;
  }
  return std::abs(expected - actual) <= epsilon;
}

/**
 * @brief Сравнение двух матриц с учетом эпсилона.
 *
 * @tparam MatrixType Тип матрицы.
 * @param expected Ожидаемая матрица.
 * @param actual Фактическая матрица.
 * @param epsilon Допустимая погрешность.
 * @return true Если матрицы равны в пределах эпсилона.
 * @return false Если матрицы отличаются более чем на эпсилон.
 */
template <typename MatrixType>
bool MatricesNearlyEqual(const MatrixType& expected, const MatrixType& actual, 
                         typename MatrixType::value_type epsilon) {
  if (expected.rows() != actual.rows() || expected.cols() != actual.cols()) {
    return false;
  }
  
  for (typename MatrixType::size_type i = 0; i < expected.rows(); ++i) {
    for (typename MatrixType::size_type j = 0; j < expected.cols(); ++j) {
      if (!NearlyEqual(expected(i, j), actual(i, j), epsilon)) {
        return false;
      }
    }
  }
  return true;
}

/**
 * @brief Создание единичной матрицы.
 *
 * @tparam MatrixType Тип матрицы.
 * @param size Размер единичной матрицы.
 * @return MatrixType Единичная матрица.
 */
template <typename MatrixType>
MatrixType IdentityMatrix(typename MatrixType::size_type size) {
  MatrixType result(size, size);
  for (typename MatrixType::size_type i = 0; i < size; ++i) {
    result(i, i) = static_cast<typename MatrixType::value_type>(1);
  }
  return result;
}

/**
 * @brief Создание нулевой матрицы.
 *
 * @tparam MatrixType Тип матрицы.
 * @param rows Количество строк.
 * @param cols Количество столбцов.
 * @return MatrixType Нулевая матрица.
 */
template <typename MatrixType>
MatrixType ZeroMatrix(typename MatrixType::size_type rows, 
                      typename MatrixType::size_type cols) {
  return MatrixType(rows, cols);
}

/**
 * @brief Генерация случайного числа в диапазоне.
 *
 * @tparam T Тип числа.
 * @param min Минимальное значение.
 * @param max Максимальное значение.
 * @return T Случайное число в диапазоне [min, max].
 */
template <typename T>
T RandomValue(T min, T max) {
  // Используем простую линейную интерполяцию
  // В реальных тестах можно использовать std::uniform_real_distribution
  static T last_value = min;
  last_value = min + (max - min) * static_cast<T>(0.5);
  return last_value;
}

}  // namespace s21_test_utils

#endif  // TEST_UTILS_HPP
