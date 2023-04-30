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
  ~Stack() { delete[] array_; }
};

Stack::Stack() {
  array_ = new int[2];
  top_ = -1;
}

void Stack::Push(int x) { array_[++top_] = x; }

int Stack::Pop() {
  if (top_ > -1) {
    return array_[top_--];
  } else {
    throw "error";
  }
}

int Stack::Back() {
  if (top_ > -1) {
    return array_[top_];
  } else {
    throw "error";
  }
}

int Stack::Size() {
  int stack_size = top_;
  return ++stack_size;
}

void Stack::Clear() {
  delete[] array_;
  array_ = new int[2];
  top_ = -1;
}

void Stack::Exit() {
  std::cout << "bye" << std::endl;
  std::exit(0);
}
int main() {
  Stack new_stack;
  std::string input, word, input1[10];

  while (1 == 1) {
    std::getline(std::cin, input);
    int i = 0;
    if (input != "") {
      std::stringstream X(input);
      while (std::getline(X, word, ' ')) {
        input1[i++] = word;
      }
    } else {
      input1[0] = '0';
    }

    int n = 0;
    for (int i = 0; i < input.size(); i++) {
      if (input[i] >= '0' && input[i] <= '9') {
        n *= 10;
        n += int(input[i]) - 48;
      }
    }
    for (int i = 0; i < input.size(); i++) {
      if (input[i] == '-') {
        n = n * (-1);
      }
    }
    if (input1[0] == "push" && input1[1] != "") {
      new_stack.Push(n);
      std::cout << "ok" << std::endl;
    } else if (input1[0] == "pop") {
      try {
        std::cout << new_stack.Pop() << std::endl;
      } catch (const char* error) {
        std::cout << error << std::endl;
      }
    } else if (input1[0] == "back") {
      try {
        std::cout << new_stack.Back() << std::endl;
      } catch (const char* error) {
        std::cout << error << std::endl;
      }
    } else if (input1[0] == "size") {
      std::cout << new_stack.Size() << std::endl;
    } else if (input1[0] == "clear") {
      new_stack.Clear();
      std::cout << "ok" << std::endl;
    } else if (input1[0] == "exit") {
      std::cout << "bye" << std::endl;
      std::exit(0);
    }
    for (int i = 0; i < 10; i++) input1[i] = "";
  }
  return 0;
}
