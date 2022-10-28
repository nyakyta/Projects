#include <iostream>
#include <vector>

class Solver {
 public:
  explicit Solver(int32_t n) : sz_(n) {
    a_.resize(sz_);
    prefix_sum_even_.resize(sz_);
    fen_even_.resize(sz_);
    GetA();
    CreateFenEven();
  }
  ~Solver() = default;
  void Increase(uint32_t pos, int32_t value);
  int32_t GetSum(uint32_t left, uint32_t right);
  void Update(uint32_t pos, int32_t value);

 private:
  uint32_t sz_;
  std::vector<int32_t> a_;
  std::vector<int32_t> prefix_sum_even_;
  std::vector<int32_t> fen_even_;
  static uint32_t F(uint32_t i) { return i & (i + 1); }
  static uint32_t G(uint32_t i) { return i | (i + 1); }
  void GetA();
  void CreateFenEven();
  int32_t GetPrefixSum(uint32_t pos);
};

void Solver::Increase(uint32_t pos, int32_t value) {
  for (uint32_t i = pos; i < sz_; i = G(i)) {
    fen_even_[i] += value;
  }
}

int32_t Solver::GetPrefixSum(uint32_t pos) {
  int32_t ans = 0;
  for (int32_t i = pos; i >= 0; i = F(i) - 1) {
    ans += fen_even_[i];
  }
  return ans;
}

int32_t Solver::GetSum(uint32_t left, uint32_t right) {
  if (left > 0) {
    return GetPrefixSum(right) - GetPrefixSum(left - 1);
  }
  return GetPrefixSum(right);
}

void Solver::Update(uint32_t pos, int32_t value) {
  if (pos % 2 == 0) {
    Increase(pos, value - a_[pos]);
    a_[pos] = value;
  } else {
    Increase(pos, -value - a_[pos]);
    a_[pos] = -value;
  }
}

void Solver::GetA() {
  std::cin >> a_[0];
  prefix_sum_even_[0] = a_[0];
  for (uint32_t i = 1; i < sz_; i++) {
    std::cin >> a_[i];
    if (i % 2 != 0) {
      a_[i] = -a_[i];
    }
    prefix_sum_even_[i] = a_[i] + prefix_sum_even_[i - 1];
  }
}

void Solver::CreateFenEven() {
  for (uint32_t i = 0; i < sz_; i++) {
    if (F(i) >= 1) {
      fen_even_[i] =
          prefix_sum_even_[i] - int32_t(F(i) >= 1) * prefix_sum_even_[F(i) - 1];
      continue;
    }
    fen_even_[i] = prefix_sum_even_[i];
  }
}

int main() {
  std::cout << INT32_MAX;
  uint32_t n;
  std::cin >> n;
  Solver even_fen_tree(n);
  uint32_t m;
  std::cin >> m;
  for (uint32_t i = 0; i < m; i++) {
    uint32_t operation_num;
    uint32_t first_op;
    uint32_t second_op;
    std::cin >> operation_num >> first_op >> second_op;
    if (operation_num == 0) {
      even_fen_tree.Update(first_op - 1, second_op);
      continue;
    }
    if (first_op % 2 == 0) {
      std::cout << -even_fen_tree.GetSum(first_op - 1, second_op - 1) << '\n';
      continue;
    }
    std::cout << even_fen_tree.GetSum(first_op - 1, second_op - 1) << '\n';
  }
  return 0;
}
