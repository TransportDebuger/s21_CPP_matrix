# Unit Tests for s21_matrix+

## Overview

Comprehensive unit testing suite for the s21::Matrix<T> library using Google Test framework.

## Test Structure

The test suite is organized into the following files:

### 1. test_matrix_core.cpp
**Tests for constructors, destructors, and accessors**

- Default constructor (empty matrix 0×0)
- Constructor with dimensions (rows, cols)
- Constructor with std::initializer_list (automatic dimension deduction)
- Constructor with explicit dimensions and std::initializer_list
- Copy constructor (deep copy)
- Move constructor (move semantics)
- Assignment operator (copy-and-swap)
- Destructor
- rows(), cols() accessors for various dimensions
- operator() for reading and writing
- Boundary checks (std::out_of_range)
- Class invariants:
  - data_ != nullptr iff rows_ > 0 and cols_ > 0
  - Buffer size equals rows_ * cols_
  - Empty matrix: rows_ == 0, cols_ == 0, data_ == nullptr

### 2. test_matrix_arithmetic.cpp
**Tests for element-wise arithmetic operations**

- operator+, operator+= (with matching dimensions)
- operator-, operator-= (with matching dimensions)
- operator* (scalar), operator*= (scalar)
- Size mismatch checks (std::invalid_argument)
- operator== with kEpsilon tolerance
- Comparison of empty matrices
- Comparison with NaN (returns false)

### 3. test_matrix_linalg.cpp
**Tests for linear algebra operations**

- Matrix multiplication operator*, operator*=
- Size compatibility checks (cols() == other.rows())
- transpose() (rectangular and square matrices)
- determinant() (Gaussian elimination with partial pivoting)
- calc_complements() (matrix of algebraic complements)
- inverse() (via adjugate matrix)
- Relations between operations:
  - A^(-1) = adj(A) / det(A)
  - (A × B)^T = B^T × A^T

### 4. test_exception_safety.cpp
**Tests for exception safety guarantees**

- Strong Exception Guarantee:
  - operator=: state unchanged on exception
  - copy-and-swap idiom
- No-throw Guarantee:
  - ~Matrix() destructor
  - deallocate()
  - swap()
  - Move constructor
- Class invariants after operations
- Self-assignment tests
- Copy-and-swap idiom verification
- Move semantics verification
- Const correctness tests

### 5. test_edge_cases.cpp
**Tests for edge cases and numerical stability**

- Empty matrices (0×0):
  - All operations with empty matrices
  - Invariant: data_ == nullptr
- Degenerate matrices:
  - inverse() for matrices with det ≈ 0 (std::logic_error)
  - Dynamic epsilon usage
- Invalid FPU values:
  - Matrices with NaN and Inf
  - Checking std::isnan() and std::isinf() in inverse()
- Size_type overflow:
  - Creating matrix with extreme dimensions (std::length_error)
- Numerical stability:
  - Comparison with kEpsilon tolerance
  - Dynamic epsilon in inverse()
  - Partial pivoting in determinant()

## Test Types

All tests are parameterized for three floating-point types:
- `s21::Matrix<float>`
- `s21::Matrix<double>`
- `s21::Matrix<long double>`

Uses Google Test's `TYPED_TEST` and `TYPED_TEST_SUITE` for type parameterization.

## Building and Running Tests

### Prerequisites

- CMake 3.20+
- Google Test (gtest)
- Compiler with C++20 support
- Valgrind (for memory checking)
- lcov and genhtml (for coverage reporting)

### Build Instructions

```bash
cd src/s21_matrix+
mkdir -p build && cd build
cmake .. -DLIBTYPE=static
make test_runner
```

### Running Tests

```bash
# Run all tests
make unit-test

# Or directly
./test_runner

# Run with verbose output
./test_runner --gtest_brief=0
```

### Memory Testing (Valgrind)

```bash
make mem-test
```

### Coverage Report

```bash
make gcov-report
# Open build/coverage/report/index.html in browser
```

### All Tests

```bash
make test-all
```

## Test Coverage

Target coverage:
- 100% of public functions
- ≥95% of code lines
- All critical code branches

## Exception Safety Guarantees

### Strong Guarantee (operator=)
```cpp
Matrix<T> a(2, 2);
Matrix<T> b(3, 3);
// If assignment throws, 'a' remains unchanged
a = b;  // Strong guarantee
```

### No-throw Guarantee
```cpp
Matrix<T> m(2, 2);
~Matrix<T>() noexcept;        // Destructor
m.deallocate() noexcept;      // Deallocate
swap(a, b) noexcept;          // Swap
Matrix<T>(std::move(m));      // Move constructor
```

## Numerical Stability

### Epsilon Comparison
```cpp
// Static epsilon for comparison
bool equal = (a == b);  // Uses kEpsilon internally

// Dynamic epsilon for inverse()
// Epsilon scales with matrix dimension
```

### Partial Pivoting
Determinant calculation uses partial pivoting to minimize rounding errors:
```cpp
TypeParam det = m.determinant();  // Uses partial pivoting
```

## Memory Management

All tests pass Valgrind memory checks:
```
definitely lost: 0 bytes
indirectly lost: 0 bytes
possibly lost: 0 bytes
ERROR SUMMARY: 0 errors
```

## CI/CD Integration

Tests can be integrated into CI/CD pipelines:

```yaml
# .github/workflows/tests.yml
- name: Run unit tests
  run: |
    cmake -S src/s21_matrix+ -B build
    cmake --build build --target test_runner
    ./build/test_runner

- name: Memory check
  run: |
    cmake --build build --target mem-test

- name: Coverage report
  run: |
    cmake --build build --target gcov-report
```

## Adding New Tests

1. Create a new test file in `tests/` directory
2. Include `test_utils.hpp` for helper functions
3. Use `TYPED_TEST_SUITE` for parameterized tests
4. Follow Google Test naming conventions
5. Test all edge cases and exception scenarios

Example:
```cpp
#include "test_utils.hpp"

using TestTypes = ::testing::Types<float, double, long double>;
TYPED_TEST_SUITE(MyNewTest, TestTypes);

TYPED_TEST(MyNewTest, TestName) {
  using MatrixType = Matrix<TypeParam>;
  // Test implementation
}
```

## Test Execution Order

Tests are executed in the following order:
1. test_matrix_core.cpp
2. test_matrix_arithmetic.cpp
3. test_matrix_linalg.cpp
4. test_exception_safety.cpp
5. test_edge_cases.cpp

## Coverage Analysis

Generated coverage report includes:
- Line coverage
- Function coverage
- Branch coverage

View report:
```bash
open build/coverage/report/index.html
```

## Troubleshooting

### Build Issues
- Ensure Google Test is installed: `sudo apt install libgtest-dev`
- Rebuild Google Test: `cd /usr/src/googletest && sudo cmake . && sudo make && sudo make install`

### Valgrind Errors
- Check for memory leaks in new test cases
- Ensure proper RAII implementation
- Verify destructor is noexcept

### Test Failures
- Verify kEpsilon tolerance is appropriate for the type
- Check for numerical stability issues
- Ensure proper exception handling

## License

Same as s21_matrix+ project.
