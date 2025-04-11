#include "kernel.hpp"
#include <stdio.h>

int data[N];

int main() {
  for (int i = 0; i < N; i++) {
    data[i] = (i + 1) * 3;
  }

  int sum_out = 0;
  kernel(&sum_out, data);
  printf("sum_out = %d\n", sum_out);
  return 0;
}
