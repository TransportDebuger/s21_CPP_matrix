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

S21Matrix::S21Matrix(const S21Matrix& other)
    : cols_(other.cols_),
      rows_(other.rows_),
      matrix_(createMatrix(other.rows_, other.cols_)) {
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept
    : cols_(other.cols_), rows_(other.rows_), matrix_(other.matrix_) {
  other.matrix_ = nullptr;
  other.setRows(0);
  other.setCols(0);
}

S21Matrix::~S21Matrix() noexcept {
  if (this->matrix_ != nullptr) {
    this->freeMatrix();
  }
}

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
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        pmatrix[i][j] = 0;
      }
    }
  }
  return pmatrix;
}

void S21Matrix::freeMatrix() {
  for (int i = 0; i < this->rows_; i++) {
    delete[] this->matrix_[i];
  }
  delete[] this->matrix_;
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  S21Matrix copy{other};
  *this = std::move(copy);
  return *this;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) noexcept {
  if (this != &other) {
    this->setCols(0);
    this->setRows(0);

    std::swap(rows_, other.rows_);
    std::swap(cols_, other.cols_);
    std::swap(matrix_, other.matrix_);
  }

  return *this;
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
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    throw MSG_NEQ_MATRIX_SIZE;
  } else if (this->matrix_ == nullptr || other.matrix_ == nullptr) {
    throw MSG_EMPTY_MATRIX;
  } else if (this->getRows() > 0 && this->getCols() > 0) {
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
  if (this->getRows() != other.rows_ || this->getCols() != other.cols_) {
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
  if (this->getCols() != other.rows_) {
    throw MSG_NEQ_MATRIX_SIZE;
  }
  const int resRows = this->getRows();
  const int resCols = other.cols_;
  double** rmatrix = createMatrix(resRows, resCols);

  for (int row = 0; row < resRows; row++) {
    for (int col = 0; col < resCols; col++) {
      for (int i = 0; i < this->getCols(); i++) {
        rmatrix[row][col] += this->matrix_[row][i] * other.matrix_[i][col];
      }
    }
  }
  this->freeMatrix();
  this->rows_ = resRows;
  this->cols_ = resCols;
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

  if (this->matrix_) {
    tmp.setRows(this->getCols());
    tmp.setCols(this->getRows());
    for (int i = 0; i < this->getRows(); i++) {
      for (int j = 0; j < this->getCols(); j++) {
        tmp.matrix_[j][i] = this->matrix_[i][j];
      }
    }
  } else {
    throw MSG_EMPTY_MATRIX;
  }
  return tmp;
}

S21Matrix S21Matrix::CalcComplements() {
  if (this->getCols() != this->getRows()) {
    throw std::length_error(MSG_DEP_DIM_UNEQUAL);
  }

  if (this->matrix_ == nullptr) {
    throw MSG_EMPTY_MATRIX;
  }

  S21Matrix result{this->getRows(), this->getCols()};

  if (this->getCols() == 1) {
    result.setMatrixElement(0, 0, 1.0);
  } else {
    for (int i = 0; i < this->getRows(); i++) {
      for (int j = 0; j < this->getCols(); j++) {
        S21Matrix minor{this->getRows() - 1, this->getCols() - 1};
        int step = 0;
        for (int m = 0; m < this->getRows(); m++) {
          if (i != m) {
            for (int n = 0; n < this->getCols(); n++) {
              if (j != n) {
                minor.setMatrixElement(step / minor.getRows(),
                                       step % minor.getRows(),
                                       this->getMatrixElement(m, n));
                step++;
              }
            }
          }
        }

        result.setMatrixElement(i, j, (pow(-1.0, i + j) * minor.Determinant()));
      }
    }
  }
  return result;
}

double S21Matrix::Determinant() {
  double determinant = 0.0;
  if (this->matrix_ == nullptr) {
    throw MSG_EMPTY_MATRIX;
  }
  if (this->getCols() != this->getRows()) {
    throw MSG_NOT_SQUARE_OPERANDS;
  }
  if (this->getRows() == 1) {
    determinant = this->matrix_[0][0];
  } else if (this->getRows() == 2) {
    determinant = this->matrix_[0][0] * this->matrix_[1][1] -
                  this->matrix_[1][0] * this->matrix_[0][1];
  } else {
    for (int i = 0; i < this->getCols(); i++) {
      S21Matrix minor{this->getRows() - 1, this->getCols() - 1};
      for (int m = 1; m < this->getRows(); m++) {
        int col_minor = 0;
        for (int n = 0; n < this->getCols(); n++) {
          if (n != i) {
            minor.setMatrixElement(m - 1, col_minor, this->matrix_[m][n]);
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
  if (this->matrix_ == nullptr) {
    throw MSG_EMPTY_MATRIX;
  }
  if (this->getCols() != this->getRows()) {
    throw MSG_NOT_SQUARE_OPERANDS;
  }
  double determinant = this->Determinant();
  S21Matrix result;
  if (determinant != 0) {
    result = this->Transpose();
    result = result.CalcComplements();
    result *= (1 / determinant);
  } else {
    throw MSG_CALC_ERROR;
  }
  return result;
};

int S21Matrix::getRows() { return this->rows_; };
int S21Matrix::getCols() { return this->cols_; };

double S21Matrix::getMatrixElement(int row, int col) {
  if (this->matrix_ == nullptr) {
    throw MSG_EMPTY_MATRIX;
  }
  if (row < 0 || row >= this->getRows() || col < 0 || col >= this->getCols()) {
    throw MSG_ELEM_ACCCESS_ERR;
  }
  return this->matrix_[row][col];
}

double S21Matrix::operator()(int row, int col) {
  return this->getMatrixElement(row, col);
}

void S21Matrix::setRows(int rows) {
  if (rows < 0) {
    throw MSG_WRONG_DIMENTION_SIZE;
  }

  double** tmp = nullptr;
  int cols = this->getCols();
  if (this->getCols() > 0 && rows > 0) {
    tmp = createMatrix(rows, cols);
  }

  if (tmp && this->matrix_) {
    int minRows = rows < this->getRows() ? rows : this->getRows();
    for (int i = 0; i < minRows; i++) {
      for (int j = 0; j < this->getCols(); j++) {
        tmp[i][j] = this->matrix_[i][j];
      }
    }
  }

  if (this->matrix_) {
    this->freeMatrix();
  }
  this->matrix_ = tmp;
  this->rows_ = rows;
};

void S21Matrix::setCols(int cols) {
  if (cols < 0) {
    throw MSG_WRONG_DIMENTION_SIZE;
  }

  double** tmp = nullptr;
  int rows = this->getRows();
  if (cols > 0 && this->getRows() > 0) {
    tmp = createMatrix(rows, cols);
  }

  if (tmp && this->matrix_) {
    int minCols = cols < this->getCols() ? cols : this->getCols();
    for (int i = 0; i < this->getRows(); i++) {
      for (int j = 0; j < minCols; j++) {
        tmp[i][j] = this->matrix_[i][j];
      }
    }
  }

  if (this->matrix_) {
    this->freeMatrix();
  }
  this->matrix_ = tmp;
  this->cols_ = cols;
};

void S21Matrix::setMatrixElement(int row, int col, double value) {
  if (this->matrix_ == nullptr) {
    throw MSG_EMPTY_MATRIX;
  }
  if (row < 0 || row > this->getRows() - 1 || col < 0 ||
      col > this->getCols() - 1) {
    throw MSG_ELEM_ACCCESS_ERR;
  }
  this->matrix_[row][col] = value;
}