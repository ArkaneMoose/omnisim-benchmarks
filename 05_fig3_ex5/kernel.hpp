#ifndef __KERNEL_HPP__
#define __KERNEL_HPP__

#define N 2025

int process_it_fast(int instr);
int process_it_slow(int instr);
void kernel(const int ins[N], int &processed_by_P1, int &processed_by_P2,
            int *sum_out_P1, int *sum_out_P2);

#endif // __KERNEL_HPP__
