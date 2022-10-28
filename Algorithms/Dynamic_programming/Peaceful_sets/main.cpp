#include <iostream>
#include <vector>
const int32_t kMaxSize = 2000;

using std::cin;
using std::cout;
using std::vector;

void Calculate(vector<vector<int32_t>>& piece_count, int32_t n) {
  for (auto first_it = 1; first_it <= n; ++first_it) {
    for (auto second_it = 1; second_it <= first_it; ++second_it) {
      if (piece_count[first_it][second_it] > 0) {
        for (auto k = 2 * second_it; first_it + k <= n; ++k) {
          piece_count[first_it + k][k] += piece_count[first_it][second_it];
        }
      }
    }
  }
}

void PrintAns(vector<vector<int32_t>> piece_count, int32_t n) {
  int32_t sum = 0;
  for (auto it = 1; it <= n; it++) {
    sum += piece_count[n][it];
  }
  cout << sum;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int32_t n;
  cin >> n;
  vector<vector<int32_t>> piece_count(kMaxSize + 1,
                                      vector<int32_t>(kMaxSize + 1));
  for (auto it = 1; it <= n; ++it) {
    piece_count[it][it] = 1;
  }
  Calculate(piece_count, n);
  PrintAns(piece_count, n);
  return 0;
}
