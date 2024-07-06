#ifndef S21_MATRIX_ERR_H
#define S21_MATRIX_ERR_H

// Memory and access error messeges
#define MSG_ALLOCATION_ERROR "Memory allocation error."
#define MSG_EMPTY_MATRIX "Matrix is not present or nullptr."
#define MSG_ELEM_ACCCESS_ERR "Wrong element."

// Matrix size exception messeges
#define MSG_WRONG_DIMENTION_SIZE \
  "Dimention size mismatch. The matrix dimentions can't be less than 0."
#define MSG_NEQ_MATRIX_SIZE "Unequal size of matrixes."

// Matrix calculation error
#define MSG_CALC_ERROR "Calculation error."
#define MSG_NOT_SQUARE_OPERANDS "Matrixes are not square."
#define MSG_DEP_DIM_UNEQUAL "Dependent dimentions are not equal."

#endif