#include <iostream>

struct Node {
  char value;
  Node* next;
  Node(char value) {
    this->value = value;
    next = nullptr;
  }
};

class List {
  Node* node_;

 public:
  List() { node_ = nullptr; }
  void InputData(char data);
  Node* ReverseList();
  void OutputList();
  ~List() { delete[] node_; }
};

Node* List::ReverseList() {
  Node* head = node_;
  Node* temp1 = nullptr;
  Node* temp2 = nullptr;

  while (head != nullptr) {
    temp1 = head->next;
    head->next = temp2;
    temp2 = head;
    head = temp1;
  }
  node_ = temp2;
}

void List::InputData(char data) {
  Node* temp = new Node(data);
  temp->next = node_;
  node_ = temp;
}

void List::OutputList() {
  struct Node* temp = node_;
  while (temp != nullptr) {
    std::cout << temp->value;
    temp = temp->next;
  }
}

int main() {
  List linked_list;
  std::string char_sequence;
  std::cout << "Sequence of characters: ";
  std::getline(std::cin, char_sequence);
  for (int i = 0; i < char_sequence.size(); i++)
    linked_list.InputData(char_sequence[i]);
  linked_list.OutputList();
  std::cout << "\n";
  linked_list.ReverseList();
  linked_list.OutputList();
  return 0;
}
