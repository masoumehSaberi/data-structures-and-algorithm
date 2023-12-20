#include <cmath>
#include <iostream>
#include <vector>

std::vector<std::vector<int>> SparseTable(std::vector<int>& arr, int n) {
  int logn = log2(n) + 1;
  std::vector<std::vector<int>> st(n, std::vector<int>(logn));
  for (int i = 0; i < n; i++) {
    st[i][0] = i;
  }

  for (int j = 1; (1 << j) <= n; j++) {
    for (int i = 0; (i + (1 << j) - 1) < n; i++) {
      if (arr[st[i][j - 1]] < arr[st[i + (1 << (j - 1))][j - 1]]) {
        st[i][j] = st[i][j - 1];
      } else {
        st[i][j] = st[i + (1 << (j - 1))][j - 1];
      }
    }
  }
  return st;
}

std::pair<int, int> Query(int l, int r, std::vector<int>& arr,
                          std::vector<std::vector<int>>& st) {
  int j = log2(r - l + 1);
  if (arr[st[l][j]] <= arr[st[r - (1 << j) + 1][j]]) {
    return std::make_pair(arr[st[l][j]], st[l][j]);
  } else {
    return std::make_pair(arr[st[r - (1 << j) + 1][j]],
                          st[r - (1 << j) + 1][j]);
  }
}

int Smin(int l, int r, std::vector<int>& arr,
         std::vector<std::vector<int>>& sparse_table) {
  std::pair<int, int> fmin = Query(l - 1, r - 1, arr, sparse_table);
  int min_index = fmin.second;
  if (r - l == 1) {
    return std::max(arr[l - 1], arr[r - 1]);
  }
  if (min_index == r - 1) {
    return Query(l - 1, min_index - 1, arr, sparse_table).first;
  }
  if (min_index == l - 1) {
    return Query(min_index + 1, r - 1, arr, sparse_table).first;
  }
  std::pair<int, int> a = Query(l - 1, min_index - 1, arr, sparse_table);
  std::pair<int, int> b = Query(min_index + 1, r - 1, arr, sparse_table);
  return std::min(a.first, b.first);
}

int main() {
  int n, m;
  std::cin >> n >> m;
  std::vector<int> arr(n);
  for (int i = 0; i < n; i++) {
    std::cin >> arr[i];
  }
  std::vector<std::vector<int>> sparse_table = SparseTable(arr, n);
  for (int i = 0; i < m; i++) {
    int l, r;
    std::cin >> l >> r;
    std::cout << Smin(l, r, arr, sparse_table) << std::endl;
  }
  return 0;
}
