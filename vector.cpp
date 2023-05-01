#include <iostream>
#include <sstream>
#include <string>

template <typename T>
class Vector {
 public:
  Vector();
  void Push(const T &element);
  T Pop();
  T AtI(size_t i);
  size_t Size() const;
  size_t Capacity() const;
  void Clear();
  void Exit();
  void Resize(size_t new_capacity);
  ~Vector();

 private:
  int n_;
  T *elements_ = nullptr;
  size_t capacity_ = 0;
  size_t size_ = 0;
};

template <typename T>
Vector<T>::Vector() {
  Resize(2);
}

template <typename T>
void Vector<T>::Push(const T &element) {
  if (size_ >= capacity_) {
    Resize(capacity_ * 2);
  }
  elements_[size_++] = element;
}

template <typename T>
T Vector<T>::Pop() {
  if (size_ > 0) {
    T temp = elements_[--size_];
    capacity_ = size_;
    Resize(capacity_);
    if (capacity_ == 0) {
      Resize(2);
    }
    return temp;
  } else {
    throw "error";
  }
}

template <typename T>
T Vector<T>::AtI(size_t i) {
  if (i < size_) {
    return elements_[i];
  }
  throw "error";
}

template <typename T>
void Vector<T>::Clear() {
  Resize(1);
  size_ = 0;
}

template <typename T>
void Vector<T>::Resize(size_t new_capacity) {
  T *new_memory = new T[new_capacity];
  for (size_t i = 0; i < size_; i++) {
    new_memory[i] = elements_[i];
  }
  delete[] elements_;
  elements_ = new_memory;
  capacity_ = new_capacity;
  if (capacity_ < size_) {
    size_ = capacity_;
  }
}

template <typename T>
size_t Vector<T>::Size() const {
  return size_;
}

template <typename T>
size_t Vector<T>::Capacity() const {
  return capacity_;
}

template <typename T>
void Vector<T>::Exit() {
  std::cout << "bye" << std::endl;
  std::exit(0);
}

template <typename T>
Vector<T>::~Vector() {
  delete[] elements_;
}

int main() {
  Vector<int> my_vector;
  std::string input, input1[2], word;

  while (1 == 1) {
    std::getline(std::cin, input);
    std::stringstream X(input);
    int i = 0;
    while (std::getline(X, word, ' ')) {
      input1[i++] = word;
    }
    int n = 0;
    for (int i = 0; i < input.size(); i++) {
      if (input[i] >= '0' && input[i] <= '9') {
        n *= 10;
        n += int(input[i]) - 48;
      }
    }
    if (input1[0] == "exit") {
      std::cout << "bye" << std::endl;
      break;
    } else if (input1[0] == "push") {
      my_vector.Push(n);
      std::cout << "ok" << std::endl;
    } else if (input1[0] == "pop") {
      try {
        std::cout << my_vector.Pop() << std::endl;
      } catch (char const *) {
        std::cout << "error" << std::endl;
      }
      continue;
    } else if (input1[0] == "at") {
      try {
        std::cout << my_vector.AtI(n) << std::endl;
      } catch (char const *) {
        std::cout << "error" << std::endl;
      }
      continue;
    } else if (input1[0] == "capacity") {
      std::cout << my_vector.Capacity() << std::endl;
    } else if (input1[0] == "clear") {
      my_vector.Clear();
      std::cout << "ok" << std::endl;
    } else if (input1[0] == "size") {
      std::cout << my_vector.Size() << std::endl;
    } else if (input1[0] == "resize") {
      my_vector.Resize(n);
      std::cout << "ok" << std::endl;
    } else {
      break;
    }
  }
  return 0;
}
