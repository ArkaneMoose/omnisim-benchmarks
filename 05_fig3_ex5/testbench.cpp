#include "kernel.hpp"
#include <stdio.h>

int ins[N];

int main() {
  int expected = 0;
  for (int i = 0; i < N; i++) {
    ins[i] = (i + 1) * 3;
    expected += i + 1;
  }

  int processed_by_P1 = 0;
  int processed_by_P2 = 0;
  int sum_out_P1 = 0;
  int sum_out_P2 = 0;
  kernel(ins, processed_by_P1, processed_by_P2, &sum_out_P1, &sum_out_P2);

  printf("Expected: <%7d (timing-sensitive)\n", expected);
  printf("  P1 out:  %7d (processed %4d)\n", sum_out_P1, processed_by_P1);
  printf("  P2 out:  %7d (processed %4d)\n", sum_out_P2, processed_by_P2);

  // For Vitis HLS to execute C/RTL co-simulation, it requires that the C
  // testbench return exit code 0.
  return 0;
}
