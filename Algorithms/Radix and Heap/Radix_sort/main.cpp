#include <iostream>

const uint16_t kMaxValueByte = 256;
const uint8_t kNumOfBytes = 8;

uint64_t GetValByte(uint64_t number, uint64_t byte_number) {
  return (number >> (kNumOfBytes * byte_number)) % kMaxValueByte;
}

void CountSort(uint64_t*& arr_in, uint8_t byte_number, uint32_t size) {
  uint64_t* arr_out = new uint64_t[size];
  uint32_t* counters = new uint32_t[kMaxValueByte];
  for (uint16_t i = 0; i < kMaxValueByte; i++) {
    counters[i] = 0;
  }
  for (uint32_t i = 0; i < size; i++) {
    counters[GetValByte(arr_in[i], byte_number)]++;
  }
  int32_t count = 0;
  for (uint16_t i = 0; i < kMaxValueByte; i++) {
    uint16_t temp = counters[i];
    counters[i] = count;
    count += temp;
  }
  for (uint32_t i = 0; i < size; i++) {
    arr_out[counters[GetValByte(arr_in[i], byte_number)]] = arr_in[i];
    counters[GetValByte(arr_in[i], byte_number)]++;
  }
  for (uint32_t i = 0; i < size; i++) {
    arr_in[i] = arr_out[i];
  }
  delete[] arr_out;
  delete[] counters;
}

void RadixSort(uint64_t*& array, uint32_t size) {
  for (uint8_t i = 0; i < kNumOfBytes; i++) {
    CountSort(array, i, size);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  uint32_t size;
  std::cin >> size;
  uint64_t* array = new uint64_t[size];
  for (uint32_t i = 0; i < size; i++) {
    std::cin >> array[i];
  }
  RadixSort(array, size);
  for (uint32_t i = 0; i < size; i++) {
    std::cout << array[i] << ' ';
  }
  delete[] array;
  return 0;
}
