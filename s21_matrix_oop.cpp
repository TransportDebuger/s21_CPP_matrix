#include "s21_matrix_oop.h"

S21Matrix::S21Matrix(int rows, int cols) {
    if (rows >= MIN_MATRIX_DIM && cols >= MIN_MATRIX_DIM) {
        this->cols_ = cols;
        this->rows_ = rows;
        this->matrix_ = new double*[this->rows_];
        for (int i = 0; i < this->rows_; i++) {
            this->matrix_[i] = new double[this->cols_];
        }
    } else {
        throw "Error. The dimention of matrix must be equal or higher 1.";
    }
};

//Дефолтный конструктор. Вызывает коструктор определенный с параметрами размера матрицы.
S21Matrix::S21Matrix():  S21Matrix::S21Matrix(MIN_MATRIX_DIM, MIN_MATRIX_DIM) {};

//Конструктор копирования
S21Matrix::S21Matrix(const S21Matrix& other) {
    this->cols_ = other.cols_;
    this->rows_ = other.rows_;
    this->matrix_ = new double*[this->rows_];
    for (int i = 0; i < this->rows_; i++) {
        this->matrix_[i] = new double[this->cols_];
    }
}; 

//Конструктор переноса
S21Matrix::S21Matrix(S21Matrix&& other) {};

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
  //int err_code = RES_OK;
  const int colcount = this->cols_,
            rowcount = this->rows_;

  if (this->matrix_ && rowcount >= MIN_MATRIX_DIM && colcount > MIN_MATRIX_DIM) {
    double** transposedMatrix = new double*[rowcount];
    for (int i = 0; i < rowcount; i++) {
        transposedMatrix[i] = new double[colcount];
    }
    for (int rawPosition = 0; rawPosition < rowcount; rawPosition++) {
        for (int colPosition = 0; colPosition < colcount; colPosition++) {
            transposedMatrix[rawPosition][colPosition] = this->matrix_[colPosition][rawPosition];
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

S21Matrix S21Matrix::CalcComplements() {};
double S21Matrix::Determinant() {};
S21Matrix S21Matrix::InverseMatrix() {};
