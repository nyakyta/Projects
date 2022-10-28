#include <iostream>

struct MyStack {
  int val;
  MyStack* prev;
};

void MyPush(MyStack*& head, int data) {
  MyStack* new_cell = new MyStack;
  new_cell->val = data;
  new_cell->prev = head;
  head = new_cell;
}

void MyPop(MyStack*& head) {
  MyStack* temp = head;
  head = head->prev;
  delete temp;
}

int GetBackVal(MyStack* head) { return head->val; }

int GetSize(MyStack* head) {
  int stack_size = 0;
  for (; head != nullptr; stack_size++) {
    head = head->prev;
  }
  return stack_size;
}

void MyClear(MyStack*& head) {
  if (head == nullptr) {
    return;
  }
  MyStack* temp;
  while (head != nullptr) {
    temp = head;
    head = head->prev;
    delete temp;
  }
}

void Output(std::string s, MyStack*& head) {
  if (s == "pop") {
    if (head == nullptr) {
      std::cout << "error\n";
    } else {
      std::cout << head->val << '\n';
      MyPop(head);
    }
  }
  if (s == "back") {
    if (head == nullptr) {
      std::cout << "error\n";
    } else {
      std::cout << GetBackVal(head) << '\n';
    }
  }
  if (s == "size") {
    std::cout << GetSize(head) << '\n';
  }
  if (s == "clear") {
    MyClear(head);
    std::cout << "ok\n";
  }
}

int main() {
  MyStack* my_head = nullptr;
  std::string s;
  while (s != "exit") {
    std::cin >> s;
    if (s == "push") {
      int n;
      std::cin >> n;
      MyPush(my_head, n);
      std::cout << "ok\n";
    } else {
      Output(s, my_head);
    }
  }
  MyClear(my_head);
  std::cout << "bye\n";
  return 0;
}
