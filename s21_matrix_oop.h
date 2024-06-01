#ifndef S21_MATRIX_OOP
#define S21_MATRIX_OOP

#define MIN_MATRIX_DIM 0
#define DEFAULT_ELEMENT_VAL 0

class S21Matrix {
 private:
  int cols_, rows_;
  double** matrix_;

 public:
//project functionality
  S21Matrix();                        // default constructor +
  S21Matrix(int rows, int cols);      // Parametrized constructor +
  S21Matrix(const S21Matrix& other);  // Copy constructor
  S21Matrix(S21Matrix&& other);       // Move constructor
  ~S21Matrix();
  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

//accessors
  int getRows();
  int getCols();
//mutators
  void setRows(int rows);
  void setCols(int cols);

};

#endif