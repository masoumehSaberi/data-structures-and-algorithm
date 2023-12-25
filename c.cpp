#include <iostream>
#include <set>
#include <stack>
#include <vector>

template <typename T>
class Matrix {
  std::vector<std::vector<T>> matrix_;
  int dimension_;

 public:
  Matrix(int n) {
    dimension_ = n;
    matrix_.resize(dimension_);
  }
  std::vector<T>& operator[](int row) { return matrix_[row]; }
};

struct MaxStack {
  std::stack<int> s;
  int max_element = 0;
  int index = 0;
  int max_index = 0;
  int GetMax() const {
    if (s.empty())
      throw "error";
    else
      return max_element;
  }
  void Pop() {
    if (s.empty()) {
      throw "error";
    }
    int t = s.top();
    s.pop();
    index--;
    if (t > max_element) {
      int temp = max_element;
      max_element = 2 * max_element - t;
      max_index = index;
    }
  }
  void Push(int x) {
    if (s.empty()) {
      max_element = x;
      s.push(x);
      return;
    }
    index++;
    if (x > max_element) {
      s.push(2 * x - max_element);
      max_element = x;
      max_index = index;

    } else
      s.push(x);
  }
  int GetMaxIndex() const { return max_index; }
};

std::set<int> FriendZone(int n, Matrix<bool>& adj_matrix,
                         std::vector<int>& one_index, int index) {
  std::set<int> answer;
  int a, b;
  bool friend_a = true, friend_b = true;
  answer.insert(index);
  for (int i = 0; i < n; i++) {
    a = one_index[i];
    if (a != 0) {
      for (int j = i - 1; j < n; j++) {
        b = one_index[j];
        if (adj_matrix[a][b] != 0) {
          for (auto k = answer.begin(); k != answer.end(); ++k) {
            if (adj_matrix[b][*k] == 0) {
              friend_b = false;
            }
          }
          if (friend_b) {
            answer.insert(b);
          }
          friend_b = true;
        } else {
          friend_a = false;
        }
        if (friend_a) {
          answer.insert(a);
        }
      }
      friend_a = true;
    }
  }
  return answer;
}

std::set<int> MaxFZone(int n, Matrix<bool>& adj_matrix, Matrix<int>& one_index,
                       MaxStack& max_stack) {
  int index = max_stack.GetMaxIndex();
  std::set<int> fzone = FriendZone(n, adj_matrix, one_index[index], index),
                fzone1;

  for (int i = 0; i < n; i++) {
    max_stack.Pop();
    if (index != max_stack.GetMaxIndex()) {
      index = max_stack.GetMaxIndex();
      fzone1 = FriendZone(n, adj_matrix, one_index[index], index);
      fzone = (fzone.size() >= fzone1.size()) ? fzone : fzone1;
    }
  }
  return fzone;
}

int main() {
  int n, count_one = 0, temp;
  MaxStack max_stack;
  std::cin >> n;
  Matrix<bool> adj_matrix(n);
  Matrix<int> one_index(n);
  for (int i = 0; i < n; i++) {
    one_index[i].resize(n, 0);
    for (int j = 0; j < n; j++) {
      std::cin >> temp;
      adj_matrix[i].push_back(temp);
      if (temp == 1) {
        count_one++;
        one_index[i][j] = j;
      }
    }
    max_stack.Push(count_one);
    count_one = 0;
  }
  std::set<int> fzone = MaxFZone(n, adj_matrix, one_index, max_stack);
  for (auto i = fzone.begin(); i != fzone.end(); ++i) {
    std::cout << *i << ' ';
  }
  return 0;
}
