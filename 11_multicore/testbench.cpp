#include "kernel.hpp"
#include <stdio.h>

int instr_in1[N];
int instr_in2[N];
int instr_in3[N];
int instr_in4[N];
int instr_in5[N];
int instr_in6[N];
int instr_in7[N];
int instr_in8[N];
int instr_in9[N];
int instr_in10[N];
int instr_in11[N];
int instr_in12[N];
int instr_in13[N];
int instr_in14[N];
int instr_in15[N];
int instr_in16[N];

int main() {
  for (int i = 0; i < N; i++) {
    instr_in1[i] = (i % 20 == 0) ? i + 25 : 0;
    instr_in2[i] = (i % 21 == 0) ? i + 26 : 0;
    instr_in3[i] = (i % 22 == 0) ? i + 27 : 0;
    instr_in4[i] = (i % 23 == 0) ? i + 28 : 0;
    instr_in5[i] = (i % 24 == 0) ? i + 29 : 0;
    instr_in6[i] = (i % 25 == 0) ? i + 30 : 0;
    instr_in7[i] = (i % 26 == 0) ? i + 31 : 0;
    instr_in8[i] = (i % 27 == 0) ? i + 32 : 0;
    instr_in9[i] = (i % 28 == 0) ? i + 33 : 0;
    instr_in10[i] = (i % 29 == 0) ? i + 34 : 0;
    instr_in11[i] = (i % 30 == 0) ? i + 35 : 0;
    instr_in12[i] = (i % 31 == 0) ? i + 36 : 0;
    instr_in13[i] = (i % 32 == 0) ? i + 37 : 0;
    instr_in14[i] = (i % 33 == 0) ? i + 38 : 0;
    instr_in15[i] = (i % 34 == 0) ? i + 39 : 0;
    instr_in16[i] = (i % 35 == 0) ? i + 40 : 0;
  }

  int total_fetched = 0;
  int total_executed = 0;
  kernel(instr_in1, instr_in2, instr_in3, instr_in4, instr_in5, instr_in6,
         instr_in7, instr_in8, instr_in9, instr_in10, instr_in11, instr_in12,
         instr_in13, instr_in14, instr_in15, instr_in16, total_fetched,
         total_executed);
  printf("total_fetched = %d\n", total_fetched);
  printf("total_executed = %d\n", total_executed);
  return 0;
}
