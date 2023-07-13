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

#include "s21_matrix_oop.h"

// Constructors
S21Matrix::S21Matrix() : rows_(1), cols_(1), matrix_(nullptr) {
  CreateMatrix();
}

S21Matrix::S21Matrix(int rows, int cols)
    : rows_(rows), cols_(cols), matrix_(nullptr) {
  CreateMatrix();
}

S21Matrix::S21Matrix(const S21Matrix& other) {
  cols_ = other.cols_;
  rows_ = other.rows_;
  this->CreateMatrix();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept {
  cols_ = other.cols_;
  rows_ = other.rows_;
  matrix_ = other.matrix_;
  other.matrix_ = nullptr;
  other.cols_ = other.rows_ = 0;
}

// Destructors
S21Matrix::~S21Matrix() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
  rows_ = cols_ = 0;
}

// Mutators
void S21Matrix::SetRows(int Rows) {
  if (Rows != rows_) {
    S21Matrix res(Rows, cols_);
    for (int i = 0; i < res.rows_; i++) {
      for (int j = 0; j < res.cols_; j++) {
        if (i < this->rows_) {
          res.matrix_[i][j] = this->matrix_[i][j];
        }
      }
    }
    *this = res;
  }
}

void S21Matrix::SetCols(int Cols) {
  if (Cols != cols_) {
    S21Matrix res(rows_, Cols);
    for (int i = 0; i < res.rows_; i++) {
      for (int j = 0; j < res.cols_; j++) {
        if (j < this->cols_) {
          res.matrix_[i][j] = this->matrix_[i][j];
        }
      }
    }
    *this = res;
  }
}

// Accessors
int S21Matrix::GetRows() { return rows_; }

int S21Matrix::GetCols() { return cols_; }

// Equals
bool S21Matrix::EqMatrix(const S21Matrix& other) {
  bool flag = 1;
  if (cols_ != other.cols_ || rows_ != other.rows_) {
    flag = 0;
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        if (fabs(matrix_[i][j] - other.matrix_[i][j]) > 1e-7) {
          flag = 0;
        }
      }
    }
  }
  return flag;
}

// Multiplications
void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] * num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument(
        "The number of columns of the first matrix is not equal to the number "
        "of rows of the second matrix");
  }
  S21Matrix new_matrix(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < other.rows_; k++) {
        new_matrix.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = new_matrix;
}

// Sum
void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Different matrix dimensions");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

// Sub
void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Different matrix dimensions");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

// Transpose
S21Matrix S21Matrix::Transpose() {
  S21Matrix new_matrix(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      new_matrix.matrix_[j][i] = matrix_[i][j];
    }
  }
  return new_matrix;
}

// Algebra
double S21Matrix::Determinant() {
  if (cols_ != rows_) {
    throw std::invalid_argument("The matrix is not square");
  }
  double result = 0;
  S21Matrix res = *this;
  DeterminantExtra(&res, &result);
  return result;
}

S21Matrix S21Matrix::CalcComplements() {
  if (cols_ != rows_) {
    throw std::invalid_argument("The matrix is not square");
  }
  S21Matrix result(rows_, cols_);
  CalcComplementsExtra(this, &result);
  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  if (cols_ != rows_) {
    throw std::invalid_argument("The matrix is not square");
  }
  S21Matrix result(rows_, cols_);
  InverseMatrixExtra(this, &result);
  return result;
}

// Overload operators
S21Matrix& S21Matrix::operator=(S21Matrix other) {
  std::swap(cols_, other.cols_);
  std::swap(rows_, other.rows_);
  std::swap(matrix_, other.matrix_);
  return *this;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix res = *this;
  res.MulMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix res = *this;
  res.MulNumber(num);
  return res;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix res = *this;
  res.SubMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix res = *this;
  res.SumMatrix(other);
  return res;
}

void S21Matrix::operator*=(const double num) {
  S21Matrix res = *this * num;
  *this = res;
}

void S21Matrix::operator+=(const S21Matrix& other) {
  S21Matrix res = *this + other;
  *this = res;
}

void S21Matrix::operator-=(const S21Matrix& other) {
  S21Matrix res = *this - other;
  *this = res;
}

bool S21Matrix::operator==(const S21Matrix& other) {
  S21Matrix res = *this;
  return res.EqMatrix(other);
}

double& S21Matrix::operator()(int rows, int cols) {
  if (rows >= rows_ || cols >= cols_ || cols < 0 || rows < 0) {
    throw std::out_of_range("Index is outside the matrix");
  }
  return matrix_[rows][cols];
}

void S21Matrix::operator*=(const S21Matrix& other) {
  S21Matrix res = *this * other;
  *this = res;
}

// Extra functions
void S21Matrix::CreateMatrix() {
  if (rows_ <= 0 || cols_ <= 0) {
    throw std::invalid_argument("Rows and cols must be greater than 0");
  }
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
  }
  Input();
}

void S21Matrix::Input() {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = 0;
    }
  }
}

void S21Matrix::DeterminantExtra(S21Matrix* A, double* result) {
  int sign = 1;
  double temp_double = 0;
  if (A->rows_ == 1) {
    *result = A->matrix_[0][0];
  } else if (A->rows_ == 2) {
    *result = A->matrix_[0][0] * A->matrix_[1][1] -
              A->matrix_[0][1] * A->matrix_[1][0];
  } else {
    S21Matrix temp(A->rows_ - 1, A->cols_ - 1);
    for (int i = 0; i < A->rows_; i++) {
      Minor(0, i, &temp, A);
      temp_double = temp.Determinant();
      *result += A->matrix_[0][i] * temp_double * sign;
      sign *= -1;
    }
  }
}

void S21Matrix::Minor(int rows, int columns, S21Matrix* temp, S21Matrix* A) {
  int rows_plus_one = 0;
  int columns_plus_one = 0;
  for (int i = 0; i < temp->rows_; i++) {
    if (i == rows) {
      rows_plus_one++;
    }
    columns_plus_one = 0;
    for (int j = 0; j < temp->cols_; j++) {
      if (j == columns) {
        columns_plus_one++;
      }
      temp->matrix_[i][j] = A->matrix_[i + rows_plus_one][j + columns_plus_one];
    }
  }
}

void S21Matrix::CalcComplementsExtra(S21Matrix* A, S21Matrix* result) {
  if (A->rows_ == 1) {
    result->matrix_[0][0] = A->matrix_[0][0];
  } else {
    int sign = 1;
    for (int i = 0; i < A->rows_; i++) {
      for (int j = 0; j < A->cols_; j++) {
        S21Matrix temp(A->rows_ - 1, A->cols_ - 1);
        Minor(i, j, &temp, A);
        if ((i + j) % 2 == 0) {
          sign = 1;
        } else if ((i + j) % 2 != 0) {
          sign = -1;
        }
        double temp_double = temp.Determinant();
        result->matrix_[i][j] = temp_double * sign;
      }
    }
  }
}

void S21Matrix::InverseMatrixExtra(S21Matrix* A, S21Matrix* result) {
  double determinant = A->Determinant();
  if (determinant == 0) {
    throw std::invalid_argument("Matrix determinant is 0");
  }
  S21Matrix temp = A->CalcComplements();
  S21Matrix temp_trantemp = temp.Transpose();
  temp_trantemp.MulNumber(1 / determinant);
  *result = temp_trantemp;
}