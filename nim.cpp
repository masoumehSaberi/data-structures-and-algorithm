#include <iostream>
#include <vector>

const int sizeofgset = 10010;
const int sizeofset = 110;

int SG(std::vector<int> set, std::vector<int>& sg, int bead, int k) {
  if (sg[bead] != -1) {
    return sg[bead];
  };
  std::vector<bool> visit(110, 0);
  for (int i = 0; i < k; i++) {
    if (bead >= set[i]) {
      SG(set, sg, bead - set[i], k);
      visit[sg[bead - set[i]]] = 1;
    }
  }
  int e;
  for (int i = 0;; i++) {
    if (!visit[i]) {
      e = i;
      break;
    }
  }
  return sg[bead] = e;
}

std::string GameResult(std::vector<int> set, int set_size, int pos_num) {
  std::vector<int> sg(sizeofgset, -1);
  std::vector<bool> hash(sizeofgset);
  int heaps, beads, result = 0;
  std::string answer;
  for (int i = 0; i < pos_num; i++) {
    std::cin >> heaps;
    for (int j = 0; j < heaps; j++) {
      std::cin >> beads;
      result ^= SG(set, sg, beads, set_size);
    }
    if (result != 0) {
      answer += 'W';
    } else {
      answer += 'L';
    }
    result = 0;
    sg.resize(sizeofgset, -1);
  }
  return answer;
}

std::string Game() {
  std::vector<int> set(sizeofset);
  int set_size, pos_num;
  std::cin >> set_size;
  for (int i = 0; i < set_size; i++) {
    std::cin >> set[i];
  }
  std::cin >> pos_num;
  return GameResult(set, set_size, pos_num);
}

int main() {
  std::cout << Game() + '\n';
  return 0;
}
