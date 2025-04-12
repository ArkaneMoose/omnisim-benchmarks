#include "kernel.hpp"
#include <stdio.h>

int instr_in[N];

int main() {
  for (int i = 0; i < N; i++) {
    instr_in[i] = (i % 20 == 0) ? i + 25 : 0;
  }

  int fetched = 0;
  int executed = 0;
  kernel(instr_in, fetched, executed);
  printf("fetched = %d\n", fetched);
  printf("executed = %d\n", executed);
  return 0;
}
