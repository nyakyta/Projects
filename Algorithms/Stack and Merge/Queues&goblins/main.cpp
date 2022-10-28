#include <deque>
#include <iostream>

void Privileges(std::deque<int>& first, std::deque<int>& second) {
  int goblin_number;
  std::cin >> goblin_number;
  int first_counter = first.size();
  int second_counter = second.size();
  while ((second_counter - first_counter > 0)) {
    first.push_back(second.front());
    first_counter++;
    second.pop_front();
    second_counter--;
  }
  second.push_front(goblin_number);
}

void Leave(std::deque<int>& first, std::deque<int>& second) {
  if (!first.empty()) {
    std::cout << first.front() << '\n';
    first.pop_front();
  } else {
    std::cout << second.front() << '\n';
    second.pop_front();
  }
}

void Coming(std::deque<int>& second) {
  int goblin_number;
  std::cin >> goblin_number;
  second.push_back(goblin_number);
}

void Print(std::deque<int>& first, std::deque<int>& second, char symbol) {
  if (symbol == '-') {
    Leave(first, second);
  }
  if (symbol == '+') {
    Coming(second);
  }
  if (symbol == '*') {
    Privileges(first, second);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::deque<int> que_first;
  std::deque<int> que_second;
  int size_of_queue;
  std::cin >> size_of_queue;
  for (int i = 0; i < size_of_queue; i++) {
    char symbol;
    std::cin >> symbol;
    Print(que_first, que_second, symbol);
  }
  return 0;
}
