#include "s21_matrix_oop.h"

void S21Matrix::Remove_bad_matrix(S21Matrix* matrix, int num) {
  try {
    for (int i = 0; i < num; i++) {
      if (matrix->matrix_[i]) {
        delete[] matrix->matrix_[i];
        matrix->matrix_[i] = nullptr;
      }
    }
    delete[] matrix->matrix_;
    matrix->matrix_ = nullptr;
    matrix->rows_ = matrix->cols_ = 0;
    throw std::bad_alloc();
  } catch (std::bad_alloc()) {
    std::cout << "Failed to allocate memory" << std::endl;
  }
};

void S21Matrix::Check_matrix(const S21Matrix* other) {
  try {
    if (!other->matrix_) throw std::bad_alloc();
    if (other->rows_ < 1 || other->cols_ < 1)
      throw std::length_error("Invalid arguments");
    for (int i = 0; i < other->rows_; i++) {
      if (!other->matrix_[i]) throw std::bad_alloc();
    }
  } catch (std::bad_alloc()) {
    std::cout << "Failed to allocate memory" << std::endl;
  } catch (std::length_error()) {
  }
};

void S21Matrix::Clean_matrix(S21Matrix* other) {
  Check_matrix(other);
  for (int i = 0; i < other->rows_; i++) {
    if (other->matrix_[i]) delete[] other->matrix_[i];
  }
  delete[] other->matrix_;
  other->rows_ = other->cols_ = 0;
};

int S21Matrix::S21GetRows() noexcept { return rows_; };

int S21Matrix::S21GetCols() noexcept { return cols_; };

void S21Matrix::S21SetRows(int rows) {
  if (rows == this->rows_) {
  } else {
    S21Matrix res(rows, this->cols_);
    int tmp = rows < this->rows_ ? rows : this->rows_;

    for (int i = 0; i < tmp; i++) {
      memcpy(res.matrix_[i], this->matrix_[i], this->cols_ * sizeof(double));
    }
    *this = res;
  }
}

void S21Matrix::S21SetCols(int cols) {
  if (cols == this->cols_) {
  } else {
    S21Matrix res(this->rows_, cols);
    int tmp = cols < this->cols_ ? cols : this->cols_;

    for (int i = 0; i < this->rows_; i++) {
      memcpy(res.matrix_[i], this->matrix_[i], tmp * sizeof(double));
    }
    *this = res;
  }
}

double** S21Matrix::Create_matrix(int rows, int cols) {
  int i = 0;
  double** result = nullptr;
  try {
    if (rows < 1 || cols < 1) {
      throw std::out_of_range("Invalid arguments");
    }
    result = new double*[rows];
    for (; i < rows; i++) {
      result[i] = new double[cols];
      memset(result[i], 0, cols * sizeof(double));
    }
  } catch (std::bad_alloc& exception) {
    Remove_bad_matrix(this, i);
  } catch (std::out_of_range()) {
  };
  return result;
}