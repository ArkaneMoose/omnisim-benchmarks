#include "kernel.hpp"
#include <stdio.h>

int ins[N];

int main() {
  for (int i = 0; i < N; i++) {
    ins[i] = (i + 1) * 3;
  }

  int processed_by_P1 = 0;
  int processed_by_P2 = 0;
  int sum_out_P1 = 0;
  int sum_out_P2 = 0;
  kernel(ins, processed_by_P1, processed_by_P2, &sum_out_P1, &sum_out_P2);
  printf("processed_by_P1 = %d\n", processed_by_P1);
  printf("processed_by_P2 = %d\n", processed_by_P2);
  printf("sum_out_P1 = %d\n", sum_out_P1);
  printf("sum_out_P2 = %d\n", sum_out_P2);
  return 0;
}
