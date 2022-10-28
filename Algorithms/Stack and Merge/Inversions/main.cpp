#include <iostream>

void Merge(int64_t*& array, uint64_t left, uint64_t right, uint64_t arr_size,
           uint64_t& inverse_num) {
  uint64_t middle = (left + right) / 2;
  uint64_t left_part_counter = left;
  uint64_t right_part_counter = middle + 1;
  uint64_t combine_array_counter = left;
  int64_t* combine_array = new int64_t[arr_size];
  for (; left_part_counter <= middle && right_part_counter <= right;
       combine_array_counter++) {
    if (array[left_part_counter] > array[right_part_counter]) {
      combine_array[combine_array_counter] = array[right_part_counter];
      right_part_counter++;
      inverse_num += middle - left_part_counter + 1;
    } else {
      combine_array[combine_array_counter] = array[left_part_counter];
      left_part_counter++;
    }
  }
  for (; left_part_counter <= middle;
       combine_array_counter++, left_part_counter++) {
    combine_array[combine_array_counter] = array[left_part_counter];
  }
  for (; right_part_counter <= right;
       combine_array_counter++, right_part_counter++) {
    combine_array[combine_array_counter] = array[right_part_counter];
  }
  for (left_part_counter = left; left_part_counter < combine_array_counter;
       left_part_counter++) {
    array[left_part_counter] = combine_array[left_part_counter];
  }
  delete[] combine_array;
}

void MergeSort(int64_t*& array, uint64_t left, uint64_t right,
               uint64_t arr_size, uint64_t& inverse_num) {
  if (left >= right) {
    return;
  }
  uint64_t middle = (right + left) / 2;
  MergeSort(array, left, middle, arr_size, inverse_num);
  MergeSort(array, middle + 1, right, arr_size, inverse_num);
  Merge(array, left, right, arr_size, inverse_num);
}

int main() {
  uint64_t inverse_num = 0;
  uint64_t arr_size;
  std::cin >> arr_size;
  int64_t* array = new int64_t[arr_size];
  for (uint64_t i = 0; i < arr_size; i++) {
    std::cin >> array[i];
  }
  MergeSort(array, 0, arr_size - 1, arr_size, inverse_num);
  std::cout << inverse_num;
  delete[] array;
  return 0;
}
