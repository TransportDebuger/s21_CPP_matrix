#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

#define MIN_MATRIX_DIM 0

#define EQ_PRECISE 1e-7

#define COMPR_EQUAL true
#define COMPR_NEQUAL false

class S21Matrix {
 private:
  int cols_, rows_;
  double** matrix_;
  double** createMatrix(const int rows, const int cols);
  void free();

 public:
  S21Matrix() noexcept;
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);      // Copy constructor +
  S21Matrix(S21Matrix&& other) noexcept;  // Move constructor +
  ~S21Matrix();

  double operator()(int row, int col);
  bool EqMatrix(const S21Matrix& other);  // Matrix comparisson function +
  bool operator==(
      const S21Matrix& other);  // Overloaded matrix comparisson operator +
  void SumMatrix(const S21Matrix& other);  // Matrix summarization
  S21Matrix operator+(
      const S21Matrix& other);  // Overloaded summarization operator
  S21Matrix& operator+=(
      const S21Matrix& other);  // Overloaded summarization with define operator
  void SubMatrix(const S21Matrix& other);
  S21Matrix operator-(
      const S21Matrix& other);  // Overloaded matrix substruction operator
  S21Matrix& operator-=(
      const S21Matrix& other);  // Overloaded matrix substruction operator
  void MulNumber(const double num) noexcept;  // Matrix multiplicatin by Number
  S21Matrix operator*(
      const double number);  // Overloaded mtrx-num multiplication
  S21Matrix& operator*=(
      const double num);  // Overloaded mtrx-num multiplication
  void MulMatrix(
      const S21Matrix& other);  // Matrix-matrix multiplication function
  S21Matrix operator*(
      const S21Matrix& other);  // Overloaded mtrx-mtrx multiplication
  S21Matrix& operator*=(
      const S21Matrix& other);  // Overloaded mtrx-mtrx multiplication
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  // accessors
  int getRows();
  int getCols();
  double getMatrixElement(int row, int col);
  // mutators
  void setRows(int rows);
  void setCols(int cols);
  void setMatrixElement(int row, int col, double value);
};

#endif