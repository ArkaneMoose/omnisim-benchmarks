#include "kernel.hpp"
#include <hls_stream.h>
#include <stdio.h>

using hls::stream;

void producer(stream<int> &FIFO, stream<bool> &done_signal, const int *data,
              int &Dropped) {
  int i = 0;
  bool done;
  while (true) {
    if (FIFO.write_nb(data[i]))
      i++;
    else {
      i++;
      Dropped++;
    }
    if (done_signal.read_nb(done))
      break;
  }
}

void consumer(stream<int> &FIFO, stream<bool> &done_signal, int *sum_out) {
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
  done_signal.write(true);
}

void kernel(int *sum_out, const int data[MAX_DATA_SIZE], int &Dropped) {
#pragma HLS DATAFLOW
  stream<int> FIFO;
  stream<bool> done_signal;

  // N.B.: For Vitis HLS to execute C/RTL co-simulation, it requires that the C
  // testbench pass with no errors. Under C simulation, producer() will either
  // get stuck in the infinite loop, or it will run off the end of the input
  // array and crash, so this will not work. For this reason, we guard the
  // producer() with a #ifdef __SYNTHESIS__ directive. Rest assured, OmniSim
  // uses the code compiled for synthesis and will correctly call producer().
#ifdef __SYNTHESIS__
  producer(FIFO, done_signal, data, Dropped);
#else
  fprintf(stderr, "Skipping producer() in C simulation.\n");
#endif
  consumer(FIFO, done_signal, sum_out);
}
