#include <iostream>
#include <string>

struct Node {
  int64_t data;
  int64_t index_query;
};

class BinaryHeap {
 public:
  BinaryHeap()
      : array_(new Node[kMaxHeapSize]),
        pointers_(new int64_t[kMaxRequestSize]),
        size_(0) {}
  void Delete() {
    delete[] array_;
    delete[] pointers_;
  }
  void Insert(int64_t pos, int64_t number);
  int64_t GetMin();
  void ExtractMin();
  void DecreaseKey(int64_t request_index, int64_t delta);
  void SiftUp(int64_t index);
  static void NodeSwap(Node& first, Node& second);
  void SiftDown(int64_t index);

 private:
  const int64_t kMaxHeapSize = 100000;
  const int64_t kMaxRequestSize = 1000010;
  Node* array_;
  int64_t* pointers_;
  int64_t size_;
};

void BinaryHeap::NodeSwap(Node& first, Node& second) {
  Node temp = first;
  first = second;
  second = temp;
}

void BinaryHeap::SiftUp(int64_t index) {
  int64_t parent = (index - 1) / 2;
  if (-1 < parent && array_[index].data < array_[parent].data) {
    NodeSwap(array_[index], array_[parent]);
    std::swap(pointers_[array_[index].index_query],
              pointers_[array_[parent].index_query]);
    SiftUp(parent);
  }
}

void BinaryHeap::SiftDown(int64_t index) {
  int64_t right_son = 2 * index + 2;
  int64_t left_son = 2 * index + 1;
  int64_t min_node = index;
  if (left_son < size_ && array_[left_son].data < array_[index].data) {
    min_node = left_son;
  }
  if (right_son < size_ && array_[right_son].data < array_[left_son].data &&
      array_[index].data < array_[right_son].data) {
    min_node = right_son;
  }
  if (min_node != index) {
    NodeSwap(array_[index], array_[min_node]);
    std::swap(pointers_[array_[index].index_query],
              pointers_[array_[min_node].index_query]);
    SiftDown((min_node));
  }
}

void BinaryHeap::Insert(int64_t pos, int64_t number) {
  size_++;
  Node temp{};
  temp.data = number;
  temp.index_query = pos;
  NodeSwap(array_[size_ - 1], temp);
  pointers_[pos] = size_ - 1;
  SiftUp(size_ - 1);
}

int64_t BinaryHeap::GetMin() { return array_[0].data; }

void BinaryHeap::ExtractMin() {
  std::swap(pointers_[array_[0].index_query],
            pointers_[array_[size_ - 1].index_query]);
  array_[0] = array_[size_ - 1];
  SiftDown(0);
  size_--;
}

void BinaryHeap::DecreaseKey(int64_t request_index, int64_t delta) {
  array_[pointers_[request_index]].data -= delta;
  SiftUp(pointers_[request_index]);
}

void Distribution(BinaryHeap binary_heap, int64_t count) {
  std::string str;
  for (int64_t j = 1; j < count + 1; j++) {
    std::cin >> str;
    if (str == "insert") {
      int64_t number;
      std::cin >> number;
      binary_heap.Insert(j, number);
    } else if (str == "decreaseKey") {
      int64_t request_index;
      int64_t delta;
      std::cin >> request_index >> delta;
      binary_heap.DecreaseKey(request_index, delta);
    } else if (str == "getMin") {
      std::cout << binary_heap.GetMin() << '\n';
    } else if (str == "extractMin") {
      binary_heap.ExtractMin();
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  BinaryHeap heap_first;
  int64_t count;
  std::cin >> count;
  Distribution(heap_first, count);
  heap_first.Delete();
  return 0;
}
