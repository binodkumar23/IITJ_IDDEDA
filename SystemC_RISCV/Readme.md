Project name: Simple RISCV CPU design in SystemC
===========================================================================================================================
To run: 

(0) Ensure that SystemC is installed at path, /usr/local/systemc-2.3.2/

(1) Get cpu.cpp and cpu_testbench.cpp to the same path

(2) At that path run the following commands, 
    (a) export SYSTEMC_HOME=/usr/local/systemc-2.3.2/
    (b) g++ -I. -I$SYSTEMC_HOME/include -L. -L$SYSTEMC_HOME/lib-linux64 -Wl,-rpath=$SYSTEMC_HOME/lib-linux64 -o cpu_testbench cpu_testbench.cpp -lsystemc -lm
    (c) ./cpu_testbench

To make changes:

(1) Refer the opcode, and funct values used in cpu.cpp ( They can be changed as well, as long as they follow the standards)
(2) Edit the instruction in instruction memory accordingly, in the set of 32 bits


Project done by: Vipul Sharma(B19CSE099) and Darsh Patel(B19CSE115)

===================================================================================

For any query/suggestions: please write to Binod Kumar (binod@iitj.ac.in)
