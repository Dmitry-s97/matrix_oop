/* Copyright 08.02.2023 Dmitry S

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef S21_MATRIX_OOP_H_
#define S21_MATRIX_OOP_H_

#include <math.h>

#include <iostream>

class S21Matrix {
 public:
  // Constructors
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;

  // Destructors
  ~S21Matrix();

  // Accessors
  void SetRows(int Rows);
  void SetCols(int Cols);

  // Mutators
  int GetRows();
  int GetCols();

  // Equals
  bool EqMatrix(const S21Matrix& other);

  // Multiplication
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);

  // Sum
  void SumMatrix(const S21Matrix& other);

  // Sub
  void SubMatrix(const S21Matrix& other);

  // Transpose
  S21Matrix Transpose();

  // Algebra
  double Determinant();
  S21Matrix InverseMatrix();
  S21Matrix CalcComplements();

  // Overloaded
  void operator*=(const double num);
  double& operator()(int row, int col);
  S21Matrix& operator=(S21Matrix other);
  S21Matrix operator*(const double num);
  void operator*=(const S21Matrix& other);
  void operator+=(const S21Matrix& other);
  void operator-=(const S21Matrix& other);
  bool operator==(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator+(const S21Matrix& other);

 private:
  int rows_;
  int cols_;
  double** matrix_;

  // Extra functions
  void Input();
  void CreateMatrix();
  void DeterminantExtra(S21Matrix* A, double* result);
  void InverseMatrixExtra(S21Matrix* A, S21Matrix* result);
  void CalcComplementsExtra(S21Matrix* A, S21Matrix* result);
  void Minor(int rows, int columns, S21Matrix* temp, S21Matrix* A);
};
#endif  // S21_MATRIX_OOP_H_