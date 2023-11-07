#include "s21_matrix_oop.h"

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  Check_matrix(&other);
  Clean_matrix(this);
  this->rows_ = other.rows_;
  this->cols_ = other.cols_;
  this->matrix_ = Create_matrix(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      this->matrix_[i][j] = other.matrix_[i][j];
    }
  }
  return *this;
};

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  Check_matrix(&other);
  try {
    if (this->rows_ != other.rows_ || this->cols_ != other.cols_)
      throw std::invalid_argument("Matrices must have the same size");
  } catch (std::invalid_argument()) {
  }
  S21Matrix res(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      res.matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
    }
  }
  return res;
};

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  Check_matrix(&other);
  try {
    if (this->rows_ != other.rows_ || this->cols_ != other.cols_)
      throw std::invalid_argument("Matrices must have the same size");
  } catch (std::invalid_argument()) {
  }
  S21Matrix res(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      res.matrix_[i][j] = matrix_[i][j] - other.matrix_[i][j];
    }
  }
  return res;
};

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  Check_matrix(&other);
  try {
    if (this->cols_ != other.rows_)
      throw std::invalid_argument("Invalid matrix");
  } catch (std::invalid_argument()) {
  }
  S21Matrix res(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < cols_; k++) {
        res.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  return res;
};

S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix res(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      res.matrix_[i][j] = matrix_[i][j] * num;
    }
  }
  return res;
};

bool S21Matrix::operator==(const S21Matrix& other) {
  Check_matrix(&other);
  bool res = true;
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_)
    res = false;
  else {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        if (fabs(this->matrix_[i][j] - other.matrix_[i][j]) > EPS) {
          res = false;
          break;
        }
      }
    }
  }
  return res;
};

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  Check_matrix(&other);
  try {
    if (this->rows_ != other.rows_ || this->cols_ != other.cols_)
      throw std::invalid_argument("Matrices must have the same size");
  } catch (std::invalid_argument()) {
  }
  *this = *this + other;
  return *this;
};

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  Check_matrix(&other);
  try {
    if (this->rows_ != other.rows_ || this->cols_ != other.cols_)
      throw std::invalid_argument("Matrices must have the same size");
  } catch (std::invalid_argument()) {
  }
  *this = *this - other;
  return *this;
};

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  Check_matrix(&other);
  try {
    if (this->cols_ != other.rows_)
      throw std::invalid_argument("Invalid matrix");
  } catch (std::invalid_argument()) {
  }
  *this = *this * other;
  return *this;
};

S21Matrix& S21Matrix::operator*=(const double num) {
  *this = *this * num;
  return *this;
};

double& S21Matrix::operator()(int i, int j) {
  try {
    if (i >= rows_ || j >= cols_ || i < 0 || j < 0)
      throw std::invalid_argument("Invalid arguments");
  } catch (std::invalid_argument()) {
  }
  return matrix_[i][j];
};