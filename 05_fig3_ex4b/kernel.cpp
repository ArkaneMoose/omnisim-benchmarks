#include "kernel.hpp"
#include <hls_stream.h>
#include <stdio.h>

using hls::stream;

void producer(stream<int> &FIFO, const int *data, int &Dropped) {
  for (int i = 0; i < N;) {
    if (FIFO.write_nb(data[i]))
      i++;
    else {
      i++;
      Dropped++;
    }
  }
  FIFO.write(0);
}

void consumer(stream<int> &FIFO, int *sum_out) {
  while (true) {
// We intentionally slow down this pipeline so that the producer's write_nb()
// doesn't always succeed (which masks the timing-dependent behavior of this
// kernel). You can imagine that this is a more complex operation with a
// loop-carried dependency that takes several cycles to complete.
#pragma HLS PIPELINE II = 3
    int read_value = FIFO.read();
    *sum_out += read_value / 3;
    if (read_value == 0)
      break;
  }
}

void kernel(int *sum_out, const int data[N], int &Dropped) {
#pragma HLS DATAFLOW
  stream<int> FIFO;
  producer(FIFO, data, Dropped);
  consumer(FIFO, sum_out);
}
