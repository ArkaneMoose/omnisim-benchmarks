#include "kernel.hpp"
#include <etc/autopilot_ssdm_op.h>
#include <hls_stream.h>
#include <stdio.h>

using hls::stream;

void fetch(stream<int> &instr, stream<int> &addr, const int *instr_in,
           int &fetched) {
  for (int i = 0; i < N; i++) {
    fetched++;
    instr.write(instr_in[i]);
    int target_addr;
    if (addr.read_nb(target_addr)) {
      i = target_addr;
    }
  }
  instr.write(-1);
}

void execute(stream<int> &instr, stream<int> &addr, int &executed) {
  while (true) {
    int value = instr.read();
    if (value < 0)
      break;
    if (value > 0) {
      addr.write(value);
      executed++;
    }
  }
}

void kernel(const int instr_in[N], int &fetched, int &executed) {
#pragma HLS DATAFLOW
  stream<int> instr, addr;
  fetch(instr, addr, instr_in, fetched);
  execute(instr, addr, executed);
}
