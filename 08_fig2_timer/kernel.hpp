#ifndef __KERNEL_HPP__
#define __KERNEL_HPP__

#include <ap_fixed.h>

#define N 2025

typedef ap_fixed<32, 16> data_t;

void kernel(const data_t data[N], int *total_cycles);

#endif // __KERNEL_HPP__
