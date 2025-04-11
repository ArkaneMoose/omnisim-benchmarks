#include "kernel.hpp"
#include <stdio.h>

#define DATA_SIZE 2025

int data[MAX_DATA_SIZE];

int main() {
  int expected = 0;
  for (int i = 0; i < MAX_DATA_SIZE; i++) {
    data[i] = (i < DATA_SIZE) ? (i + 1) * 3 : 0;
    expected += (i < DATA_SIZE) ? i + 1 : 0;
  }

  int sum_out = 0;
  int Dropped = 0;
  kernel(&sum_out, data, Dropped);

  printf("Expected: <%7d (timing-sensitive)\n", expected);
  printf("  Actual:  %7d\n", sum_out);
  printf(" Dropped:  %7d\n", Dropped);

  // For Vitis HLS to execute C/RTL co-simulation, it requires that the C
  // testbench return exit code 0.
  return 0;
}
