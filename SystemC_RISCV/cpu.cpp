/*

To run: 

export SYSTEMC_HOME=/usr/local/systemc-2.3.2/

g++ -I. -I$SYSTEMC_HOME/include -L. -L$SYSTEMC_HOME/lib-linux64 -Wl,-rpath=$SYSTEMC_HOME/lib-linux64 -o cpu_testbench cpu_testbench.cpp -lsystemc -lm

./cpu_testbench

*/

#include "systemc.h"


SC_MODULE (cpu) {
  sc_in_clk     clock ;      // Clock input of the design
  sc_out<bool> cpu_out;

  sc_in <sc_bv<32>> instruction;
  sc_inout <int> Program_Counter;

  sc_in <sc_bv<32*32>> instruction_memory;
  sc_inout <sc_bv<32*32>> data_memory;
  
  //------------Local Variables Here---------------------
  sc_uint<4>	count;


  // 32 CPU registers
  sc_int<32> register_memory[32];

  

  //cout<<register_memory[0]<<"check 1\n";
  

    /*
    R-type: register-register
    I-type: short immediates and loads
    S-type: stores
    B-type: conditional branches, a variation of S-type
    U-type: long immediates
    J-type: unconditional jumps, a variation of U-type
    */

  sc_bv<7>  R_type_opcode = "1001111";
  sc_bv<7>  I_type_opcode = "1101111";
  sc_bv<7>  S_type_opcode = "0100011";
  sc_bv<7>  B_type_opcode = "1100011";
  sc_bv<7>  J_type_opcode = "1101110";
  //sc_bv<7>  R_type_add_func7 = "0000000";
  //sc_bv<3>  R_type_add_func3 = "111";

  // R_type grp1 
  sc_bv<7>  R_type_add_func7 = "0000000";
  sc_bv<3>  R_type_add_func3 = "111";
    
  
  // R_type grp2
  sc_bv<7>  R_type_and_func7 = "0000001";
  sc_bv<7>  R_type_or_func7 = "0000001";
  sc_bv<7>  R_type_xor_func7 = "0000001";
  
  sc_bv<3>  R_type_and_func3 = "111";
  sc_bv<3>  R_type_or_func3 = "110";
  sc_bv<3>  R_type_xor_func3 = "100";

  

  // R_type grp4
	sc_bv<7>  R_type_sub_func7 = "0100000";
  sc_bv<3>  R_type_sub_func3 = "111";

  // B type functs
  sc_bv<3>  B_type_beq_func3 = "000";
  sc_bv<3>  B_type_bne_func3 = "001";


  
  //------------Code Starts Here-------------------------
  // Below function implements actual cpu logic
  void select_line () {


    // At every rising edge of clock we read the instruction memory
    // from the location pointed by Program Counter
    sc_bv<32> temp = instruction_memory.read()( (32*32) -1 - Program_Counter ,  (32*32) -32 - Program_Counter );



    //for(int i = Program_Counter;i<Program_Counter+32)


    //sc_bv<32> temp = instruction_memory.range(Program_Counter,Program_Counter+32);
    //cout<<instruction_memory.read()(Program_Counter+31, Program_Counter )<<"\n";
    
    //cout<<"after  "<<(data_memory.read()( (32*32) -1 - (0)*32 ,  (32*32) -32 - (0)*32 ) )<<"\n";
        
    //return;
    
    cout<<"\nProgram Counter :"<<Program_Counter<<"\n";
    Program_Counter.write(Program_Counter+4*8);
    //  R-TYPE
    cout<<"Current Instruction "<<temp<<"\n";
    
    //"00000010000100000 100 000101001111"
    //"00000010000100000 111 000101001111"
    //"00000010000100000 110 000101001111"
    //cout<<temp.range(6,0)<<" "<<temp.range(31,25)<<" "<<temp.range(14,12)<<"\n";

    cout<<"Data Memory Location 0: "<<(data_memory.read()( (32*32) -1 - (0)*32 ,  (32*32) -32 - (0 )*32 ) )<<"\n";

    if(temp.range(6,0)==R_type_opcode) {

      if(temp.range(31,25)==R_type_add_func7 && temp.range(14,12)==R_type_add_func3){
        cout<<"add\n";
        sc_int<32> loc_operand1  = (temp.range(24,20)).to_int();
        sc_int<32> loc_operand2  = (temp.range(19,15)).to_int();
        sc_int<32> loc_dest  = (temp.range(11,7)).to_int();

        register_memory[loc_dest] = register_memory[loc_operand1] + register_memory[loc_operand2];
        
        cout<<register_memory[loc_dest]<<" "<<register_memory[loc_operand1]<<" "<<register_memory[loc_operand2]<<"\n";
        
        cout<<"@" << sc_time_stamp() <<"\n";
      }
      else if(temp.range(31,25)==R_type_sub_func7 && temp.range(14,12)==R_type_sub_func3){

      sc_int<32> loc_operand1  = (temp.range(24,20)).to_int();
      sc_int<32> loc_operand2  = (temp.range(19,15)).to_int();
      sc_int<32> loc_dest  = (temp.range(11,7)).to_int();

      register_memory[loc_dest] = register_memory[loc_operand1] - register_memory[loc_operand2];
      
      cout<<register_memory[loc_dest]<<" "<<register_memory[loc_operand1]<<" "<<register_memory[loc_operand2]<<"\n";
      
      cout<<"@" << sc_time_stamp() <<"\n";


      }

      else if(temp.range(31,25)==R_type_and_func7 && temp.range(14,12)==R_type_and_func3){
        cout<<"and\n";
        sc_int<32> loc_operand1  = (temp.range(24,20)).to_int();
        sc_int<32> loc_operand2  = (temp.range(19,15)).to_int();
        sc_int<32> loc_dest  = (temp.range(11,7)).to_int();

        register_memory[loc_dest] = register_memory[loc_operand1] & register_memory[loc_operand2];
        
        cout<<register_memory[loc_dest]<<" "<<register_memory[loc_operand1]<<" "<<register_memory[loc_operand2]<<"\n";
        
        cout<<"@" << sc_time_stamp() <<"\n";

      }

      else if(temp.range(31,25)==R_type_xor_func7 && temp.range(14,12)==R_type_xor_func3){
        cout<<"xor\n";
        sc_int<32> loc_operand1  = (temp.range(24,20)).to_int();
        sc_int<32> loc_operand2  = (temp.range(19,15)).to_int();
        sc_int<32> loc_dest  = (temp.range(11,7)).to_int();

        register_memory[loc_dest] = register_memory[loc_operand1] ^ register_memory[loc_operand2];
        
        cout<<register_memory[loc_dest]<<" "<<register_memory[loc_operand1]<<" "<<register_memory[loc_operand2]<<"\n";
        
        cout<<"@" << sc_time_stamp() <<"\n";

      }
      else if(temp.range(31,25)==R_type_or_func7 && temp.range(14,12)==R_type_or_func3){
        cout<<"or\n";
        sc_int<32> loc_operand1  = (temp.range(24,20)).to_int();
        sc_int<32> loc_operand2  = (temp.range(19,15)).to_int();
        sc_int<32> loc_dest  = (temp.range(11,7)).to_int();

        register_memory[loc_dest] = register_memory[loc_operand1] | register_memory[loc_operand2];
        
        cout<<register_memory[loc_dest]<<" "<<register_memory[loc_operand1]<<" "<<register_memory[loc_operand2]<<"\n";
        
        cout<<"@" << sc_time_stamp() <<"\n";


      }


    }
    else if(temp.range(6,0)==I_type_opcode){
      // I - type

      // implementing load
        //cout<<"vksdjbvkjn\n";
        cout<<"load\n";
        sc_int<32> offset   = (temp.range(31,20)).to_int();
        sc_int<32> loc_operand  = (temp.range(19,15)).to_int();
        sc_int<32> funct3  = (temp.range(14,12)).to_int();
        sc_int<32> loc_dest  = (temp.range(11,7)).to_int();
        cout<<"Register at "<< loc_dest<<" value "<<register_memory[loc_dest]<<"\n";
        //register_memory[loc_dest] = data_memory[ register_memory[loc_operand]+offset ];  
        register_memory[loc_dest] = (data_memory.read()( (32*32) -1 - (register_memory[loc_operand]+offset)*32 ,  (32*32) -32 - (register_memory[loc_operand]+offset )*32 ) ).to_int();    
        cout<<(data_memory.read()( (32*32) -1 - (register_memory[loc_operand]+offset)*32 ,  (32*32) -32 - (register_memory[loc_operand]+offset )*32 ) )<<"\n";
        cout<<"Register at "<< loc_dest<<" value "<<register_memory[loc_dest]<<"\n";

        cout<<"@" << sc_time_stamp() <<"\n";
    }
    else if(temp.range(6,0)==S_type_opcode){
        
        cout<<"store\n";
        sc_bv<12> offset_bits;
        offset_bits.range(11,5) = temp.range(31,25);
        offset_bits.range(4,0) = temp.range(11,7);
        sc_int<32> offset   = (offset_bits).to_int();
        
        sc_int<32> loc_base  = (temp.range(19,15)).to_int();
        sc_int<32> funct3  = (temp.range(14,12)).to_int();
        sc_int<32> loc_src  = (temp.range(24,20)).to_int();

        sc_bv<32*32> temp = data_memory;
        
        

        temp.range( (32*32) -1 - (register_memory[loc_base]+offset)*32 ,  (32*32) -32 - (register_memory[loc_base]+offset )*32 ) = register_memory[loc_src]; //.range(31,0)<<"sdshbvjksbdkjvbkjbfsjkbvkjbkjdvkbs\n";
        cout<<"storing "<<temp.range( (32*32) -1 - (register_memory[loc_base]+offset)*32 ,  (32*32) -32 - (register_memory[loc_base]+offset )*32 )<<"\n";
        //cout<<loc_base<<" --- "<<offset<<" --  "<<(register_memory[loc_base]+offset )<<" == "<<register_memory[5] <<"\n";
        //cout<<(32*32) -1 - (register_memory[loc_base]+offset)*32<<" ------ "<<(32*32) -32 - (register_memory[loc_base]+offset )*32<<"\ffff\n";
        data_memory.write(temp.range((32*32) -1, 0));//( (32*32) -1 - (register_memory[loc_base]+offset)*32 ,  (32*32) -32 - (register_memory[loc_base]+offset )*32 );
        
        //cout<<"after  "<<data_memory  <<"\n";
        cout<<"@" << sc_time_stamp() <<"\n";

    }
    else if(temp.range(6,0)==B_type_opcode){
      cout<<"branch\n";
      sc_bv<13> offset_bits;
      offset_bits.range(11,11) = temp.range(7,7);
      offset_bits.range(4,1) = temp.range(11,8);
      offset_bits.range(10,5) = temp.range(30,25);
      offset_bits.range(12,12) = temp.range(31,31);
      offset_bits.range(0,0) = "0";

      sc_int<32> funct3  = (temp.range(14,12)).to_int();

      sc_int<32> loc_operand1  = (temp.range(24,20)).to_int();
      sc_int<32> loc_operand2  = (temp.range(19,15)).to_int();
      
      if(funct3==B_type_bne_func3.to_int()){
        if(register_memory[loc_operand1]!=register_memory[loc_operand2] ){
          Program_Counter.write(Program_Counter + 2*32*offset_bits.to_int());
        }
      }
      else if(funct3==B_type_beq_func3.to_int()){
        if(register_memory[loc_operand1]==register_memory[loc_operand2] ){
          
          Program_Counter.write(Program_Counter + 2*32*offset_bits.to_int());
        }
      }
        cout<<"@" << sc_time_stamp() <<"\n";

    }
    else if(temp.range(6,0)==J_type_opcode){
      cout<<" unconditional branch\n";
      sc_bv<21> offset_bits;
      offset_bits.range(0,0) = "0";
      offset_bits.range(10,1) = temp.range(30,21);
      
      offset_bits.range(11,11) = temp.range(20,20);
      offset_bits.range(20,20) = temp.range(31,31);
      offset_bits.range(19,12) = temp.range(19,12);
      cout<<Program_Counter + 2*32*offset_bits.to_int()<<"\n";
      Program_Counter.write(Program_Counter + 2*32*offset_bits.to_int());
      cout<<"@" << sc_time_stamp() <<"\n";
    }

    else {
      cout<<"@" << sc_time_stamp()<<" "<<instruction <<" Null  \n";
    }
    

    /*if (select.read() == 0) {
      count =  0;
      cpu_out.write(line1);
    // If enable is active, then we in
      cout<<"@" << sc_time_stamp() <<" :: Line1 selected  "
        <<cpu_out.read()<<endl;crement the counter
    } else if (select.read() == 1) {
      count = count + 1;
      count =  0;
      cpu_out.write(line2);
      cout<<"@" << sc_time_stamp() <<" :: Line2 selected  "
        <<cpu_out.read()<<endl;
    }
    */
  } // End of function incr_count

  // Constructor for the counter
  // Since this counter is a positive edge trigged one,
  // We trigger the below block with respect to positive
  // edge of the clock and also when ever reset changes state
  SC_CTOR(cpu) {
    register_memory[0] = 111;
    register_memory[1] = 111;
    register_memory[2] = 0;
    register_memory[3] = 3;
    register_memory[5] = 0;

    cout<<"Executing new"<<endl;
    SC_METHOD(select_line);
    sensitive << clock.pos();
    //sensitive << reset;
    
  } // End of Constructor

}; // End of Module counter
