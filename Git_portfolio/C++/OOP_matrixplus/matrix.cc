#include "./s21_matrix_oop.h"
// делегирование второму конструктору
S21Matrix::S21Matrix() : S21Matrix(2, 2) {}

S21Matrix::S21Matrix(int rows, int cols) {
  if (rows <= 0 || cols <= 0) {
    throw std::logic_error("Matrix size must be greater or equal than 0");
  } else {
    rows_ = rows;
    cols_ = cols;
    matrix_ = new double* [rows] {};
    for (int i = 0; i < rows; i++) {
      matrix_[i] = new double[cols]{};
    }
  }
}
S21Matrix::S21Matrix(const S21Matrix& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = new double* [rows_] {};
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]{};
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix&& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = new double* [rows_] {};
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]{};
  }
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
  rows_ = 0;
  cols_ = 0;
}

S21Matrix& S21Matrix::operator=(S21Matrix other) {
  this->~S21Matrix();
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = new double* [rows_] {};
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]{};
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
  return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  this->SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  S21Matrix buf(*this);
  buf.SumMatrix(other);
  return buf;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  this->SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  S21Matrix buf(*this);
  buf.SubMatrix(other);
  return buf;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  this->MulMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  S21Matrix buf(*this);
  buf.MulMatrix(other);
  return buf;
}

S21Matrix& S21Matrix::operator*=(const double num) {
  this->MulNumber(num);
  return *this;
}

S21Matrix S21Matrix::operator*(const double num) const {
  S21Matrix buf(*this);
  buf.MulNumber(num);
  return buf;
}

bool S21Matrix::operator==(const S21Matrix& other) {
  bool res = this->EqMatrix(other);
  return res;
}

double& S21Matrix::operator()(int i, int j) {
  if (i >= rows_ || j >= cols_ || i < 0 || j < 0) {
    throw std::logic_error("Not in predels");
  } else {
    return matrix_[i][j];
  }
}

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  int result = true;
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    result = false;
  } else {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        if (round(matrix_[i][j] * pow(10, 7)) !=
            round(other.matrix_[i][j] * pow(10, 7))) {
          result = false;
        }
      }
    }
  }
  return result;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::logic_error("Matrices are different");
  } else {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        matrix_[i][j] += other.matrix_[i][j];
      }
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::logic_error("Matrices are different");
  } else {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        matrix_[i][j] -= other.matrix_[i][j];
      }
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::logic_error("Matrices are different");
  }
  S21Matrix buffer_mat(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int l = 0; l < cols_; l++) {
        buffer_mat.matrix_[i][j] += matrix_[i][l] * other.matrix_[l][j];
      }
    }
  }
  *this = buffer_mat;
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix buffer_mat(cols_, rows_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      buffer_mat.matrix_[j][i] = matrix_[i][j];
    }
  }
  return buffer_mat;
}

S21Matrix S21Matrix::s21_minor_matrix(int A_rows, int A_columns) {
  S21Matrix minor(rows_ - 1, cols_ - 1);
  int minor_rows = 0;
  int minor_columns = 0;
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (i != A_rows && j != A_columns) {
        minor.matrix_[minor_rows][minor_columns] = matrix_[i][j];
        ++minor_columns;
        if (minor_columns >= minor.cols_) {
          ++minor_rows;
          minor_columns = 0;
        }
      }
    }
  }
  return minor;
}

double S21Matrix::Determinant() {
  if (cols_ != rows_) {
    throw std::logic_error("Cols and rows are not equal");
  } else {
    double result = 0.0;
    result = this->s21_count_determinant();
    return result;
  }
}

double S21Matrix::s21_count_determinant() {
  double deter = 0.0;
  if (rows_ == 1) {
    deter = matrix_[0][0];
  } else {
    S21Matrix minor(rows_ - 1, cols_ - 1);
    for (int j = 0; j < cols_; ++j) {
      minor = this->s21_minor_matrix(0, j);
      if (j % 2) {
        deter -= matrix_[0][j] * minor.s21_count_determinant();
      } else {
        deter += matrix_[0][j] * minor.s21_count_determinant();
      }
    }
  }
  return deter;
}

S21Matrix S21Matrix::CalcComplements() {
  if (cols_ != rows_) {
    throw std::logic_error("Cols and rows are not equal");
  } else {
    S21Matrix result(rows_, cols_);
    if (rows_ == 1) {
      result.matrix_[0][0] = 1;
    } else {
      for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
          S21Matrix minor(rows_ - 1, cols_ - 1);
          minor = this->s21_minor_matrix(i, j);
          double determinant = 0;
          determinant = minor.Determinant();
          result.matrix_[i][j] = pow(-1, (i + j)) * determinant;
        }
      }
    }
    return result;
  }
}

S21Matrix S21Matrix::InverseMatrix() {
  S21Matrix result(rows_, cols_);
  double deter = 0.0;

  deter = this->Determinant();
  if (deter == 0.0) {
    throw std::logic_error("Determinant = 0");
  }
  if (rows_ == 1) {
    result.matrix_[0][0] = 1.0 / matrix_[0][0];
  } else {
    S21Matrix calc(result.rows_, result.cols_);
    calc = this->CalcComplements();
    S21Matrix trans(result.rows_, result.cols_);
    trans = calc.Transpose();
    trans.MulNumber(1 / deter);
    result = trans;
  }
  return result;
}

int S21Matrix::getrows() const { return rows_; }
int S21Matrix::getcols() const { return cols_; }

void S21Matrix::setrows(int rows) {
  S21Matrix buf(rows, cols_);
  int ro = rows;
  if (rows > rows_) {
    ro = rows_;
  }
  for (int i = 0; i < ro; i++) {
    for (int j = 0; j < cols_; j++) {
      buf.matrix_[i][j] = matrix_[i][j];
    }
  }
  *this = buf;
}

void S21Matrix::setcols(int cols) {
  S21Matrix buf(rows_, cols);
  int ro = cols;
  if (cols > cols_) {
    ro = cols_;
  };
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < ro; j++) {
      buf.matrix_[i][j] = matrix_[i][j];
    }
  }
  *this = buf;
}