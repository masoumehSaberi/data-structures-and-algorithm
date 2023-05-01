#include <iostream>
#include <sstream>
#include <string>

template <typename T>
class Vector {
 public:
  Vector();
  void Push(const T& element);
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
  T* elements_ = nullptr;
  size_t capacity_ = 0;
  size_t size_ = 0;
};

template <typename T>
Vector<T>::Vector() {
  Resize(2);
}

template <typename T>
void Vector<T>::Push(const T& element) {
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
    if (capacity_ == 0) {
      Resize(2);
    } else {
      Resize(capacity_);
    }
    return temp;
  }
  throw "error";
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
  delete[] elements_;
  capacity_ = 1;
  elements_ = new T[capacity_];
  size_ = 0;
}

template <typename T>
void Vector<T>::Resize(size_t new_capacity) {
  if (new_capacity == 0) {
    Clear();
  } else {
    T* new_memory = new T[new_capacity];
    size_t n = 0;
    if (size_ <= new_capacity) {
      n = size_;
    } else {
      n = new_capacity;
    }
    for (size_t i = 0; i < n; i++) {
      new_memory[i] = elements_[i];
    }
    delete[] elements_;
    elements_ = new_memory;
    capacity_ = new_capacity;
    if (capacity_ < size_) {
      size_ = capacity_;
    }
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

Vector<int> my_vector;

int Number(std::string str) {
  int n = 0;
  for (unsigned int i = 0; i < str.size(); i++) {
    if (str[i] >= '0' && str[i] <= '9') {
      n *= 10;
      n += str[i] - 48;
    }
  }
  return n;
}

std::string Text(std::string str) {
  std::string str_array[2];
  std::string word;
  std::stringstream x(str);
  int i = 0;
  while (std::getline(x, word, ' ')) {
    str_array[i++] = word;
  }
  return str_array[0];
}

void Output(std::string txt, int n) {
  if (txt == "push") {
    my_vector.Push(n);
    std::cout << "ok" << std::endl;
  } else if (txt == "pop") {
    try {
      std::cout << my_vector.Pop() << std::endl;
    } catch (char const*) {
      std::cout << "error" << std::endl;
    }
  } else if (txt == "at") {
    try {
      std::cout << my_vector.AtI(n) << std::endl;
    } catch (char const*) {
      std::cout << "error" << std::endl;
    }
  } else if (txt == "capacity") {
    std::cout << my_vector.Capacity() << std::endl;
  } else if (txt == "clear") {
    my_vector.Clear();
    std::cout << "ok" << std::endl;
  } else if (txt == "size") {
    std::cout << my_vector.Size() << std::endl;
  } else if (txt == "resize") {
    my_vector.Resize(n);
    std::cout << "ok" << std::endl;
  } else {
    std::cout << "error" << std::endl;
  }
}

int main() {
  std::string input;
  std::string text;
  int number;
  while (1 == 1) {
    std::getline(std::cin, input);
    text = Text(input);
    number = Number(input);
    if (text == "exit") {
      my_vector.Exit();
    }
    Output(text, number);
  }
  return 0;
}
