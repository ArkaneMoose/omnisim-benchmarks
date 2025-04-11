open_project -reset project
set_top kernel
add_files kernel.cpp
add_files -tb testbench.cpp

open_solution -reset solution1
set_part {xcvu9p-flga2104-2-i}
create_clock -period 5 -name default

csim_design
csynth_design
cosim_design
