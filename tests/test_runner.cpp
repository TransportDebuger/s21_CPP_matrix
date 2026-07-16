/**
 * @file test_runner.cpp
 * @brief Точка входа для unit-тестов библиотеки s21_matrix+.
 *
 * @details Запускает все тесты, определенные в отдельных файлах.
 *          Использует Google Test для организации и выполнения тестов.
 *
 * @author provemet (School21)
 * @version 2.0
 * @date 2026-07-16
 */

#include <gtest/gtest.h>

// Подключение всех модулей тестов
#include "test_matrix_core.cpp"
#include "test_matrix_arithmetic.cpp"
#include "test_matrix_linalg.cpp"
#include "test_exception_safety.cpp"
#include "test_edge_cases.cpp"

/**
 * @brief Основная функция, запускающая все тесты Google Test.
 *
 * @param argc Количество аргументов командной строки.
 * @param argv Массив аргументов командной строки.
 * @return int Код возврата (0 - все тесты пройдены, ненулевой - есть сбои).
 */
int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
