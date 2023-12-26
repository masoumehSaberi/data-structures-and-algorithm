#include <cstdint>
#include <iostream>
#include <vector>

const int modulo = 1000003;

std::vector<std::vector<uint64_t>> Multiply(
    std::vector<std::vector<uint64_t>> matrix_a,
    std::vector<std::vector<uint64_t>> matrix_b) {
  std::vector<std::vector<uint64_t>> result(5, std::vector<uint64_t>(5));
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      for (int x = 0; x < 5; x++) {
        result[i][j] = (result[i][j] +
                        (matrix_a[i][x] % modulo) * (matrix_b[x][j] % modulo)) %
                       modulo;
      }
    }
  }
  return result;
}

std::vector<std::vector<uint64_t>> Pow(
    std::vector<std::vector<uint64_t>> matrix, size_t n) {
  if (n == 1) {
    return matrix;
  }

  if (n % 2) {
    return Multiply(matrix, Pow(matrix, n - 1));
  } else {
    std::vector<std::vector<uint64_t>> x = Pow(matrix, n / 2);
    return Multiply(x, x);
  }
}

uint64_t Compute(size_t n) {
  if (n == 1) return 1;
  if (n == 2) return 1;
  if (n == 3) return 2;
  if (n == 4) return 4;
  if (n == 5) return 8;
  uint64_t ways[5] = {};
  ways[0] = 1;
  ways[1] = 1;
  ways[2] = 2;
  ways[3] = 4;
  ways[4] = 8;
  std::vector<std::vector<uint64_t>> matrix(5, std::vector<uint64_t>(5));
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      if (i == 0 || i == (j + 1)) {
        matrix[i][j] = 1;
      } else {
        matrix[i][j] = 0;
      }
    }
  }
  matrix = Pow(matrix, n - 5);
  uint64_t sum = 0;
  for (int i = 0; i < 5; i++) {
    sum = (sum + (matrix[0][i] % 1000003) * ways[4 - i]) % 1000003;
  }
  return sum;
}

int main() {
  size_t n;
  std::cin >> n;
  std::cout << Compute(n) << std::endl;
  return 0;
}
