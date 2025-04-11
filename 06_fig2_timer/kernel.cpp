#include "kernel.hpp"
#include <hls_stream.h>
#include <stdio.h>

using hls::stream;

void compute(stream<data_t> &d_in, stream<data_t> &FIFO) {
  for (int i = 0; i < N; i++) {
#pragma HLS PIPELINE off
    data_t d = d_in.read();
    data_t d_out = d / 3;
    FIFO.write(d_out);
  }
}

void timer(stream<data_t> &d_in, stream<data_t> &FIFO, const data_t data[N],
           int *total_cycles) {
  for (int i = 0; i < N; i++) {
#pragma HLS PIPELINE off
    int cycles = 0;
    d_in.write(data[i]);
    while (FIFO.empty())
      cycles++;
    FIFO.read();
    *total_cycles += cycles;
  }
}

void kernel(const data_t data[N], int *total_cycles) {
#pragma HLS DATAFLOW
  stream<data_t> d_in, FIFO;
  compute(d_in, FIFO);
  timer(d_in, FIFO, data, total_cycles);
}
