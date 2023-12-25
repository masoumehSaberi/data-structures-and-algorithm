#include <bitset>
#include <iostream>
#include <vector>

class Matrix {
  std::vector<std::bitset<1000>> adjacency_matrix_;
  int dimension_;

 public:
  Matrix(int n) {
    dimension_ = n;
    adjacency_matrix_.resize(dimension_);
  }
  void FillMatrix() {
    for (int i = 0; i < dimension_; i++) {
      std::string row;
      std::cin >> row;
      for (int j = 0; j < dimension_; j++) {
        if (row[j] == '1') {
          adjacency_matrix_[i][j] = 1;
        }
      }
    }
  }
  std::bitset<1000>& operator[](int row) { return adjacency_matrix_[row]; }
  int GetDimension() { return dimension_; }
};

void CheckPath(Matrix& matrix) {
  for (int k = 0; k < matrix.GetDimension(); k++) {
    for (int i = 0; i < matrix.GetDimension(); i++) {
      if (matrix[i][k]) {
        matrix[i] |= matrix[k];
      }
    }
  }
}

int main() {
  int n;
  std::cin >> n;
  Matrix matrix(n);
  matrix.FillMatrix();
  CheckPath(matrix);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      std::cout << matrix[i][j];
    }
    std::cout << std::endl;
  }
  return 0;
}
