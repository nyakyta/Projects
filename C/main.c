#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

bool Check(int n, const long long int* mas) {
  bool t = true;
  for (int i = 0; i < n - 1; i++)
    if (mas[i] > mas[i + 1]) t = false;
  return t;
}

void GetAns(bool result, long long int p, long long s) {
  printf("Сработала сортировка?\n");
  if (result) {
    printf("Да.\n");
  } else {
    printf("Нет.\n");
  }
  printf("Количество перемещений: %lld\n", p);
  printf("Количество сравнений: %lld\n", s);
}

void BubbleSort(int n, long long int* mas) {
  long long int p = 0, s = 0;
  for (int i = 0; i < n - 1; ++i) {
    for (int j = 0; j < n - i - 1; ++j) {
      s++;
      if (mas[j] > mas[j + 1]) {
        p++;
        mas[j] += mas[j + 1];
        mas[j + 1] = mas[j] - mas[j + 1];
        mas[j] -= mas[j + 1];
      }
    }
  }
  GetAns(Check(n, mas), p, s);
}

void ShellSort(int n, long long int* mas) {
  long long int temp, j;
  long long int p = 0, s = 0;
  for (int h = n / 2; h > 0; h /= 2) {
    for (int i = h; i < n; ++i){
      temp = mas[i];
      for (j = i; j >= h; j -= h) {
        s++;
        if (temp < mas[j - h]) {
          mas[j] = mas[j - h];
          p++;
        }
        else break;
      }
      mas[j] = temp;
    }
  }
  GetAns(Check(n, mas), p, s);
}
long long int* Generate(int n, short v) {
  int i;
  long long int* mas = (long long int *) malloc(n * sizeof(long long int));
  switch (v) {
    case 1:
      i = 0;
      while (i != n) {
        mas[i] = i + 1;
        ++i;
      }
      return mas;
    case 2:
      i = 0;
      while (i != n) {
        mas[i] = n - i;
        ++i;
      }
      return mas;
    default:
      i = 0;
      while (i != n) {
        mas[i] = (rand() * rand() * rand() * rand() * rand() - rand() * rand() * rand() * rand() * rand()) % (RAND_MAX + 1);
        ++i;
      }
      return mas;
  }
}

int main(void) {
  srand(time(NULL));
  int i = 0, N = 10000;
  long long int* arr = Generate(N , 4);
  long long int* arr_1 = (long long int *) malloc(N * sizeof(long long int)), *arr_2 = (long long int *) malloc(N * sizeof(long long int));
  while (i != N) {
    arr_1[i] = arr[i];
    arr_2[i] = arr[i];
    ++i;
  }
  printf("Запустим сортировку методом Шелла\n");
  ShellSort(N, arr_1);
  printf("Запустим сортировку методом \"пузырька\"\n");
  BubbleSort(N, arr_2);
  return 0;
}