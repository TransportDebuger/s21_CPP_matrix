#include "s21_matrix_oop.h"
#include "s21_matrix_err.h"

#include <new>

//Базовый конструктор.
S21Matrix::S21Matrix() noexcept : rows_(0), cols_(0), matrix_(nullptr) {};

//Конструктор создания матрицы с определенными размерами.
S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (this->rows_ < 0 || this->cols_ < 0)  
    throw MSG_WRONG_DIMENTION_SIZE;
  try {
    this->matrix_ = new double* [rows_];
  } catch (std::bad_alloc&) {
    throw MSG_ALLOCATION_ERROR;
  }
  for (int i = 0; i < this->rows_; i++) {
    try {
      this->matrix_[i] = new double[cols_];
    } catch (std::bad_alloc&) {
      for (int j = 0; j < i; j++) {
        delete[] this->matrix_[j];
      }
      delete[] this->matrix_;
      throw MSG_ALLOCATION_ERROR;
    }
  }
};

//Конструктор копирования
S21Matrix::S21Matrix(const S21Matrix& other) {
    setRows(other.cols_);
    setCols(other.rows_);
    this->matrix_ = new double*[this->rows_];
    for (int i = 0; i < this->rows_; i++) {
      this->matrix_[i] = new double[this->cols_];
    }
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        this->matrix_[i][j] = other.matrix_[i][j];
      }
    }
};

//Конструктор переноса
S21Matrix::S21Matrix(S21Matrix&& other) {
  
};

S21Matrix::~S21Matrix() {
  for (int i = 0; i < this->rows_; i++) {
    delete[] this->matrix_[i];
  }
  delete[] this->matrix_;
};

bool S21Matrix::EqMatrix(const S21Matrix& other) {};
void S21Matrix::SumMatrix(const S21Matrix& other) {};
void S21Matrix::SubMatrix(const S21Matrix& other) {};
void S21Matrix::MulNumber(const double num) {};
void S21Matrix::MulMatrix(const S21Matrix& other) {};

S21Matrix S21Matrix::Transpose() {
  // int err_code = RES_OK;
  const int colcount = this->cols_, rowcount = this->rows_;

  if (this->matrix_ && rowcount >= MIN_MATRIX_DIM &&
      colcount > MIN_MATRIX_DIM) {
    double** transposedMatrix = new double*[rowcount];
    for (int i = 0; i < rowcount; i++) {
      transposedMatrix[i] = new double[colcount];
    }
    for (int rawPosition = 0; rawPosition < rowcount; rawPosition++) {
      for (int colPosition = 0; colPosition < colcount; colPosition++) {
        transposedMatrix[rawPosition][colPosition] =
            this->matrix_[colPosition][rawPosition];
      }
    }
    for (int i = 0; i < rowcount; i++) {
      delete[] this->matrix_[i];
    }
    delete[] this->matrix_;
    this->matrix_ = transposedMatrix;
  }
  // err_code = RES_INCORRECT_MATRIX;

  // return err_code;
};

S21Matrix S21Matrix::CalcComplements(){};
double S21Matrix::Determinant(){};
S21Matrix S21Matrix::InverseMatrix(){};

int S21Matrix::getRows() {
  return this->rows_;
};

int S21Matrix::getCols() {
  return this->cols_;
};
void S21Matrix::setRows(int rows) {
  this->rows_ = rows;
};

void S21Matrix::setCols(int cols) {
  this->cols_ = cols;
};