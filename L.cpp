#include <iostream>
#include <vector>

struct Node {
  int capacity, start, end, lazy;
};

bool Query(std::vector<Node>& s_tree, int index, int left, int right, int x) {
  if (s_tree[index].start > right || s_tree[index].end < left) {
    return true;
  }
  if (s_tree[index].start == s_tree[index].end) {
    s_tree[index].capacity -= s_tree[index].lazy;
    s_tree[index].lazy = 0;
    return (s_tree[index].capacity >= x);
  }
  if (s_tree[index].lazy != 0) {
    s_tree[index].capacity -=
        (s_tree[index].end - s_tree[index].start + 1) * s_tree[index].lazy;
    s_tree[index * 2 + 1].lazy += s_tree[index].lazy;
    s_tree[index * 2 + 2].lazy += s_tree[index].lazy;
    s_tree[index].lazy = 0;
  }
  return (Query(s_tree, 2 * index + 1, left, right, x) &&
          Query(s_tree, 2 * index + 2, left, right, x));
}

int Update(std::vector<Node>& s_tree, int index, int left, int right, int x) {
  if (s_tree[index].lazy != 0) {
    s_tree[index].capacity -=
        (s_tree[index].end - s_tree[index].start + 1) * s_tree[index].lazy;
    if (s_tree[index].end != s_tree[index].start) {
      s_tree[index * 2 + 1].lazy += s_tree[index].lazy;
      s_tree[index * 2 + 2].lazy += s_tree[index].lazy;
    }
    s_tree[index].lazy = 0;
  }
  if (s_tree[index].start > right || s_tree[index].end < left) {
    return s_tree[index].capacity;
  }
  if (s_tree[index].end <= right && s_tree[index].start >= left) {
    s_tree[index].capacity -= (s_tree[index].end - s_tree[index].start + 1) * x;
    if (s_tree[index].end != s_tree[index].start) {
      s_tree[index * 2 + 1].lazy += x;
      s_tree[index * 2 + 2].lazy += x;
    }
    return s_tree[index].capacity;
  }
  s_tree[index].capacity = Update(s_tree, index * 2 + 1, left, right, x) +
                           Update(s_tree, index * 2 + 2, left, right, x);
  return s_tree[index].capacity;
}

int SegmentTree(std::vector<Node>& s_tree, int capacity, int start, int end,
                int index, std::vector<int>& initial_arr) {
  s_tree[index].start = start;
  s_tree[index].end = end;
  s_tree[index].lazy = 0;
  if (start == end) {
    s_tree[index].capacity = capacity - initial_arr[start];
    return s_tree[index].capacity;
  }
  int mid = (start + end) / 2;
  s_tree[index].capacity =
      SegmentTree(s_tree, capacity, start, mid, index * 2 + 1, initial_arr) +
      SegmentTree(s_tree, capacity, mid + 1, end, index * 2 + 2, initial_arr);
  return s_tree[index].capacity;
}

int main() {
  int n, m, atmpts, left, right, x;
  std::cin >> n;
  std::vector<int> initial_arr(n);
  std::vector<Node> s_tree(4 * n);
  for (int i = 0; i < n; i++) {
    std::cin >> initial_arr[i];
  }
  std::cin >> m >> atmpts;
  SegmentTree(s_tree, m, 0, n - 1, 0, initial_arr);
  std::vector<int> result;
  for (int i = 0; i < atmpts; i++) {
    std::cin >> left >> right >> x;
    if (Query(s_tree, 0, left, right, x)) {
      Update(s_tree, 0, left, right, x);
    } else {
      result.push_back(i);
    }
  }
  for (int i = 0; i < result.size(); i++) {
    std::cout << result[i] << " ";
  }
  return 0;
}
