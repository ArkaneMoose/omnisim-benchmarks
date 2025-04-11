#include "kernel.hpp"
#include <stdio.h>

#define DATA_SIZE 2025

int data[MAX_DATA_SIZE];

int main() {
  for (int i = 0; i < MAX_DATA_SIZE; i++) {
    data[i] = (i < DATA_SIZE) ? (i + 1) * 3 : 0;
  }

  int sum_out = 0;
  kernel(&sum_out, data);
  printf("sum_out = %d\n", sum_out);
  return 0;
}
