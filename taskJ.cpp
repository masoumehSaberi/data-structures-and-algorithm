#include <bitset>
#include <iostream>
#include <vector>

void CheckPath(int n, std::vector<std::bitset<1000>>& adjacency_matrix) {
  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      if (adjacency_matrix[i][k]) {
        adjacency_matrix[i] |= adjacency_matrix[k];
      }
    }
  }
}

int main() {
  int n;
  std::cin >> n;
  std::vector<std::bitset<1000>> adjacency_matrix(n);
  for (int i = 0; i < n; i++) {
    std::string row;
    std::cin >> row;
    for (int j = 0; j < n; j++) {
      if (row[j] == '1') {
        adjacency_matrix[i][j] = 1;
      }
    }
  }
  CheckPath(n, adjacency_matrix);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      std::cout << adjacency_matrix[i][j];
    }
    std::cout << std::endl;
  }
  return 0;
}
