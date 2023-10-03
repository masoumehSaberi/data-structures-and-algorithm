#include <iostream>
#include <vector>
using namespace std;

vector<vector<unsigned long long>> multiply(
    vector<vector<unsigned long long>> A,
    vector<vector<unsigned long long>> B) {
  vector<vector<unsigned long long>> C(5, vector<unsigned long long>(5));

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      for (int x = 0; x < 5; x++) {
        C[i][j] =
            (C[i][j] + (A[i][x] % 1000003) * (B[x][j] % 1000003)) % 1000003;
      }
    }
  }

  return C;
}

vector<vector<unsigned long long>> pow(vector<vector<unsigned long long>> t,
                                       size_t n) {
  if (n == 1) {
    return t;
  }

  if (n % 2) {
    return multiply(t, pow(t, n - 1));
  } else {
    vector<vector<unsigned long long>> X = pow(t, n / 2);
    return multiply(X, X);
  }
}

unsigned long long compute(size_t n) {
  if (n == 1) return 1;
  if (n == 2) return 1;
  if (n == 3) return 2;
  if (n == 4) return 4;
  if (n == 5) return 8;

  unsigned long long f[5] = {};
  f[0] = 1;
  f[1] = 1;
  f[2] = 2;
  f[3] = 4;
  f[4] = 8;

  vector<vector<unsigned long long>> t(5, vector<unsigned long long>(5));
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      if (i == 0 || i == (j + 1)) {
        t[i][j] = 1;
      } else {
        t[i][j] = 0;
      }
    }
  }

  t = pow(t, n - 5);
  unsigned long long sum = 0;
  for (int i = 0; i < 5; i++) {
    sum = (sum + (t[0][i] % 1000003) * f[4 - i]) % 1000003;
  }
  return sum;
}
int main() {
  size_t n;
  std::cin >> n;
  cout << compute(n) << endl;

  return 0;
}
