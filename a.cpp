#include <cstdint>
#include <iostream>
#include <vector>

std::vector<std::vector<uint64_t>> Multiply(
    std::vector<std::vector<uint64_t>> a,
    std::vector<std::vector<uint64_t>> b) {
  std::vector<std::vector<uint64_t>> c(2, std::vector<uint64_t>(2));

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      for (int x = 0; x < 2; x++) {
        c[i][j] =
            (c[i][j] + (a[i][x] % 1000003) * (b[x][j] % 1000003)) % 1000003;
      }
    }
  }

  return c;
}

std::vector<std::vector<uint64_t>> Pow(std::vector<std::vector<uint64_t>> t,
                                       size_t n) {
  if (n == 1) {
    return t;
  }

  if (n % 2) {
    return Multiply(t, Pow(t, n - 1));
  } else {
    std::vector<std::vector<uint64_t>> x = Pow(t, n / 2);
    return Multiply(x, x);
  }
}

uint64_t Compute(size_t n) {
  if (n == 1) return 0;
  if (n == 2) return 1;

  uint64_t f[2] = {};
  f[0] = 0;
  f[1] = 1;

  std::vector<std::vector<uint64_t>> t(2, std::vector<uint64_t>(2));
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      if (i == 0 || i == (j + 1)) {
        t[i][j] = 1;
      } else {
        t[i][j] = 0;
      }
    }
  }

  t = Pow(t, n - 2);
  uint64_t sum = 0;
  for (int i = 0; i < 2; i++) {
    sum = (sum + (t[0][i] % 1000003) * f[1 - i]) % 1000003;
  }
  return sum;
}
int main() {
  size_t n;
  std::cin >> n;
  std::cout << Compute(n) << std::endl;
  return 0;
}
