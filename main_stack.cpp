#include <iostream>
#include <sstream>
#include <string>

class Stack {
  int* array_;
  int capacity_;
  int top_;

 public:
  Stack();

  void Push(int x);
  int Pop();
  int Back();
  int Size();
  void Clear();
  void Exit();
  ~Stack();
};

Stack::Stack() {
  array_ = new int[2];
  top_ = -1;
  capacity_ = 2;
}

Stack::~Stack() { delete[] array_; }

void Stack::Push(int x) {
  if (++top_ >= capacity_) {
    capacity_ *= 2;
    int* new_memory = new int[capacity_];
    for (int i = 0; i < top_; i++) {
      new_memory[i] = array_[i];
    }
    delete[] array_;
    array_ = new_memory;
  }
  array_[top_] = x;
}

int Stack::Pop() {
  if (top_ > -1) {
    return array_[top_--];
  }
  throw "error";
}

int Stack::Back() {
  if (top_ > -1) {
    return array_[top_];
  }
  throw "error";
}

int Stack::Size() {
  int stack_size = top_;
  return ++stack_size;
}

void Stack::Clear() {
  delete[] array_;
  capacity_ = 2;
  array_ = new int[capacity_];
  top_ = -1;
}

void Stack::Exit() {
  std::cout << "bye" << std::endl;
  std::exit(0);
}

std::string Text(std::string str) {
  std::string word;
  std::string input_arr[10];
  int i = 0;
  if (!str.empty()) {
    std::stringstream x(str);
    while (std::getline(x, word, ' ')) {
      input_arr[i++] = word;
    }
  } else {
    input_arr[0] = "";
  }
  return input_arr[0];
}

int Number(std::string str) {
  std::string word;
  std::string input_arr[10];
  int i = 0;
  if (!str.empty()) {
    std::stringstream x(str);
    while (std::getline(x, word, ' ')) {
      input_arr[i++] = word;
    }
  } else {
    input_arr[0] = "";
  }
  if (!input_arr[1].empty()) {
    int n = 0;
    for (unsigned int i = 0; i < str.size(); i++) {
      if (str[i] >= '0' && str[i] <= '9') {
        n *= 10;
        n += int(str[i]) - 48;
      }
    }
    for (unsigned int i = 0; i < str.size(); i++) {
      if (str[i] == '-') {
        n = n * (-1);
      }
    }
    return n;
  }
  throw 0;
}

int main() {
  Stack new_stack;
  std::string input;
  while (1 == 1) {
    std::getline(std::cin, input);
    try {
      if (Text(input) == "back") {
        std::cout << new_stack.Back() << std::endl;
      } else if (Text(input) == "pop") {
        std::cout << new_stack.Pop() << std::endl;
      } else if (Text(input) == "push") {
        new_stack.Push(Number(input));
        std::cout << "ok" << std::endl;
      }
    } catch (const char* error) {
      std::cout << error << std::endl;
    } catch (...) {
      continue;
    }
    if (Text(input) == "size") {
      std::cout << new_stack.Size() << std::endl;
    } else if (Text(input) == "clear") {
      new_stack.Clear();
      std::cout << "ok" << std::endl;
    } else if (Text(input) == "exit") {
      new_stack.Exit();
    }
  }
  return 0;
}
