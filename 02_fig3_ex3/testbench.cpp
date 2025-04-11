#include "kernel.hpp"
#include <stdio.h>

int data_in[N];

int main() {
  for (int i = 0; i < N; i++) {
    data_in[i] = i;
  }

  int sum = 0;
  kernel(&sum, data_in);
  printf("sum = %d\n", sum);
  return 0;
}
