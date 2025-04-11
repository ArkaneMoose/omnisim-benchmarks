#include "kernel.hpp"
#include <etc/autopilot_ssdm_op.h>
#include <hls_stream.h>
#include <stdio.h>

using hls::stream;

void controller(stream<int> &FIFO1, stream<int> &FIFO2, const int *data_in,
                int *sum) {
  for (int i = 0; i < N; i++) {
    int read_value = FIFO2.read();
    FIFO1.write(data_in[i]);
    *sum += read_value;
  }
}

void processor(stream<int> &FIFO1, stream<int> &FIFO2) {
  for (int i = 0; i < N; i++) {
    int value = FIFO1.read();
    FIFO2.write(value * 2);
  }
}

void kernel(int *sum, const int data_in[N]) {
#pragma HLS DATAFLOW
  stream<int> FIFO1, FIFO2;
  controller(FIFO1, FIFO2, data_in, sum);
  processor(FIFO1, FIFO2);
}
