#include <iostream>

template <class T>
class Deque {
  T* arr_;
  int front_;
  int rear_;
  int capacity_;
  int size_;

 public:
  Deque() {
    front_ = -1;
    rear_ = 0;
    capacity_ = 2;
    size_ = 0;
    arr_ = new T[2];
  }

  Deque(int capacity) {
    front_ = -1;
    rear_ = 0;
    capacity_ = capacity;
    size_ = 0;
    arr_ = new T[capacity_];
  }
  void PushFront(T key);
  void PushBack(T key);
  void PopFront();
  void PopBack();
  bool IsFull();
  bool IsEmpty();
  T Front();
  T Back();
  void Resize();
  int Size() { return size_; }
  void Clear();
  ~Deque() { delete[] arr_; }
};

template <class T>
bool Deque<T>::IsFull() {
  return ((front_ == 0 && rear_ == capacity_ - 1) || front_ == rear_ + 1);
}

template <class T>
bool Deque<T>::IsEmpty() {
  return (front_ == -1);
}

template <class T>
void Deque<T>::Resize() {
  T* new_memory = new T[capacity_ * 8];
  for (int i = 0; i < capacity_; i++) {
    new_memory[i] = arr_[i];
  }
  delete[] arr_;
  arr_ = new_memory;
  capacity_ *= 8;
}

template <class T>
void Deque<T>::PushFront(T key) {
  if (IsFull()) {
    Resize();
  }
  if (front_ == -1) {
    front_ = 0;
    rear_ = 0;
  } else if (front_ == 0) {
    front_ = capacity_ - 1;
  } else {
    front_ = front_ - 1;
  }
  arr_[front_] = key;
  size_++;
}

template <class T>
void Deque<T>::PushBack(T key) {
  if (IsFull()) {
    Resize();
  }
  if (front_ == -1) {
    front_ = 0;
    rear_ = 0;
  } else if (rear_ == capacity_ - 1) {
    Resize();
    rear_++;
  } else {
    rear_ = rear_ + 1;
  }
  arr_[rear_] = key;
  size_++;
}

template <class T>
void Deque<T>::PopFront() {
  if (IsEmpty()) {
    throw "Queue Underflow";
  }

  if (front_ == rear_) {
    front_ = -1;
    rear_ = 0;
  } else {
    if (front_ == capacity_ - 1) {
      front_ = 0;
    } else {
      front_ = front_ + 1;
    }
  }
  size_--;
}

template <class T>
void Deque<T>::PopBack() {
  if (IsEmpty()) {
    throw " Underflow";
  }
  if (front_ == rear_) {
    front_ = -1;
    rear_ = -1;
  } else if (rear_ == 0) {
    rear_ = capacity_ - 1;
  } else {
    rear_ = rear_ - 1;
  }
  size_--;
}

template <class T>
T Deque<T>::Front() {
  if (IsEmpty()) {
    throw " Underflow";
  }
  return arr_[front_];
}

template <class T>
T Deque<T>::Back() {
  if (IsEmpty() || rear_ < 0) {
    throw " Underflow";
  }
  return arr_[rear_];
}

template <class T>
void Deque<T>::Clear() {
  delete[] arr_;
  front_ = -1;
  rear_ = 0;
  capacity_ = 2;
  size_ = 0;
  arr_ = new int[2];
}

template <class T>
class Hat {
 private:
  Deque<T> que_;
  Deque<T> deque_;
  int size_;

 public:
  Hat() { size_ = 0; }
  void Enqueue(int element) {
    if (que_.Size() == 0) {
      que_.PushBack(element);
      deque_.PushBack(element);
    } else {
      que_.PushBack(element);

      while (!deque_.IsEmpty() && deque_.Back() > element) {
        deque_.PopBack();
      }
      deque_.PushBack(element);
    }
    size_++;
  }

  T Dequeue() {
    if (que_.IsEmpty()) {
      throw "error";
    }
    T temp = que_.Front();
    if (que_.Front() == deque_.Front()) {
      que_.PopFront();
      deque_.PopFront();
    } else {
      que_.PopFront();
    }
    size_--;
    return temp;
  }

  T Min() { return deque_.Front(); }

  int Size() { return size_; }
  T Front() { return que_.Front(); }
  void Clear() {
    que_.Clear();
    deque_.Clear();
    size_ = 0;
  }
};

using std::cout;

int main() {
  Hat<int> hat;
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
      } else if (input[0] == 'm') {
        cout << hat.Min() << std::endl;
      } else if (input[0] == 's') {
        cout << hat.Size() << std::endl;
      } else if (input[0] == 'f') {
        cout << hat.Front() << std::endl;
      } else if (input[0] == 'c') {
        hat.Clear();
        cout << "ok" << std::endl;
      }
    } catch (const char*) {
      cout << "error" << std::endl;
    }
  }
  return 0;
}
