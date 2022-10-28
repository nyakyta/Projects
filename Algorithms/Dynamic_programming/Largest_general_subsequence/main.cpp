#include <cmath>
#include <iostream>
#include <vector>

void CalculatePrint(std::vector<int16_t> first_seq,
                    std::vector<int16_t> second_seq,
                    std::vector<std::vector<int16_t>> largest_seq,
                    int16_t first_size, int16_t second_size) {
  for (int16_t first_it = 1; first_it <= first_size; ++first_it) {
    for (int16_t second_it = 1; second_it <= second_size; ++second_it) {
      if (first_seq[first_it] == second_seq[second_it]) {
        largest_seq[first_it][second_it] =
            largest_seq[first_it - 1][second_it - 1] + 1;
      } else {
        largest_seq[first_it][second_it] =
            std::max(largest_seq[first_it - 1][second_it],
                     largest_seq[first_it][second_it - 1]);
      }
    }
  }
  std::cout << largest_seq[first_size][second_size];
}

int main() {
  int16_t first_size;
  int16_t second_size;
  std::cin >> first_size;
  std::vector<int16_t> first_seq(first_size + 1);
  for (int16_t i = 1; i <= first_size; ++i) {
    std::cin >> first_seq[i];
  }
  std::cin >> second_size;
  std::vector<int16_t> second_seq(second_size + 1);
  for (int16_t i = 1; i <= second_size; ++i) {
    std::cin >> second_seq[i];
  }
  std::vector<std::vector<int16_t>> largest_seq(
      first_size + 1, std::vector<int16_t>(second_size + 1));
  for (int16_t first_it = 0; first_it <= first_size; ++first_it) {
    for (int16_t second_it = 0; second_it <= second_size; ++second_it) {
      largest_seq[first_it][second_it] = 0;
    }
  }
  CalculatePrint(first_seq, second_seq, largest_seq, first_size, second_size);
  return 0;
}
