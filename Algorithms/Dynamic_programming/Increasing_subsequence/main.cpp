#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;

int32_t CountingLen(std::vector<int32_t>& seq,
                    std::vector<int32_t>& last_seq_index,
                    std::vector<int32_t>& prev_pos,
                    std::vector<int32_t>& low_com_seq, int32_t count) {
  int32_t len;
  for (int32_t it = 0; it < count; ++it) {
    int32_t pos =
        std::upper_bound(low_com_seq.begin(), low_com_seq.end(), seq[it]) -
        low_com_seq.begin();
    if (low_com_seq[pos - 1] <= seq[it] && seq[it] <= low_com_seq[pos]) {
      low_com_seq[pos] = seq[it];
      prev_pos[it] = last_seq_index[pos - 1];
      last_seq_index[pos] = it;
      len = std::max(pos, len);
    }
  }
  return len;
}

int main() {
  int32_t count;
  int32_t max_len;
  cin >> count;
  std::vector<int32_t> seq(count + 1);
  std::vector<int32_t> last_seq_index(count + 1);
  std::vector<int32_t> prev_pos(count + 1);
  std::vector<int32_t> low_com_seq(count + 1, INT32_MAX);
  low_com_seq[0] = INT32_MIN;
  last_seq_index[0] = INT32_MIN;
  for (int32_t it = count - 1; it >= 0; --it) {
    cin >> seq[it];
  }
  max_len = CountingLen(seq, last_seq_index, prev_pos, low_com_seq, count);
  cout << max_len << '\n';
  std::vector<int32_t> subseq(max_len + 1);
  for (int32_t first_it = last_seq_index[max_len]; first_it >= 0;
       first_it = prev_pos[first_it]) {
    cout << count - first_it << ' ';
  }
}
