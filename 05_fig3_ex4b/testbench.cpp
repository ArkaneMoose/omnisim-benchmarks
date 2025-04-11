#include "kernel.hpp"
#include <stdio.h>

int data[N];

int main() {
  for (int i = 0; i < N; i++) {
    data[i] = (i + 1) * 3;
  }

  int sum_out = 0;
  int Dropped = 0;
  kernel(&sum_out, data, Dropped);
  printf("sum_out = %d\n", sum_out);
  printf("Dropped = %d\n", Dropped);
  return 0;
}
