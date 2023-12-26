#include <iostream>


int main() {
  size_t n, f_n, f_one, f_two;
  f_one = 0;
  f_two = 1;
  f_n = 0;
  std::cin >> n;
  if (n == 2) {
    f_n = 1;
  }
  if (n > 2) {
    n = n % 2000008;
    for (int i = 3; i <= n; i++) {
      f_n = (f_one + f_two) % 1000003;
      f_one = f_two;
      f_two = f_n;
    }
  }
  std::cout << (f_n) << std::endl;
  return 0;
}
