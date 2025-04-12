#include "kernel.hpp"
#include <etc/autopilot_ssdm_op.h>
#include <hls_stream.h>
#include <stdio.h>

using hls::stream;

void fetch(stream<int> &instr, stream<int> &addr, const int *instr_in,
           stream<int> &fetched) {
  int num_fetched = 0;
  for (int i = 0; i < N; i++) {
    num_fetched++;
    instr.write(instr_in[i]);
    int target_addr;
    if (addr.read_nb(target_addr)) {
      i = target_addr;
    }
  }
  instr.write(-1);
  fetched.write(num_fetched);
}

void execute(stream<int> &instr, stream<int> &addr, stream<int> &executed) {
  int num_executed = 0;
  while (true) {
    int value = instr.read();
    if (value < 0)
      break;
    if (value > 0) {
      addr.write(value);
      num_executed++;
    }
  }
  executed.write(num_executed);
}

void aggregate(stream<int> fetched[16], stream<int> executed[16],
               int &total_fetched, int &total_executed) {
  for (int i = 0; i < 16; i++) {
#pragma HLS UNROLL
    total_fetched += fetched[i].read();
    total_executed += executed[i].read();
  }
}

void kernel(const int instr_in1[N], const int instr_in2[N],
            const int instr_in3[N], const int instr_in4[N],
            const int instr_in5[N], const int instr_in6[N],
            const int instr_in7[N], const int instr_in8[N],
            const int instr_in9[N], const int instr_in10[N],
            const int instr_in11[N], const int instr_in12[N],
            const int instr_in13[N], const int instr_in14[N],
            const int instr_in15[N], const int instr_in16[N],
            int &total_fetched, int &total_executed) {
#pragma HLS DATAFLOW
  stream<int> instr[16], addr[16], fetched[16], executed[16];
  fetch(instr[0], addr[0], instr_in1, fetched[0]);
  fetch(instr[1], addr[1], instr_in2, fetched[1]);
  fetch(instr[2], addr[2], instr_in3, fetched[2]);
  fetch(instr[3], addr[3], instr_in4, fetched[3]);
  fetch(instr[4], addr[4], instr_in5, fetched[4]);
  fetch(instr[5], addr[5], instr_in6, fetched[5]);
  fetch(instr[6], addr[6], instr_in7, fetched[6]);
  fetch(instr[7], addr[7], instr_in8, fetched[7]);
  fetch(instr[8], addr[8], instr_in9, fetched[8]);
  fetch(instr[9], addr[9], instr_in10, fetched[9]);
  fetch(instr[10], addr[10], instr_in11, fetched[10]);
  fetch(instr[11], addr[11], instr_in12, fetched[11]);
  fetch(instr[12], addr[12], instr_in13, fetched[12]);
  fetch(instr[13], addr[13], instr_in14, fetched[13]);
  fetch(instr[14], addr[14], instr_in15, fetched[14]);
  fetch(instr[15], addr[15], instr_in16, fetched[15]);
  execute(instr[0], addr[0], executed[0]);
  execute(instr[1], addr[1], executed[1]);
  execute(instr[2], addr[2], executed[2]);
  execute(instr[3], addr[3], executed[3]);
  execute(instr[4], addr[4], executed[4]);
  execute(instr[5], addr[5], executed[5]);
  execute(instr[6], addr[6], executed[6]);
  execute(instr[7], addr[7], executed[7]);
  execute(instr[8], addr[8], executed[8]);
  execute(instr[9], addr[9], executed[9]);
  execute(instr[10], addr[10], executed[10]);
  execute(instr[11], addr[11], executed[11]);
  execute(instr[12], addr[12], executed[12]);
  execute(instr[13], addr[13], executed[13]);
  execute(instr[14], addr[14], executed[14]);
  execute(instr[15], addr[15], executed[15]);
  aggregate(fetched, executed, total_fetched, total_executed);
}
