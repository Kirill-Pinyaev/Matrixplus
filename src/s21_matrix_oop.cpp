#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() {
  rows_ = 2;
  cols_ = 3;
  matrix_ = Create_matrix(rows_, cols_);
}

S21Matrix::S21Matrix(int rows, int cols) {
  rows_ = rows;
  cols_ = cols;
  matrix_ = Create_matrix(rows_, cols_);
}

S21Matrix::S21Matrix(const S21Matrix& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = Create_matrix(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;
  other.matrix_ = nullptr;
  other.rows_ = other.cols_ = 0;
}

S21Matrix::~S21Matrix() {
  rows_ = cols_ = 0;
  for (int i = 0; i < rows_; i++) {
    if (matrix_[i]) {
      delete[] matrix_[i];
      matrix_[i] = nullptr;
    }
  }
  if (matrix_) {
    delete[] matrix_;
    matrix_ = nullptr;
  }
}