#include "kernel.hpp"
#include <stdio.h>

int data_in[N];

int main() {
  int expected = 0;
  for (int i = 0; i < N; i++) {
    data_in[i] = i;
    expected += i * 2;
  }

  int sum = 0;
  kernel(&sum, data_in);

  printf("Expected: %7d\n", expected);
  printf("  Actual: %7d\n", sum);

  // For Vitis HLS to execute C/RTL co-simulation, it requires that the C
  // testbench return exit code 0.
  return 0;
}
