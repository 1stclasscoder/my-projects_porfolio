#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

void fillMatrix(const double* arr, S21Matrix& M) {
  int n = 0;
  for (int i = 0; i < M.getrows(); i++) {
    for (int j = 0; j < M.getcols(); j++) {
      M(i, j) = arr[n++];
    }
  }
}

TEST(CalcComplements, 1) {
  S21Matrix matrix1{2, 2};
  EXPECT_EQ(matrix1.getcols(), 2);
  EXPECT_EQ(matrix1.getrows(), 2);

  S21Matrix result_check{2, 2};
  EXPECT_EQ(result_check.getcols(), 2);
  EXPECT_EQ(result_check.getrows(), 2);

  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;

  result_check(0, 0) = 4;
  result_check(0, 1) = -3;
  result_check(1, 0) = -2;
  result_check(1, 1) = 1;

  S21Matrix matrix_before = matrix1;
  S21Matrix result = matrix1.CalcComplements();

  EXPECT_TRUE(result == result_check);
  EXPECT_TRUE(matrix1 == matrix_before);
}

TEST(CalcComplements, 2) {
  S21Matrix M1(1, 1);
  double a[] = {7.05735};
  fillMatrix(a, M1);

  S21Matrix R = M1.CalcComplements();
  ASSERT_EQ(1, R(0, 0) == 1);
}

TEST(CalcComplements, 3) {
  S21Matrix M1(3, 3);
  double a[] = {1, 2, 3, 0, 4, 2, 5, 2, 1};
  fillMatrix(a, M1);

  S21Matrix M2(3, 3);
  double b[] = {0, 10, -20, 4, -14, 8, -8, -2, 4};
  fillMatrix(b, M2);
  S21Matrix R = M1.CalcComplements();

  ASSERT_EQ(1, R.EqMatrix(M2));
}

TEST(CalcComplements, 4) {
  S21Matrix M1(2, 3);
  double a[] = {1, 1, 1, 1, 1, 1};
  fillMatrix(a, M1);

  try {
    S21Matrix R = M1.CalcComplements();
  } catch (const std::logic_error& e) {
    std::string error = e.what();
    ASSERT_EQ("Cols and rows are not equal", error);
  }
}
TEST(trans, 1) {
  S21Matrix matrix1{1, 4};
  EXPECT_EQ(matrix1.getrows(), 1);
  EXPECT_EQ(matrix1.getcols(), 4);

  S21Matrix result_check{4, 1};
  EXPECT_EQ(result_check.getrows(), 4);
  EXPECT_EQ(result_check.getcols(), 1);

  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(0, 2) = 3;
  matrix1(0, 3) = 4;

  result_check(0, 0) = 1;
  result_check(1, 0) = 2;
  result_check(2, 0) = 3;
  result_check(3, 0) = 4;

  S21Matrix matrix_before = matrix1;
  S21Matrix result = matrix1.Transpose();

  EXPECT_TRUE(result == result_check);
  EXPECT_TRUE(matrix1 == matrix_before);
}

TEST(trans, 2) {
  S21Matrix M1(3, 3);
  double a[] = {1, 2, 3, 7, 5, 6, 1, 1, 1};
  fillMatrix(a, M1);

  S21Matrix M2(3, 3);
  double b[] = {1, 7, 1, 2, 5, 1, 3, 6, 1};
  fillMatrix(b, M2);

  S21Matrix R = M1.Transpose();
  ASSERT_EQ(1, R.EqMatrix(M2));
}

TEST(trans, 3) {
  S21Matrix M1(2, 3);
  double a[] = {1, 2, 3, 7, 5, 6};
  fillMatrix(a, M1);

  S21Matrix M2(3, 2);
  double b[] = {1, 7, 2, 5, 3, 6};
  fillMatrix(b, M2);

  S21Matrix R = M1.Transpose();
  ASSERT_EQ(1, R.EqMatrix(M2));
}

TEST(sub, 1) {
  S21Matrix matrix1{3, 2};
  S21Matrix matrix2{2, 2};

  S21Matrix matrix1_before = matrix1;
  S21Matrix matrix2_before = matrix2;

  EXPECT_ANY_THROW(matrix1 - matrix2);
  EXPECT_ANY_THROW(matrix2 - matrix1);
  EXPECT_TRUE(matrix1 == matrix1_before);
  EXPECT_TRUE(matrix2 == matrix2_before);
}

TEST(sub, 2) {
  S21Matrix M1(3, 3);
  double a[] = {1, 2, 3, 7.632, 5, 6, -1, 1, 1.000001};
  fillMatrix(a, M1);

  S21Matrix M2(3, 3);
  double b[] = {1, 2, 3, 7, 7, 6, 1, 1, 1};
  fillMatrix(b, M2);

  S21Matrix R(3, 3);
  double c[] = {0, 0, 0, 0.632, -2, 0, -2, 0, 0.000001};
  fillMatrix(c, R);

  M1.SubMatrix(M2);
  ASSERT_EQ(1, M1.EqMatrix(R));
}

TEST(sub, 3) {
  S21Matrix M1(2, 3);
  double a[] = {1, 2, 3, 7, 5, 6};
  fillMatrix(a, M1);

  S21Matrix M2(3, 3);
  double b[] = {1, 2, 3, 7, 7, 6, 1, 1, 1};
  fillMatrix(b, M2);

  try {
    M1.SubMatrix(M2);
  } catch (const std::logic_error& e) {
    std::string error = e.what();
    ASSERT_EQ("Matrices are different", error);
  }
}

TEST(sub, 4) {
  S21Matrix M1(3, 3);
  double a[] = {1, 2, 3, 7.632, 5, 6, -1, 1, 1.000001};
  fillMatrix(a, M1);

  S21Matrix M2(3, 3);
  double b[] = {1, 2, 3, 7, 7, 6, 1, 1, 1};
  fillMatrix(b, M2);

  S21Matrix R(3, 3);
  double c[] = {0, 0, 0, 0.632, -2, 0, -2, 0, 0.000001};
  fillMatrix(c, R);

  M1 -= M2;
  ASSERT_EQ(1, M1.EqMatrix(R));
}

TEST(sum, 1) {
  S21Matrix matrix1{2, 2};
  S21Matrix matrix2{3, 2};

  S21Matrix matrix1_before = matrix1;
  S21Matrix matrix2_before = matrix2;

  EXPECT_ANY_THROW(matrix1 += matrix2);
  EXPECT_ANY_THROW(matrix2 += matrix1);
  EXPECT_TRUE(matrix1 == matrix1_before);
  EXPECT_TRUE(matrix2 == matrix2_before);
}

TEST(sum, 2) {
  S21Matrix M1(2, 3);
  double a[] = {1, 2, 3, 7, 5, 6};
  fillMatrix(a, M1);

  S21Matrix M2(3, 3);
  double b[] = {1, 2, 3, 7, 7, 6, 1, 1, 1};
  fillMatrix(b, M2);

  try {
    M1.SumMatrix(M2);
  } catch (const std::logic_error& e) {
    std::string error = e.what();
    ASSERT_EQ("Matrices are different", error);
  }
}

TEST(sum, 3) {
  S21Matrix M1(3, 3);
  double a[] = {1, 2, 3, 7, 5, 6, 1, 1, 1};
  fillMatrix(a, M1);

  S21Matrix M2(3, 3);
  double b[] = {1, 2, 3, 7, 7, 6, 1, 1, 1};
  fillMatrix(b, M2);

  S21Matrix R(3, 3);
  double c[] = {2, 4, 6, 14, 12, 12, 2, 2, 2};
  fillMatrix(c, R);

  M1 += M2;
  ASSERT_EQ(1, M1.EqMatrix(R));
}

TEST(sum, 4) {
  S21Matrix M1(3, 3);
  double a[] = {1, 2, 3, 7, 5, 6, 1, 1, 1};
  fillMatrix(a, M1);

  S21Matrix M2(3, 3);
  double b[] = {1, 2, 3, 7, 7, 6, 1, 1, 1};
  fillMatrix(b, M2);

  S21Matrix M3(3, 3);
  double c[] = {2, 4, 6, 14, 12, 12, 2, 2, 2};
  fillMatrix(c, M3);

  S21Matrix R = M1 + M2;
  ASSERT_EQ(1, M3.EqMatrix(R));
}

TEST(mult_n, 1) {
  S21Matrix M1(3, 3);
  double a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  fillMatrix(a, M1);

  double num = 8.90001;
  S21Matrix R(3, 3);
  double c[] = {8.90001,  17.80002, 26.70003, 35.60004, 44.50005,
                53.40006, 62.30007, 71.20008, 80.10009};
  fillMatrix(c, R);

  M1.MulNumber(num);
  ASSERT_EQ(1, R.EqMatrix(M1));
}

TEST(mult_n, 2) {
  S21Matrix M1(3, 3);
  double a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  fillMatrix(a, M1);

  double num = 8.90001;
  S21Matrix R(3, 3);
  double c[] = {8.90001,  17.80002, 26.70003, 35.60004, 44.50005,
                53.40006, 62.30007, 71.20008, 80.10009};
  fillMatrix(c, R);

  M1 *= num;
  ASSERT_EQ(1, R.EqMatrix(M1));
}

TEST(mult_n, 3) {
  S21Matrix M1(3, 3);
  double a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  fillMatrix(a, M1);

  double num = 8.90001;
  S21Matrix R(3, 3);
  double c[] = {8.90001,  17.80002, 26.70003, 35.60004, 44.50005,
                53.40006, 62.30007, 71.20008, 80.10009};
  fillMatrix(c, R);

  S21Matrix M3 = M1 * num;
  ASSERT_EQ(1, R == M3);
}

TEST(mult_m, 1) {
  S21Matrix matrix1{3, 2};
  S21Matrix matrix2{3, 2};

  S21Matrix matrix1_before = matrix1;
  S21Matrix matrix2_before = matrix2;

  EXPECT_ANY_THROW(matrix1.MulMatrix(matrix2));
  EXPECT_ANY_THROW(matrix2.MulMatrix(matrix1));
  EXPECT_TRUE(matrix1 == matrix1_before);
  EXPECT_TRUE(matrix2 == matrix2_before);
}

TEST(mult_m, 2) {
  S21Matrix M1(3, 3);
  double a[] = {1, 2, 3, -44, 5, 6, -7.548, 8, 9.000001};
  fillMatrix(a, M1);

  S21Matrix M2(3, 3);
  double b[] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
  fillMatrix(b, M2);

  S21Matrix R(3, 3);
  double c[] = {6, 6, 6, -33, -33, -33, 9.452001, 9.452001, 9.452001};
  fillMatrix(c, R);
  M1.MulMatrix(M2);
  ASSERT_EQ(1, R.EqMatrix(M1));
}

TEST(mult_m, 3) {
  S21Matrix M1(3, 3);
  double a[] = {1, 2, 3, -44, 5, 6, -7.548, 8, 9.000001};
  fillMatrix(a, M1);

  S21Matrix M2(1, 1);
  double b[] = {1, 1};
  fillMatrix(b, M2);

  try {
    M1.MulMatrix(M2);
  } catch (const std::logic_error& e) {
    std::string error = e.what();
    ASSERT_EQ("Matrices are different", error);
  }
}

TEST(mult_m, 4) {
  S21Matrix M1(3, 3);
  double a[] = {1, 2, 3, -44, 5, 6, -7.548, 8, 9.000001};
  fillMatrix(a, M1);

  S21Matrix M2(3, 3);
  double b[] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
  fillMatrix(b, M2);

  S21Matrix R(3, 3);
  double c[] = {6, 6, 6, -33, -33, -33, 9.452001, 9.452001, 9.452001};
  fillMatrix(c, R);

  M1 *= M2;
  ASSERT_EQ(1, R.EqMatrix(M1));
}

TEST(mult_m, 5) {
  S21Matrix M1(3, 3);
  double a[] = {1, 2, 3, -44, 5, 6, -7.548, 8, 9.000001};
  fillMatrix(a, M1);

  S21Matrix M2(3, 3);
  double b[] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
  fillMatrix(b, M2);

  S21Matrix M3(3, 3);
  double c[] = {6, 6, 6, -33, -33, -33, 9.452001, 9.452001, 9.452001};
  fillMatrix(c, M3);

  S21Matrix R(3, 3);
  double r[] = {6, 6, 6, -33, -33, -33, 9.452001, 9.452001, 9.452001};
  fillMatrix(r, R);

  R = M1 * M2;
  ASSERT_EQ(1, R.EqMatrix(M3));
}

TEST(inverse, 1) {
  S21Matrix M1(1, 1);
  double a[] = {42.12849};
  fillMatrix(a, M1);

  S21Matrix M2(1, 1);
  double b[] = {1 / 42.12849};
  fillMatrix(b, M2);

  S21Matrix R = M1.InverseMatrix();
  ASSERT_EQ(1, R.EqMatrix(M2));
}

TEST(inverse, 2) {
  S21Matrix M1(3, 3);
  double a[] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
  fillMatrix(a, M1);
  try {
    S21Matrix R = M1.InverseMatrix();
  } catch (const std::logic_error& e) {
    std::string error = e.what();
    ASSERT_EQ("Determinant = 0", error);
  }
}

TEST(inverse, 3) {
  S21Matrix M1(3, 3);
  double a[] = {2, 5, 7, 6, 3, 4, 5, -2, -3};
  fillMatrix(a, M1);

  S21Matrix M2(3, 3);
  double b[] = {1, -1, 1, -38, 41, -34, 27, -29, 24};
  fillMatrix(b, M2);

  S21Matrix R = M1.InverseMatrix();
  ASSERT_EQ(1, R.EqMatrix(M2));
}

TEST(deter, 1) {
  S21Matrix M1(3, 3);
  double a[] = {1, 2, 3, -44, 5, 6, -7.548, 8, 9.000001};
  fillMatrix(a, M1);
  ASSERT_NEAR(M1.Determinant(), -244.355907, 0.0000001);
}

TEST(deter, 2) {
  S21Matrix M1(2, 3);
  double a[] = {1, 1, 1, 1, 1, 1};
  fillMatrix(a, M1);

  try {
    M1.Determinant();
  } catch (const std::logic_error& e) {
    std::string error = e.what();
    ASSERT_EQ("Cols and rows are not equal", error);
  }
}

TEST(equal, 1) {
  S21Matrix M1(2, 3);
  double a[] = {4, 5, -6.6135, 7.000004, -8, 9};
  fillMatrix(a, M1);

  S21Matrix M2(2, 3);
  double b[] = {4, 5, -6.6135, 7.000004, -8, 9};
  fillMatrix(b, M2);

  ASSERT_EQ(1, M1 == M2);
}

TEST(equal, 2) {
  S21Matrix M1(2, 3);
  double a[] = {4, 5, -6, 7, -8, 9};
  fillMatrix(a, M1);

  S21Matrix M2(2, 3);
  double b[] = {4, 5, -6.6135, 7.000004, -8, 9};
  fillMatrix(b, M2);

  ASSERT_EQ(0, M1 == M2);
}

TEST(equal, 3) {
  S21Matrix M1(2, 3);
  double a[] = {4, 5, 6, 7, 8, 9};
  fillMatrix(a, M1);

  S21Matrix M2(3, 3);
  double b[] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
  fillMatrix(b, M2);

  ASSERT_EQ(0, M1 == M2);
}
TEST(CONSTRUCTORS, default) { S21Matrix M1; }

TEST(index, 1) {
  S21Matrix M(3, 3);
  double a[] = {1.8934, -3, 55, -10.0003, 5, 6, 7, 8, 9};
  fillMatrix(a, M);

  ASSERT_EQ(1, M(0, 0) == 1.8934);
  ASSERT_EQ(1, M(0, 1) == -3);
  ASSERT_EQ(1, M(0, 2) == 55);
}

TEST(index, 2) {
  S21Matrix M(3, 3);
  double a[] = {1.8934, 2, -33, -4.000005, 5, 6, 7, 8, 9};
  fillMatrix(a, M);

  M(0, 0) = 45;
  M(0, 1) = 2.6834;
  M(0, 2) = -892;
  M(1, 0) = -4.543;

  ASSERT_EQ(1, M(0, 0) == 45);
  ASSERT_EQ(1, M(0, 1) == 2.6834);
  ASSERT_EQ(1, M(0, 2) == -892);
  ASSERT_EQ(1, M(1, 0) == -4.543);
}

TEST(index, 3) {
  S21Matrix M1(3, 3);
  double a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  fillMatrix(a, M1);

  try {
    M1(-1, 5);
  } catch (const std::logic_error& e) {
    std::string error = e.what();
    ASSERT_EQ("Not in predels", error);
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
