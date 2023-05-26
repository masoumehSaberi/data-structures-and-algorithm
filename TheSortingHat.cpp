#include <iostream>

using std::cout;

class Hat {
  int* queue_;
  int size_;
  int capacity_;
  int minimum_;

 public:
  Hat();
  void Enqueue(int input);
  int Dequeue();
  int Front();
  int Size();
  void Clear();
  int Min();
  ~Hat();
};

Hat::Hat() {
  capacity_ = 2;
  size_ = 0;
  queue_ = new int[capacity_];
  minimum_ = 2147483647;
}

Hat::~Hat() { delete[] queue_; }

void Hat::Enqueue(int input) {
  if (size_ == 0) {
    minimum_ = 2147483647;
  }
  if (size_ + 1 >= capacity_) {
    capacity_ *= 16;
    int* new_memory = new int[capacity_];
    for (int i = 0; i < size_; i++) {
      new_memory[i] = queue_[i];
    }
    delete[] queue_;
    queue_ = new_memory;
  }
  queue_[size_] = input;
  if (input < minimum_) {
    minimum_ = input;
  }
  size_++;
}

int Hat::Dequeue() {
  if (size_ == 0) {
    throw "error";
  }
  size_--;
  int temp = queue_[0];
  if (temp != minimum_) {
    for (int i = 0; i < size_; i++) {
      queue_[i] = queue_[i + 1];
    }
    return temp;
  }
  minimum_ = queue_[size_];
  for (int i = 0; i < size_; i++) {
    queue_[i] = queue_[i + 1];
    if (queue_[i] < minimum_) {
      minimum_ = queue_[i];
    }
  }
  return temp;
}

int Hat::Front() {
  if (size_ == 0) {
    throw "error";
  }
  return queue_[0];
}

int Hat::Size() { return size_; }

void Hat::Clear() {
  delete[] queue_;
  capacity_ = 2;
  size_ = 0;
  queue_ = new int[capacity_];
  minimum_ = 2147483647;
}

int Hat::Min() {
  if (size_ == 0) {
    throw "error";
  }
  return minimum_;
}

int main() {
  Hat hat;
  std::string input;
  int n, number;
  std::cin >> n;
  for (int i = 0; i < n; i++) {
    std::cin >> input;
    try {
      if (input[0] == 'e') {
        std::cin >> number;
        hat.Enqueue(std::move(number));
        cout << "ok" << std::endl;
      } else if (input[0] == 'd') {
        cout << hat.Dequeue() << std::endl;
      } else if (input[0] == 'f') {
        cout << hat.Front() << std::endl;
      } else if (input[0] == 'm') {
        cout << hat.Min() << std::endl;
      } else if (input[0] == 's') {
        cout << hat.Size() << std::endl;
      } else if (input[0] == 'c') {
        hat.Clear();
        cout << "ok" << std::endl;
      }
    } catch (const char* error) {
      cout << "error" << std::endl;
    }
  }
  return 0;
}
