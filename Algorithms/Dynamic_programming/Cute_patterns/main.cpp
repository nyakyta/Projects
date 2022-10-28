#include <cmath>
#include <iostream>
#include <vector>

bool Bit(int64_t mask, int64_t pos) { return bool((mask >> pos) & 1); }

void CalculateMatrix(int64_t m, std::vector<std::vector<bool>>& accept_trans) {
  for (int64_t cur = 0; cur < (1 << m); ++cur) {
    for (int64_t next = 0; next < (1 << m); ++next) {
      accept_trans[cur][next] = true;
      for (int64_t pos = 0; pos < m - 1; ++pos) {
        if ((Bit(cur, pos) && Bit(cur, pos + 1) && Bit(next, pos) &&
             Bit(next, pos + 1)) ||
            (!Bit(cur, pos) && !Bit(cur, pos + 1) && !Bit(next, pos) &&
             !Bit(next, pos + 1))) {
          accept_trans[cur][next] = false;
          break;
        }
      }
    }
  }
}

int main() {
  int64_t m;
  int64_t n;
  int64_t count = 0;
  std::cin >> m >> n;
  if (m < n) {
    std::swap(m, n);
  }
  std::vector<std::vector<bool>> accept_trans(1 << n,
                                              std::vector<bool>(1 << n));
  CalculateMatrix(n, accept_trans);
  std::vector<std::vector<int64_t>> count_patterns(
      m, std::vector<int64_t>(1 << n));
  for (int64_t i = 0; i < (1 << n); ++i) {
    count_patterns[0][i] = 1;
  }
  for (int64_t i = 1; i < m; ++i) {
    for (int64_t mask = 0; mask < (1 << n); ++mask) {
      for (int64_t new_mask = 0; new_mask < (1 << n); ++new_mask) {
        if (accept_trans[mask][new_mask]) {
          count_patterns[i][new_mask] += count_patterns[i - 1][mask];
        }
      }
    }
  }
  for (int64_t mask = 0; mask <= (1 << n); ++mask) {
    count += count_patterns[m - 1][mask];
  }
  std::cout << count;
  return 0;
}
