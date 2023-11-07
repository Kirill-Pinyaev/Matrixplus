#ifndef _S21MATRIX_H_
#define _S21MATRIX_H_
#define EPS 1e-6

#include <string.h>

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

class S21Matrix {
 private:
  int rows_;
  int cols_;
  double **matrix_;

  void Remove_bad_matrix(S21Matrix *bad_matrix, int num);
  void Check_matrix(const S21Matrix *other);
  void Clean_matrix(S21Matrix *other);
  double **Create_matrix(int rows, int cols);

 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other) noexcept;
  ~S21Matrix();

  int S21GetRows() noexcept;
  int S21GetCols() noexcept;
  void S21SetRows(int rows);
  void S21SetCols(int cols);

  bool EqMatrix(const S21Matrix &other);
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose();
  double Determinant();
  S21Matrix CalcComplements();
  S21Matrix InverseMatrix();

  S21Matrix &operator=(const S21Matrix &other);
  S21Matrix operator+(const S21Matrix &other);
  S21Matrix &operator+=(const S21Matrix &other);
  S21Matrix operator-(const S21Matrix &other);
  S21Matrix &operator-=(const S21Matrix &other);
  S21Matrix operator*(const double num);
  S21Matrix &operator*=(const double num);
  S21Matrix operator*(const S21Matrix &other);
  S21Matrix &operator*=(const S21Matrix &other);
  double &operator()(int rows, int cols);
  bool operator==(const S21Matrix &other);
};

#endif