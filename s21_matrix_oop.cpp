#include "s21_matrix_oop.h"

#include <cmath>
#include <stdexcept>

#include "s21_matrix_err.h"

S21Matrix::S21Matrix() noexcept : cols_(0), rows_(0), matrix_(nullptr) {}

S21Matrix::S21Matrix(int rows, int cols) : cols_(cols), rows_(rows) {
  if (this->rows_ < 0 || this->cols_ < 0)
    throw std::length_error(MSG_WRONG_DIMENTION_SIZE);
  else if (this->rows_ > 0 && this->cols_ > 0)
    this->matrix_ = createMatrix(rows, cols);
  else {  
    this->rows_ = 0;
    this->cols_ = 0;
    this->matrix_ = nullptr;
  }
}

//Конструктор копирования
S21Matrix::S21Matrix(const S21Matrix& other)
    : cols_(other.cols_),
      rows_(other.rows_),
      matrix_(createMatrix(rows_, cols_)) {
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

//Конструктор переноса
S21Matrix::S21Matrix(S21Matrix&& other) noexcept
    : cols_(other.cols_), rows_(other.rows_), matrix_(other.matrix_) {
  other.matrix_ = nullptr;
  other.setRows(0);
  other.setCols(0);
  //  delete &other;
}

//Деструктор
S21Matrix::~S21Matrix() noexcept {
  if (this->matrix_ != nullptr) {
    this->free();
  }
}

double S21Matrix::operator()(int row, int col) {
  return this->getMatrixElement(row, col); 
}

//Внутренняя функция для создания матрицы
double** S21Matrix::createMatrix(const int rows, const int cols) {
  double** pmatrix = nullptr;
  if (rows > MIN_MATRIX_DIM && cols > MIN_MATRIX_DIM) {
    pmatrix = new double*[rows];
    for (int i = 0; i < rows; i++) {
      try {
        pmatrix[i] = new double[cols]{};
      } catch (std::bad_alloc&) {
        for (int j = 0; j < i; j++) {
          delete[] pmatrix[j];
        }
        delete[] pmatrix;
        throw MSG_ALLOCATION_ERROR;
      }
    }
  }
  return pmatrix;
}

//внутрення функция удаления матрицы
void S21Matrix::free() {
  for (int i = 0; i < this->rows_; i++) {
    delete[] this->matrix_[i];
  }
  delete[] this->matrix_;
  setRows(0);
  setCols(0);
}

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  bool result_code = COMPR_EQUAL;

  if (this->matrix_ != nullptr && other.matrix_ != nullptr && this->rows_ > 0 &&
      other.rows_ > 0 && this->cols_ > 0 && other.cols_ > 0 &&
      this->rows_ == other.rows_ && this->cols_ == other.cols_) {
    for (int row = 0; row < this->getRows(); row++) {
      for (int col = 0; col < this->getCols(); col++) {
        if (fabs(this->matrix_[row][col] - other.matrix_[row][col]) >=
            EQ_PRECISE) {
          result_code = COMPR_NEQUAL;
          break;
        }
      }
      if (result_code == COMPR_NEQUAL) break;
    }
  } else {
    result_code = COMPR_NEQUAL;
  }

  return result_code;
};

bool S21Matrix::operator==(const S21Matrix& other) {
  return this->EqMatrix(other);
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (this->getRows() != other.rows_ && this->getCols() != other.cols_) {
    throw MSG_NEQ_MATRIX_SIZE;
  }
  if (this->matrix_ == nullptr || other.matrix_ == nullptr) {
    throw MSG_EMPTY_MATRIX;
  }
  if (this->getRows() > 0 && this->getCols() > 0) {
    for (int i = 0; i < this->getRows(); i++) {
      for (int j = 0; j < this->getCols(); j++) {
        this->matrix_[i][j] += other.matrix_[i][j];
      }
    }
  }
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix tmp{*this};
  tmp.SumMatrix(other);
  return tmp;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  this->SumMatrix(other);
  return *this;
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (this->getRows() != other.rows_ && this->getCols() != other.cols_) {
    throw MSG_NEQ_MATRIX_SIZE;
  }
  if (this->matrix_ == nullptr || other.matrix_ == nullptr) {
    throw MSG_EMPTY_MATRIX;
  }
  if (this->getRows() > 0 && this->getCols() > 0) {
    for (int i = 0; i < this->getRows(); i++) {
      for (int j = 0; j < this->getCols(); j++) {
        this->matrix_[i][j] -= other.matrix_[i][j];
      }
    }
  }
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix tmp{*this};
  tmp.SubMatrix(other);
  return tmp;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  this->SubMatrix(other);
  return *this;
}

void S21Matrix::MulNumber(const double num) noexcept {
  for (int i = 0; i < this->getRows(); i++) {
    for (int j = 0; j < this->getCols(); j++) {
      this->matrix_[i][j] *= num;
    }
  }
}

S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix tmp{*this};
  tmp.MulNumber(num);
  return tmp;
}

S21Matrix& S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (this->getRows() != other.cols_ || this->getCols() != other.rows_) {
    throw MSG_NEQ_MATRIX_SIZE;
  }
  const int resRows = this->getRows();
  const int resCols = other.cols_;
  double** rmatrix = createMatrix(resRows, resCols);

  for (int row = 0; row < resRows; row++) {
    for (int col = 0; col < resCols; col++) {
      for (int i = 0; i < this->getCols(); i++) {
        rmatrix[row][col] += this->matrix_[row][i] + other.matrix_[i][col];
      }
    }
  }
  this->free();
  this->setRows(resRows);
  this->setCols(resCols);
  this->matrix_ = rmatrix;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix tmp{*this};
  tmp.MulMatrix(other);
  return tmp;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix tmp;

  if (this->matrix_ && this->getRows() >= MIN_MATRIX_DIM &&
      this->getCols() > MIN_MATRIX_DIM) {
    tmp.setRows(this->getCols());
    tmp.setCols(this->getRows());
    tmp.matrix_ = createMatrix(tmp.getRows(), tmp.getCols());
    for (int i = 0; i < this->getRows(); i++) {
      for (int j = 0; j < this->getCols(); j++) {
        tmp.matrix_[j][i] = this->matrix_[i][j];
      }
    }
  } else {
    throw "Wrong source matrix";
  }
  return tmp;
}

S21Matrix S21Matrix::CalcComplements() {
  S21Matrix* tmp{this};

  if (this->getCols() == this->getRows()) {
    if (this->getCols() > 1 && this->getRows() > 1) {
      for (int i = 0; i < this->getRows(); i++) {
        for (int j = 0; j < this->getCols(); j++) {
          S21Matrix minor{this->getRows() - 1, this->getCols()};
          int l = 0;
          for (int m = 0; m < this->getRows(); m++) {
            if (i != m) {
              for (int n = 0; this->getCols(); n++) {
                if (j != n) {
                  minor.matrix_[l / minor.getRows()][l % minor.getRows()] =
                      this->matrix_[m][n];
                  l++;
                }
              }
            }
          }
          tmp->matrix_[i][j] = pow(-1.0, i + j) * minor.Determinant();
        }
      }
    }
  }

  return *tmp;
}

double S21Matrix::Determinant() {
  double determinant = 0.0;
  if (this->matrix_ == nullptr) {
    throw "Matrix values are not defined";
  }
  if (this->getCols() != this->getRows()) {
    throw "Matrix is not square";
  }
  if (this->getRows() == 1) {
    determinant = this->matrix_[0][0];
  } else if (this->getRows() == 2) {
    determinant = this->matrix_[0][0] * this->matrix_[1][1] -
                  this->matrix_[1][0] * this->matrix_[0][1];
  } else {
    for (int i = 0; i < this->getCols(); i++) {
      S21Matrix minor{this->getRows() - 1, this->getCols() - 1};
      minor.createMatrix(minor.getRows(), minor.getCols());
      for (int m = 1; m < this->getRows(); m++) {
        double col_minor = 0;
        for (int n = 0; n < this->getCols(); n++) {
          if (n != i) {
            minor.matrix_[m - 1][n] = this->matrix_[m][n];
            col_minor++;
          }
        }
      }
      double minorDeterminant = minor.Determinant();
      determinant += pow(-1, i) * this->matrix_[0][i] * minorDeterminant;
    }
  }
  return determinant;
};

S21Matrix S21Matrix::InverseMatrix() {
  S21Matrix result{this->CalcComplements()};
  if (this->matrix_ == nullptr && this->getCols() <= 0 &&
      this->getRows() <= 0) {
    throw "Incorrect matrix";
  }
  if (this->getCols() != this->getRows()) {
    throw "Matrix is not square";
  }
  double determinant = this->Determinant();
  if (determinant != 0) {
    result.Transpose();
    result *= determinant;
  } else {
    throw "Calculation error";
  }
  return result;
};

int S21Matrix::getRows() { return this->rows_; };
int S21Matrix::getCols() { return this->cols_; };

double S21Matrix::getMatrixElement(int row, int col) {
  if (this->matrix_ == nullptr) {
    throw MSG_EMPTY_MATRIX;
  }
  if (row < 0 || row > this->getRows() - 1 || col < 0 ||
      col > this->getCols() - 1) {
    throw "Wrong element";
  }
  return this->matrix_[row][col];
}

void S21Matrix::setRows(int rows) { this->rows_ = rows; };
void S21Matrix::setCols(int cols) { this->cols_ = cols; };

void S21Matrix::setMatrixElement(int row, int col, double value) {
  if (this->matrix_ == nullptr) {
    throw MSG_EMPTY_MATRIX;
  }
  if (row < 0 || row > this->getRows() - 1 || col < 0 ||
      col > this->getCols() - 1) {
    throw "Wrong element";
  }
  this->matrix_[row][col] = value;
}