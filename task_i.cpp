#include <iostream>

class Hash {
 private:
  bool* arr_;
  int capacity_;

 public:
  Hash() {
    capacity_ = 1000;
    arr_ = new bool[capacity_];
    for (int i = 0; i < capacity_; i++) {
      arr_[i] = false;
    }
  }
  void ReallocateMemory(int j) {
    bool* new_memory = new bool[j * 2];
    for (int i = 0; i < capacity_; i++) {
      new_memory[i] = arr_[i];
    }
    for (int i = capacity_; i < j * 2; i++) {
      new_memory[i] = false;
    }
    capacity_ = j * 2;
    delete[] arr_;
    arr_ = new_memory;
  }
  void InsertI(int i) {
    if (i >= capacity_) {
      ReallocateMemory(i);
    }
    arr_[i] = true;
  }
  void DeleteI(int i) {
    if (i < capacity_) {
      arr_[i] = false;
    }
  }
  bool Check(int i) { return (i < capacity_ && arr_[i]); }
  int Capacity() { return capacity_; }
  ~Hash() { delete[] arr_; }
};

int main() {
  Hash hash;
  int n;
  int i;
  std::string input;
  std::cin >> n;
  for (int j = 0; j < n; j++) {
    std::cin >> input;
    if (input == "+") {
      std::cin >> i;
      hash.InsertI(i);
    } else if (input == "-") {
      std::cin >> i;
      hash.DeleteI(i);
    } else if (input == "?") {
      std::cin >> i;
      if (hash.Check(i)) {
        std::cout << "YES" << std::endl;
      } else {
        std::cout << "NO" << std::endl;
      }
    }
  }
}
