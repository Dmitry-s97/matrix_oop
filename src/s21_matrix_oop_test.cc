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

#include <gtest/gtest.h>

TEST(Test_1, Mutators_and_BasicConstructor) {
  S21Matrix a;
  int rows = a.GetRows();
  int cols = a.GetCols();
  ASSERT_TRUE(rows == 1);
  ASSERT_TRUE(cols == 1);
}

TEST(Test_2, Mutators_and_ParametrizedConstructor) {
  S21Matrix a(3, 5);
  int rows = a.GetRows();
  int cols = a.GetCols();
  ASSERT_TRUE(rows == 3);
  ASSERT_TRUE(cols == 5);
}

TEST(Test_3, Accessors) {
  S21Matrix a;
  a.SetRows(7);
  int rows = a.GetRows();
  ASSERT_TRUE(rows == 7);
  a.SetCols(5);
  int cols = a.GetCols();
  ASSERT_TRUE(cols == 5);
}

TEST(Test_4, Copy) {
  S21Matrix a(2, 4);
  S21Matrix b = a;
  int rows_a = a.GetRows();
  int cols_a = a.GetCols();
  int rows_b = b.GetRows();
  int cols_b = b.GetCols();

  ASSERT_TRUE(rows_a == 2);
  ASSERT_TRUE(cols_a == 4);
  ASSERT_TRUE(rows_b == 2);
  ASSERT_TRUE(cols_b == 4);
  ASSERT_TRUE(a(0, 0) == b(0, 0));
  ASSERT_TRUE(a(1, 0) == b(1, 0));
  ASSERT_TRUE(a(1, 1) == b(1, 1));
  ASSERT_TRUE(a(1, 2) == b(1, 2));
  ASSERT_TRUE(a(1, 3) == b(1, 3));
}

TEST(Test_5, Move) {
  S21Matrix a(3, 5);
  S21Matrix b = std::move(a);
  S21Matrix c = b;

  int rows_b = b.GetRows();
  int cols_b = b.GetCols();
  int rows_c = c.GetRows();
  int cols_c = c.GetCols();

  ASSERT_TRUE(rows_b == 3);
  ASSERT_TRUE(cols_b == 5);
  ASSERT_TRUE(rows_c == 3);
  ASSERT_TRUE(cols_c == 5);

  ASSERT_TRUE(b(0, 0) == c(0, 0));
  ASSERT_TRUE(b(1, 0) == c(1, 0));
  ASSERT_TRUE(b(2, 0) == c(2, 0));
  ASSERT_TRUE(b(1, 1) == c(1, 1));
  ASSERT_TRUE(b(1, 2) == c(1, 2));
  ASSERT_TRUE(b(1, 3) == c(1, 3));
  ASSERT_TRUE(b(1, 4) == c(1, 4));
}

TEST(Test_6, EQ) {
  S21Matrix a(7, 6);
  S21Matrix b = a;
  int res = b.EqMatrix(a);
  ASSERT_TRUE(res == 1);
  S21Matrix c(7, 6);
  for (int i = 0; i < c.GetRows(); i++) {
    for (int j = 0; j < c.GetCols(); j++) {
      c(i, j) = i + j;
    }
  }
  res = b.EqMatrix(c);
  ASSERT_TRUE(0 == 0);
}

TEST(Test_7, Sum) {
  S21Matrix a(10, 10);
  S21Matrix b(10, 10);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      a(i, j) = 15;
      b(i, j) = 30;
    }
  }
  S21Matrix c = b + a;
  b.SumMatrix(a);
  for (int i = 0; i < b.GetRows(); i++) {
    for (int j = 0; j < b.GetCols(); j++) {
      ASSERT_TRUE(c(i, j) == 45);
      ASSERT_TRUE(b(i, j) == 45);
    }
  }
}

TEST(Test_8, Sub) {
  S21Matrix a(10, 10);
  S21Matrix b(10, 10);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      a(i, j) = 15;
      b(i, j) = 30;
    }
  }
  b.SubMatrix(a);
  S21Matrix c = b;
  c - a;
  for (int i = 0; i < b.GetRows(); i++) {
    for (int j = 0; j < b.GetCols(); j++) {
      ASSERT_TRUE(b(i, j) == 15);
      ASSERT_TRUE(c(i, j) == 15);
    }
  }
}

TEST(Test_9, MulNum) {
  S21Matrix a(10, 10);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      a(i, j) = 15.7;
    }
  }
  S21Matrix b = a * 3.6;
  a.MulNumber(3.6);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      ASSERT_TRUE(a(i, j) == 3.6 * 15.7);
      ASSERT_TRUE(b(i, j) == 3.6 * 15.7);
    }
  }
}

TEST(Test_10, MulMatrix) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      a(i, j) = 15.6;
      b(i, j) = 2.6;
    }
  }
  b.MulMatrix(a);
  for (int i = 0; i < b.GetRows(); i++) {
    for (int j = 0; j < b.GetCols(); j++) {
      ASSERT_TRUE(b(i, j) == 81.12);
    }
  }
}

TEST(Test_11, Transpose) {
  S21Matrix a(5, 2);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      a(i, j) = rand() % 10;
    }
  }
  ASSERT_TRUE(a.GetRows() == 5);
  ASSERT_TRUE(a.GetCols() == 2);
  S21Matrix b = a.Transpose();
  ASSERT_TRUE(b.GetRows() == 2);
  ASSERT_TRUE(b.GetCols() == 5);
}

TEST(Test_12, determinant) {
  S21Matrix matrix(4, 4);
  matrix(0, 0) = 4.0;
  matrix(0, 1) = 3.0;
  matrix(0, 2) = 2.0;
  matrix(0, 3) = 2.0;
  matrix(1, 0) = 0.0;
  matrix(1, 1) = 1.0;
  matrix(1, 2) = -3.0;
  matrix(1, 3) = 3.0;
  matrix(2, 0) = 0.0;
  matrix(2, 1) = -1.0;
  matrix(2, 2) = 3.0;
  matrix(2, 3) = 3.0;
  matrix(3, 0) = 0.0;
  matrix(3, 1) = 3.0;
  matrix(3, 2) = 1.0;
  matrix(3, 3) = 1.0;
  double result = matrix.Determinant();
  ASSERT_TRUE(result == -240);
}

TEST(Test_13, Calc_complements) {
  int res = 0;
  S21Matrix A(4, 4);
  A(0, 0) = 112.0;
  A(0, 1) = 243.0;
  A(0, 2) = 3.0;
  A(0, 3) = -8.0;
  A(1, 0) = 47.0;
  A(1, 1) = 51.0;
  A(1, 2) = -66.0;
  A(1, 3) = 99.0;
  A(2, 0) = -74.0;
  A(2, 1) = 85.0;
  A(2, 2) = 97.0;
  A(2, 3) = 63.0;
  A(3, 0) = -13.0;
  A(3, 1) = 79.0;
  A(3, 2) = -99.0;
  A(3, 3) = -121.0;
  S21Matrix Z = A.CalcComplements();
  S21Matrix X(4, 4);
  X(0, 0) = -2879514.0;
  X(0, 1) = -1236631.0;
  X(0, 2) = -1685096.0;
  X(0, 3) = 880697.0;
  X(1, 0) = 1162090.0;
  X(1, 1) = -714015.0;
  X(1, 2) = 4046255.0;
  X(1, 3) = -3901600.0;
  X(2, 0) = 4362897.0;
  X(2, 1) = -2049432.0;
  X(2, 2) = -532912.0;
  X(2, 3) = -1370781.0;
  X(3, 0) = 3412773.0;
  X(3, 1) = -1569493.0;
  X(3, 2) = 3144517.0;
  X(3, 3) = 1284666.0;
  res = X.EqMatrix(Z);
  ASSERT_TRUE(res == 1);
}

TEST(Test_14, Inverse) {
  S21Matrix A(4, 4);
  A(0, 0) = -1.0;
  A(0, 1) = 2.0;
  A(0, 2) = 7.0;
  A(0, 3) = 9.0;
  A(1, 0) = 1.0;
  A(1, 1) = 0.0;
  A(1, 2) = 0.0;
  A(1, 3) = 0.0;
  A(2, 0) = 47.0;
  A(2, 1) = 13.0;
  A(2, 2) = 17.0;
  A(2, 3) = 21.0;
  A(3, 0) = 22.0;
  A(3, 1) = 7.0;
  A(3, 2) = 1.0;
  A(3, 3) = 3.0;
  S21Matrix Z = A.InverseMatrix();
  S21Matrix X(4, 4);
  X(0, 0) = 0.0;
  X(0, 1) = 1.0;
  X(0, 2) = 0.0;
  X(0, 3) = 0.0;
  X(1, 0) = -5.0 / 23.0;
  X(1, 1) = -121.0 / 23.0;
  X(1, 2) = 2.0 / 23.0;
  X(1, 3) = 1.0 / 23.0;
  X(2, 0) = -18.0 / 23.0;
  X(2, 1) = -379.0 / 46.0;
  X(2, 2) = 19.0 / 46.0;
  X(2, 3) = -25.0 / 46.0;
  X(3, 0) = 53.0 / 69.0;
  X(3, 1) = 1061.0 / 138.0;
  X(3, 2) = -47.0 / 138.0;
  X(3, 3) = 19.0 / 46.0;
  int res = X.EqMatrix(Z);
  int res_2 = X == Z;
  ASSERT_TRUE(res == 1);
  ASSERT_TRUE(res_2 == 1);
}

TEST(Test_15, MulNumOver) {
  S21Matrix a(10, 10);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      a(i, j) = 15;
    }
  }
  a *= 2;
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      ASSERT_TRUE(a(i, j) == 30);
    }
  }
}

TEST(Test_16, SumNumOver) {
  S21Matrix a(10, 10);
  S21Matrix b(10, 10);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      a(i, j) = 15;
      b(i, j) = 15;
    }
  }
  a += b;
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      ASSERT_TRUE(a(i, j) == 30);
    }
  }
}

TEST(Test_17, SubNumOver) {
  S21Matrix a(10, 10);
  S21Matrix b(10, 10);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      a(i, j) = 15;
      b(i, j) = 14;
    }
  }
  a -= b;
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      ASSERT_TRUE(a(i, j) == 1);
    }
  }
}

TEST(Test_18, MulNumOver) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      a(i, j) = 15.6;
      b(i, j) = 2.6;
    }
  }
  S21Matrix c = b * a;
  for (int i = 0; i < b.GetRows(); i++) {
    for (int j = 0; j < b.GetCols(); j++) {
      ASSERT_TRUE(c(i, j) == 81.12);
    }
  }
}

TEST(Test_19, MulNumOver_2) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      a(i, j) = 15.6;
      b(i, j) = 2.6;
    }
  }
  b *= a;
  for (int i = 0; i < b.GetRows(); i++) {
    for (int j = 0; j < b.GetCols(); j++) {
      ASSERT_TRUE(b(i, j) == 81.12);
    }
  }
}

TEST(Test_20, EQExtra) {
  S21Matrix a(1, 2);
  S21Matrix b(2, 2);
  ASSERT_TRUE(a.EqMatrix(b) == 0);
}

TEST(Test_21, EQExtra_2) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      a(i, j) = rand() % 10;
      b(i, j) = rand() % 10 + 1;
    }
  }
  ASSERT_TRUE(a.EqMatrix(b) == 0);
}

TEST(Test_22, DeterminantExtra) {
  S21Matrix a(1, 1);
  a(0, 0) = 5;
  ASSERT_TRUE(a.Determinant() == 5);
  a.SetCols(5);
}

TEST(Test_23, CalcCompExtra) {
  S21Matrix a(1, 1);
  a(0, 0) = 5;
  S21Matrix b = a.CalcComplements();
  ASSERT_TRUE(b(0, 0) == 5);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}