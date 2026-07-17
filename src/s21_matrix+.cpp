/**
 * @file s21_matrix+.cpp
 * @brief Файл реализации шаблонного класса s21::Matrix<T>.
 *
 * @author provemet (School21)
 * @version 2.0
 * @date 2026-07-16
 */

#include "s21_matrix+.hpp"

#include <cmath>
#include <limits>
#include <stdexcept>

namespace s21 {

template <std::floating_point T>
Matrix<T>::Matrix() noexcept = default;

template <std::floating_point T>
Matrix<T>::Matrix(size_type rows, size_type cols) : rows_(rows), cols_(cols) {
  if (rows_ == 0 || cols_ == 0) {
    rows_ = 0;
    cols_ = 0;
    data_ = nullptr;
    return;
  }
  allocate(rows_, cols_);
}

template <std::floating_point T>
Matrix<T>::Matrix(std::initializer_list<value_type> values) {
    size_type size = values.size();

    if (size == 0) {
        rows_ = 0;
        cols_ = 0;
        data_ = nullptr;
        return;
    }

    size_type dim = static_cast<size_type>(std::sqrt(static_cast<double>(size)));

    bool is_perfect_square = false;
    for (size_type candidate = (dim > 0 ? dim - 1 : 0); candidate <= dim + 1; ++candidate) {
        if (candidate > 0 && size / candidate == candidate && size % candidate == 0) {
            dim = candidate;
            is_perfect_square = true;
            break;
        }
    }

    if (!is_perfect_square) {
        throw std::invalid_argument("Size of initializer_list must be square");
    }

    rows_ = dim;
    cols_ = dim;
    allocate(rows_, cols_);
    
    std::copy(values.begin(), values.end(), data_);
}

template <std::floating_point T>
Matrix<T>::Matrix(size_type rows, size_type cols, std::initializer_list<value_type> values) 
    : rows_(rows), cols_(cols) {
  
  size_type expected_size = rows_ * cols_;
  if (values.size() != expected_size) {
    throw std::invalid_argument(
        "Initializer list size does not match the specified matrix dimensions");
  }

  if (expected_size == 0) {
    data_ = nullptr;
    return;
  }

  allocate(rows_, cols_);
  std::copy(values.begin(), values.end(), data_);
}

template <std::floating_point T>
Matrix<T>::Matrix(const Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  if (rows_ > 0 && cols_ > 0) {
    allocate(rows_, cols_);
    std::size_t n = rows_ * cols_;
    for (std::size_t i = 0; i < n; ++i) {
      data_[i] = other.data_[i];
    }
  }
}

template <std::floating_point T>
Matrix<T>::Matrix(Matrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_), data_(other.data_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.data_ = nullptr;
}

template <std::floating_point T>
Matrix<T>& Matrix<T>::operator=(Matrix other) {
  // copy-and-swap
  std::swap(rows_, other.rows_);
  std::swap(cols_, other.cols_);
  std::swap(data_, other.data_);
  return *this;
}

template <std::floating_point T>
Matrix<T>::~Matrix() noexcept {
  deallocate();
}

template <std::floating_point T>
typename Matrix<T>::value_type& Matrix<T>::operator()(size_type row,
                                                      size_type col) {
  if (row >= rows_ || col >= cols_) {
    throw std::out_of_range("Matrix index out of range");
  }
  return data_[row * cols_ + col];
}

template <std::floating_point T>
const typename Matrix<T>::value_type& Matrix<T>::operator()(
    size_type row, size_type col) const {
  if (row >= rows_ || col >= cols_) {
    throw std::out_of_range("Matrix index out of range");
  }
  return data_[row * cols_ + col];
}

template <std::floating_point T>
typename Matrix<T>::size_type Matrix<T>::rows() const noexcept {
  return rows_;
}

template <std::floating_point T>
typename Matrix<T>::size_type Matrix<T>::cols() const noexcept {
  return cols_;
}

template <std::floating_point T>
bool Matrix<T>::operator==(const Matrix& other) const noexcept {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        return false;
    }
    
    if (data_ == nullptr && other.data_ == nullptr) {
        return true;
    }

    const size_type total_size = rows_ * cols_;
    for (size_type i = 0; i < total_size; ++i) {
        if (std::isnan(data_[i]) || std::isnan(other.data_[i])) {
            return false;
        }
        
        if (std::abs(data_[i] - other.data_[i]) > kEpsilon) {
            return false;
        }
    }
    return true;
}

template <std::floating_point T>
Matrix<T>& Matrix<T>::operator+=(const Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Unequal matrix sizes");
  }
  std::size_t n = rows_ * cols_;
  for (std::size_t i = 0; i < n; ++i) {
    data_[i] += other.data_[i];
  }
  return *this;
}

template <std::floating_point T>
Matrix<T> Matrix<T>::operator+(const Matrix& other) const {
  Matrix result(*this); 
  result += other;      
  return result;        
}

template <std::floating_point T>
Matrix<T>& Matrix<T>::operator-=(const Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Unequal matrix sizes");
  }
  
  const size_type total_elements = rows_ * cols_;
  for (size_type i = 0; i < total_elements; ++i) {
    data_[i] -= other.data_[i];
  }
  
  return *this;
}

template <std::floating_point T>
Matrix<T> Matrix<T>::operator-(const Matrix& other) const {
  Matrix result{*this};
  result -= other;
  return result;
}

template <std::floating_point T>
Matrix<T>& Matrix<T>::operator*=(value_type scalar) {
  std::size_t n = rows_ * cols_;
  for (std::size_t i = 0; i < n; ++i) {
    data_[i] *= scalar;
  }
  return *this;
}

template <std::floating_point T>
Matrix<T>& Matrix<T>::operator*=(const Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument("Matrix dimensions are not compatible for multiplication");
  }
  
  Matrix result(rows_, other.cols_);
  
  // Порядок циклов r, k, c для оптимизации кэш-локальности 
  // (последовательное чтение из *this и result, линейное чтение из other)
  for (size_type r = 0; r < rows_; ++r) {
    for (size_type k = 0; k < cols_; ++k) {
      value_type a_ik = data_[r * cols_ + k]; // Прямой доступ без проверок
      for (size_type c = 0; c < other.cols_; ++c) {
        result.data_[r * other.cols_ + c] += a_ik * other.data_[k * other.cols_ + c];
      }
    }
  }
  
  *this = std::move(result);
  return *this;
}

template <std::floating_point T>
Matrix<T> Matrix<T>::operator*(value_type scalar) const {
  Matrix result{*this};
  result *= scalar;
  return result;
}

template <std::floating_point T>
Matrix<T> Matrix<T>::operator*(const Matrix& other) const {
  Matrix result{*this};
  result *= other;
  return result;
}

template <std::floating_point T>
Matrix<T> Matrix<T>::transpose() const {
  // Создаем новую матрицу с инвертированными размерностями.
  // Если текущая матрица пуста (rows_ == 0 или cols_ == 0), 
  // конструктор корректно обработает это и создаст пустую матрицу.
  Matrix result(cols_, rows_);

  // Если матрица пуста, циклы не выполнятся, и вернется пустой result.
  for (size_type i = 0; i < rows_; ++i) {
    // Указатель на начало текущей строки исходной матрицы.
    // Это помогает компилятору оптимизировать чтение и улучшает кэш-локальность.
    const value_type* src_row = data_ + (i * cols_);
    
    for (size_type j = 0; j < cols_; ++j) {
      // Прямой доступ к памяти.
      // Индекс в исходной матрице (row-major): i * cols_ + j
      // Индекс в транспонированной матрице: j * rows_ + i
      result.data_[(j * rows_) + i] = src_row[j];
    }
  }

  return result;
}

template <std::floating_point T>
Matrix<T> Matrix<T>::calc_complements() const {
  // 1. Проверка на квадратность и непустоту
  if (rows_ != cols_) {
    throw std::invalid_argument("Matrix must be square to calculate complements");
  }
  if (rows_ == 0) {
    throw std::invalid_argument("Cannot calculate complements of an empty matrix");
  }
  
  // 2. Базовый случай для матрицы 1x1: алгебраическое дополнение равно 1
  if (rows_ == 1) {
    Matrix result(1, 1);
    result(0, 0) = static_cast<value_type>(1.0);
    return result;
  }

  Matrix result(rows_, cols_);
  
  // 3. Выделение памяти под минорную матрицу ЕДИНОЖДЫ вне циклов.
  // Это снижает количество аллокаций с O(N^2) до O(1).
  Matrix minor(rows_ - 1, cols_ - 1);

  for (size_type i = 0; i < rows_; ++i) {
    for (size_type j = 0; j < cols_; ++j) {
      
      // 4. Заполнение минорной матрицы пропуском строки i и столбца j
      size_type mi = 0;
      for (size_type r = 0; r < rows_; ++r) {
        if (r == i) continue;
        size_type mj = 0;
        for (size_type c = 0; c < cols_; ++c) {
          if (c == j) continue;
          // Прямой доступ к data_ для обеих матриц.
          // Это полностью исключает накладные расходы на проверку границ operator().
          minor.data_[mi * minor.cols_ + mj] = data_[r * cols_ + c];
          ++mj;
        }
        ++mi;
      }
      
      // 5. Вычисление знака (-1)^(i+j) без использования std::pow
      value_type sign = ((i + j) % 2 == 0) ? static_cast<value_type>(1.0) 
                                           : static_cast<value_type>(-1.0);
      
      // 6. Вычисление определителя минора и запись результата
      result(i, j) = sign * minor.determinant();
    }
  }

  return result;
}

template <std::floating_point T>
typename Matrix<T>::value_type Matrix<T>::determinant() const {
  // 1. Проверка на квадратность и непустоту
  if (rows_ != cols_) {
    throw std::invalid_argument("Matrix must be square to calculate determinant");
  }
  if (rows_ == 0) {
    throw std::invalid_argument("Cannot calculate determinant of an empty matrix");
  }
  
  // 2. Базовый случай для матрицы 1x1
  if (rows_ == 1) {
    return data_[0];
  }

  // 3. Создание копии матрицы для выполнения преобразований.
  // Это необходимо, так как метод помечен как const и не должен изменять *this.
  // Для малых матриц (4x4) аллокация занимает наносекунды.
  Matrix<T> temp{*this};
  
  value_type det = static_cast<value_type>(1.0);
  
  // Практический допуск для сравнения с нулем.
  // Машинный эпсилон, умноженный на размерность матрицы, компенсирует 
  // накопление ошибок округления при операциях с плавающей точкой.
  const value_type epsilon = std::numeric_limits<value_type>::epsilon() * 
                             static_cast<value_type>(rows_);

  // 4. Прямой ход метода Гаусса (приведение к верхнетреугольному виду)
  for (size_type i = 0; i < rows_; ++i) {
    
    // Partial Pivoting: поиск строки с максимальным по модулю элементом в текущем столбце.
    // Это критически важно для численной стабильности и избежания деления на ноль.
    size_type max_row = i;
    value_type max_val = std::abs(temp.data_[i * cols_ + i]);
    
    for (size_type j = i + 1; j < rows_; ++j) {
      value_type current_val = std::abs(temp.data_[j * cols_ + i]);
      if (current_val > max_val) {
        max_val = current_val;
        max_row = j;
      }
    }
    
    // Если главный элемент равен нулю (или меньше эпсилона), определитель равен 0
    if (max_val < epsilon) {
      return static_cast<value_type>(0.0);
    }
    
    // Обмен строк, если максимальный элемент не на главной диагонали
    if (max_row != i) {
      // Прямой доступ к памяти для обмена элементов строк
      for (size_type k = 0; k < cols_; ++k) {
        std::swap(temp.data_[i * cols_ + k], temp.data_[max_row * cols_ + k]);
      }
      det = -det; // При перестановке двух строк знак определителя меняется
    }
    
    // Умножаем определитель на текущий главный элемент (диагональный)
    value_type pivot = temp.data_[i * cols_ + i];
    det *= pivot;
    
    // 5. Исключение элементов ниже главной диагонали
    for (size_type j = i + 1; j < rows_; ++j) {
      value_type factor = temp.data_[j * cols_ + i] / pivot;
      
      // Оптимизация: начинаем цикл с i + 1, так как элементы до i уже нулевые
      for (size_type k = i + 1; k < cols_; ++k) {
        temp.data_[j * cols_ + k] -= factor * temp.data_[i * cols_ + k];
      }
    }
  }
  
  return det;
}

template <std::floating_point T>
Matrix<T> Matrix<T>::inverse() const {
  // 1. Проверка на квадратность и непустоту
  if (rows_ != cols_) {
    throw std::invalid_argument("Matrix must be square to calculate inverse");
  }
  if (rows_ == 0) {
    throw std::invalid_argument("Cannot invert an empty matrix");
  }

  // 2. Вычисление определителя
  value_type det = determinant();

  if (std::isnan(det) || std::isinf(det)) {
        throw std::logic_error("Matrix determinant has invalid value (NaN or Inf)");
  }
  // 3. Проверка матрицы на вырожденность (сингулярность).
  // Прямое сравнение det == 0 для чисел с плавающей точкой некорректно.
  // Используем динамический эпсилон, масштабированный на размерность матрицы,
  // чтобы учесть накопленную погрешность при вычислении определителя.
  const value_type epsilon = std::numeric_limits<value_type>::epsilon() * 
                             static_cast<value_type>(rows_);
  
  if (std::abs(det) < epsilon) {
    throw std::logic_error("Matrix is singular and cannot be inverted");
  }

  // 4. Формирование присоединенной матрицы (adjugate matrix).
  // Математически: adj(A) = transpose(calc_complements(A))
  // Мы создаем матрицу алгебраических дополнений и сразу транспонируем её.
  Matrix adj = calc_complements().transpose();

  // 5. Умножение на обратное значение определителя.
  // Операция выполняется "на месте" (in-place) через operator*=, 
  // что исключает создание лишних временных объектов.
  adj *= (static_cast<value_type>(1.0) / det);

  return adj;
}

template <std::floating_point T>
void Matrix<T>::allocate(size_type rows, size_type cols) {
  if (rows == 0 || cols == 0) {
    rows_ = 0;
    cols_ = 0;
    data_ = nullptr;
    return;
  }

  if (rows > std::numeric_limits<size_type>::max() / cols) {
    throw std::length_error("Matrix dimensions cause size overflow");
  }

  size_type total_size = rows * cols;

  data_ = new value_type[total_size]();
  
  rows_ = rows;
  cols_ = cols;
}

template <std::floating_point T>
void Matrix<T>::deallocate() noexcept {
  delete[] data_;
  
  data_ = nullptr;
  rows_ = 0;
  cols_ = 0;
}

template class Matrix<float>;
template class Matrix<double>;
template class Matrix<long double>;

}  // namespace s21