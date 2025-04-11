#include "kernel.hpp"
#include <stdio.h>

data_t data[N];

int main() {
  for (int i = 0; i < N; i++) {
    data[i] = data_t(i + 1);
  }

  int total_cycles = 0;
  kernel(data, &total_cycles);

  printf("Internal timer counted %d cycles\n", total_cycles);
  return 0;
}
