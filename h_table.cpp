#include <iostream>

struct Hash {
  bool* arr;
  int capacity;
  Hash() {
    capacity = 1000;
    arr = new bool[capacity];
    for (int i = 0; i < capacity; i++) {
      arr[i] = false;
    }
  }
  void ReallocateMemory(int j) {
    bool* new_memory = new bool[j * 2];
    for (int i = 0; i < capacity; i++) {
      new_memory[i] = arr[i];
    }
    for (int i = capacity; i < j * 2; i++) {
      new_memory[i] = false;
    }
    capacity = j * 2;
    delete[] arr;
    arr = new_memory;
  }
  ~Hash() { delete[] arr; }
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
      if (i >= hash.capacity) {
        hash.ReallocateMemory(i);
      }
      hash.arr[i] = true;
    } else if (input == "-") {
      std::cin >> i;
      if (i < hash.capacity) {
        hash.arr[i] = false;
      }
    } else if (input == "?") {
      std::cin >> i;
      if (i < hash.capacity && hash.arr[i]) {
        std::cout << "YES" << std::endl;
      } else {
        std::cout << "NO" << std::endl;
      }
    }
  }
}
