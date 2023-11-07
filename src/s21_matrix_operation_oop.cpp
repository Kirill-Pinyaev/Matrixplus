#include "s21_matrix_oop.h"

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  Check_matrix(&other);
  return *this == other;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  Check_matrix(&other);
  *this += other;
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  Check_matrix(&other);
  *this -= other;
}

void S21Matrix::MulNumber(const double num) { *this *= num; };

void S21Matrix::MulMatrix(const S21Matrix& other) {
  Check_matrix(&other);
  *this *= other;
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix res(cols_, rows_);
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      res.matrix_[j][i] = matrix_[i][j];
    }
  }
  return res;
}

double S21Matrix::Determinant() {
  try {
    if (rows_ != cols_) {
      throw std::invalid_argument("Matrix must be square");
    }
  } catch (std::invalid_argument()) {
  };
  S21Matrix tmp = *this;

  double det = 1;
  for (int i = 0; i < rows_; i++) {
    for (int j = i + 1; j < rows_; j++) {
      if (tmp.matrix_[i][i] == 0) {
        bool found = false;
        for (int k = i + 1; k < rows_; k++) {
          if (tmp.matrix_[k][i] != 0) {
            found = true;
            double* tmp_row = tmp.matrix_[i];
            tmp.matrix_[i] = tmp.matrix_[k];
            tmp.matrix_[k] = tmp_row;
            det *= -1;
            break;
          }
        }
        if (!found) {
          det = 0;
          i = j = rows_;
          break;
        }
      }
      double factor = tmp.matrix_[j][i] / tmp.matrix_[i][i];
      for (int k = i; k < rows_; k++) {
        tmp.matrix_[j][k] -= factor * tmp.matrix_[i][k];
      }
    }
    if (det == 0) {
      break;
    }
    det *= tmp.matrix_[i][i];
  }
  return det;
}

S21Matrix S21Matrix::CalcComplements() {
  try {
    if (this->rows_ != this->cols_)
      throw std::invalid_argument("Matrix must be square");
  } catch (std::invalid_argument()) {
  };

  S21Matrix result(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      S21Matrix sub_mat(rows_ - 1, cols_ - 1);
      int row_index = 0;
      for (int row = 0; row < rows_; row++) {
        if (row == i) {
          continue;
        }
        int col_index = 0;
        for (int col = 0; col < cols_; col++) {
          if (col == j) {
            continue;
          }
          sub_mat.matrix_[row_index][col_index] = matrix_[row][col];
          col_index++;
        }
        row_index++;
      }
      int sign = ((i + j) % 2 == 0) ? 1 : -1;
      result.matrix_[i][j] = sub_mat.Determinant() * sign;
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  int det = Determinant();
  try {
    if (det == 0) throw std::invalid_argument("Determinant is zero");
  } catch (std::invalid_argument()) {
  }
  S21Matrix result = CalcComplements().Transpose();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result.matrix_[i][j] /= det;
    }
  }
  return result;
}
