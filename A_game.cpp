#include <iostream>
#include <vector>
#include <deque>

int MinMoney(int max_num) {
  std::vector<std::vector<int>> vctr(max_num + 2,
                                     std::vector<int>(max_num + 2));
  for (int i = 2; i <= max_num; ++i) {
    int wrong_guess = i - 1;
    std::deque<std::pair<int, int>> que;
    for (int j = i - 1; j != 0; --j) {
      while (vctr[j][wrong_guess - 1] > vctr[wrong_guess + 1][i]) {
        if (!que.empty() && que.front().second == wrong_guess) {
          que.pop_front();
        }
        --wrong_guess;
      }
      int qmax_n = j + vctr[j + 1][i];
      while (!que.empty() && qmax_n < que.back().first) {
        que.pop_back();
      }
      que.emplace_back(qmax_n, j);
      vctr[j][i] =
          (vctr[j][wrong_guess] + wrong_guess + 1) < (que.front().first)
              ? (vctr[j][wrong_guess] + wrong_guess + 1)
              : (que.front().first);
    }
  }
  return vctr[1][max_num];
}

int main() {
  int dr_strange_num;
  std::cin >> dr_strange_num;
  std::cout << MinMoney(dr_strange_num) << std::endl;
  return 0;
}
