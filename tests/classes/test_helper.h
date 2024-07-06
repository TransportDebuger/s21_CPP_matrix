#ifndef TEST_HELPER_H
#define TEST_HELPER_H

#include <gtest/gtest.h>

#include "../test.h"

#define EQ_PRECISE 1e-7

namespace test_helper {
void CheckMatrix(S21Matrix& matrix, double value);
void FillMatrix(S21Matrix& matrix, double value);
}  // namespace test_helper
#endif