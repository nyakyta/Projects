#include <iostream>
#include <string>

using std::cin;
using std::cout;

struct Node {
  int64_t val;
  int64_t h;
  Node* left;
  Node* right;
  explicit Node(int64_t value) : val(value), h(1), left(nullptr), right(nullptr) {}
  Node* LeftRot();
  Node* RightRot();
  Node* Balance();
  Node* DeleteMin();
};

int64_t GetHeight(Node* cur) {
  if (cur != nullptr) {
    return cur->h;
  }
  return 0;
}

Node* Node::LeftRot() {
  Node* save_right = right;
  right = save_right->left;
  save_right->left = this;
  if (GetHeight(left) > GetHeight(right)) {
    h = GetHeight(left) + 1;
  } else {
    h = GetHeight(right) + 1;
  }
  if (GetHeight(save_right->left) > GetHeight(save_right->right)) {
    save_right->h = GetHeight(save_right->left) + 1;
  } else {
    save_right->h = GetHeight(save_right->right) + 1;
  }
  return save_right;
}

Node* DeleteNode(Node*& cur, int64_t value) {
  if (cur == nullptr) {
    return cur;
  }
  if (value < cur->val) {
    cur->left = DeleteNode(cur->left, value);
    return cur->Balance();
  }
  if (value > cur->val) {
    cur->right = DeleteNode(cur->right, value);
    return cur->Balance();
  }
  Node* save_left = cur->left;
  Node* save_right = cur->right;
  delete cur;
  if (save_right == nullptr) {
    return save_left;
  }
  Node* node_min = save_right;
  while (node_min->left != nullptr) {
    node_min = node_min->left;
  }
  node_min->right = save_right->DeleteMin();
  node_min->left = save_left;
  return node_min->Balance();
}

Node* Node::RightRot() {
  Node* save_left = left;
  left = save_left->right;
  save_left->right = this;
  if (GetHeight(left) > GetHeight(right)) {
    h = GetHeight(left) + 1;
  } else {
    h = GetHeight(right) + 1;
  }
  if (GetHeight(save_left->left) > GetHeight(save_left->right)) {
    save_left->h = GetHeight(save_left->left) + 1;
  } else {
    save_left->h = GetHeight(save_left->right) + 1;
  }
  return save_left;
}

Node* Insert(Node*& cur, int64_t value) {
  if (cur == nullptr) {
    return new Node(value);
  }
  if (value < cur->val) {
    cur->left = Insert(cur->left, value);
  } else {
    cur->right = Insert(cur->right, value);
  }
  return cur->Balance();
}

Node* Node::DeleteMin() {
  if (left == nullptr) {
    return right;
  }
  left = left->DeleteMin();
  return Balance();
}

Node* Node::Balance() {
  if (GetHeight(left) > GetHeight(right)) {
    h = GetHeight(left) + 1;
  } else {
    h = GetHeight(right) + 1;
  }
  int64_t delta = GetHeight(right) - GetHeight(left);
  if (delta == 2) {
    if (GetHeight(right->right) - GetHeight(right->left) < 0) {
      right = right->RightRot();
    }
    return LeftRot();
  }
  if (delta == -2) {
    if (GetHeight(left->right) - GetHeight(left->left) > 0) {
      left = left->LeftRot();
    }
    return RightRot();
  }
  return this;
}

bool Exists(Node*& cur, int64_t value) {
  if (cur != nullptr) {
    if (cur->val == value) {
      return true;
    }
    if (cur->val < value && cur->right != nullptr) {
      return Exists(cur->right, value);
    }
    if (cur->val > value && cur->left != nullptr) {
      return Exists(cur->left, value);
    }
  }
  return false;
}

class AvlTree {
 public:
  AvlTree() : root_(nullptr) {}
  ~AvlTree() { Clear(root_); }
  void Insert(int64_t x);
  int64_t Prev(int64_t x);
  int64_t Next(int64_t x);
  bool Exists(int64_t x) { return ::Exists(root_, x); }
  void Delete(int64_t x) { root_ = DeleteNode(root_, x); }

 private:
  Node* root_;
  void Clear(Node*& cur) {
    if (cur != nullptr) {
      Clear(cur->left);
      Clear(cur->right);
      delete cur;
    }
  }
};

int64_t AvlTree::Next(int64_t x) {
  int64_t next = INT64_MIN;
  Node* save = root_;
  if (save != nullptr && save->val == x) {
    save = save->right;
  }
  while (save != nullptr) {
    if (save->val == x) {
      save = save->right;
      continue;
    }
    if (save->val < x) {
      save = save->right;
    } else if (save->val > x) {
      next = save->val;
      save = save->left;
    } else {
      next = save->val;
      break;
    }
  }
  return next;
}

int64_t AvlTree::Prev(int64_t x) {
  int64_t prev = INT64_MIN;
  Node* save = root_;
  if (save != nullptr && save->val == x) {
    save = save->left;
  }
  while (save != nullptr) {
    if (save->val == x) {
      save = save->left;
      continue;
    }
    if (save->val > x) {
      save = save->left;
    } else if (save->val < x) {
      prev = save->val;
      save = save->right;
    } else {
      prev = save->val;
      break;
    }
  }
  return prev;
}

void AvlTree::Insert(int64_t x) {
  if (root_ == nullptr) {
    root_ = new Node(x);
    return;
  }
  root_ = ::Insert(root_, x);
}

void OutPrevNext(int64_t x) {
  if (x == INT64_MIN) {
    cout << "none\n";
    return;
  }
  cout << x << '\n';
}

void Distribution(AvlTree& my_tree, std::string s, int64_t x) {
  if (s == "insert") {
    if (!my_tree.Exists(x)) {
      my_tree.Insert(x);
    }
  }
  if (s == "delete") {
    if (my_tree.Exists(x)) {
      my_tree.Delete(x);
    }
  }
  if (s == "exists") {
    if (my_tree.Exists(x)) {
      cout << "true\n";
    } else {
      cout << "false\n";
    }
  }
  if (s == "prev") {
    OutPrevNext(my_tree.Prev(x));
  }
  if (s == "next") {
    OutPrevNext(my_tree.Next(x));
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  AvlTree my_avl;
  std::string s;
  int64_t x;
  while (cin >> s >> x) {
    Distribution(my_avl, s, x);
  }
  return 0;
}
