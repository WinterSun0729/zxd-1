`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/04/13 18:48:32
// Design Name: 
// Module Name: Single_Cycle_CPU_tb
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module Single_Cycle_CPU_tb(

    );
    reg clk;
    reg reset;
    
    Top processor(
        .clk(clk),
        .reset(reset)
    );
    
    initial begin
        $readmemb("Y:/Vivado/lab05/mem_inst.dat", processor.instmem_module.instMEM);
        $readmemh("Y:/Vivado/lab05/mem_data.dat", processor.datamemory_module.memFile);         
        reset = 0;
        clk = 0;
    end
    
    always #10 clk = ~clk;
    
    initial begin
        reset = 0;
        #30;
        reset = 1;
        #40;
        reset = 0;
    end
endmodule
