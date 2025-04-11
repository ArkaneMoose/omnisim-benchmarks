#include "kernel.hpp"
#include <hls_stream.h>
#include <stdio.h>

using hls::stream;

void producer(stream<int> &FIFO1, stream<int> &FIFO2, const int *ins,
              int &processed_by_P1, int &processed_by_P2) {
  for (int i = 0; i < N;) {
    if (FIFO1.write_nb(ins[i])) {
      processed_by_P1++;
      i++;
    } else if (FIFO2.write_nb(ins[i])) {
      processed_by_P2++;
      i++;
    }
  }
  FIFO1.write(0);
  FIFO2.write(0);
}

void processor1(stream<int> &FIFO1, int *sum_out_P1) {
  while (true) {
#pragma HLS PIPELINE II = 3
    int instr = FIFO1.read();
    *sum_out_P1 += process_it_fast(instr);
    if (instr == 0)
      break;
  }
}

void processor2(stream<int> &FIFO2, int *sum_out_P2) {
  while (true) {
#pragma HLS PIPELINE II = 5
    int instr = FIFO2.read();
    *sum_out_P2 += process_it_slow(instr);
    if (instr == 0)
      break;
  }
}

void kernel(const int ins[N], int &processed_by_P1, int &processed_by_P2,
            int *sum_out_P1, int *sum_out_P2) {
#pragma HLS DATAFLOW
  stream<int> FIFO1, FIFO2;
  producer(FIFO1, FIFO2, ins, processed_by_P1, processed_by_P2);
  processor1(FIFO1, sum_out_P1);
  processor2(FIFO2, sum_out_P2);
}

int process_it_fast(int instr) {
#pragma HLS LATENCY min = 2
  return instr / 3;
}

int process_it_slow(int instr) {
#pragma HLS LATENCY min = 4
  return instr / 3;
}
