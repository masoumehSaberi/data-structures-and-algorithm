#include <iostream>
#include <vector>
#include <cstdint>

std::vector<std::vector<uint64_t>> Multiply(
    std::vector<std::vector<uint64_t>> a,
    std::vector<std::vector<uint64_t>> b) {
  std::vector<std::vector<uint64_t>> c(5, std::vector<uint64_t>(5));

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      for (int x = 0; x < 5; x++) {
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
  if (n == 1) return 1;
  if (n == 2) return 1;
  if (n == 3) return 2;
  if (n == 4) return 4;
  if (n == 5) return 8;

  uint64_t f[5] = {};
  f[0] = 1;
  f[1] = 1;
  f[2] = 2;
  f[3] = 4;
  f[4] = 8;

  std::vector<std::vector<uint64_t>> t(5, std::vector<uint64_t>(5));
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      if (i == 0 || i == (j + 1)) {
        t[i][j] = 1;
      } else {
        t[i][j] = 0;
      }
    }
  }

  t = Pow(t, n - 5);
  uint64_t sum = 0;
  for (int i = 0; i < 5; i++) {
    sum = (sum + (t[0][i] % 1000003) * f[4 - i]) % 1000003;
  }
  return sum;
}
int main() {
  size_t n;
  std::cin >> n;
  std::cout << Compute(n) << std::endl;
  return 0;
}
