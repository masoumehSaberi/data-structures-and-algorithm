#include <cstdint>
#include <iostream>
#include <vector>

const int modulo = 1000003;

std::vector<std::vector<uint64_t>> Multiply(
    std::vector<std::vector<uint64_t>> matrix_a,
    std::vector<std::vector<uint64_t>> matrix_b) {
  std::vector<std::vector<uint64_t>> result(2, std::vector<uint64_t>(2));

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      for (int x = 0; x < 2; x++) {
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
  if (n == 1) return 0;
  if (n == 2) return 1;

  uint64_t fibo[2] = {};
  fibo[0] = 0;
  fibo[1] = 1;

  std::vector<std::vector<uint64_t>> matrix(2, std::vector<uint64_t>(2));
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      if (i == 0 || i == (j + 1)) {
        matrix[i][j] = 1;
      } else {
        matrix[i][j] = 0;
      }
    }
  }

  matrix = Pow(matrix, n - 2);
  uint64_t sum = 0;
  for (int i = 0; i < 2; i++) {
    sum = (sum + (matrix[0][i] % modulo) * fibo[1 - i]) % modulo;
  }
  return sum;
}

int main() {
  size_t n;
  std::cin >> n;
  std::cout << Compute(n) << std::endl;
  return 0;
}
