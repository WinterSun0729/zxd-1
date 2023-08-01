`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/04/17 23:17:54
// Design Name: 
// Module Name: Streamline_CPU
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


module mips_tb(
    );
    reg clk;
    reg reset;
        
    Top processor(.clk(clk), .reset(reset));
    
    initial begin
        $readmemb("Y:/Vivado/lab06/inst_data.dat", processor.instmem_module.instMEM);
        $readmemh("Y:/Vivado/lab06/mem_data.dat", processor.datamemory_module.memFile);         
        reset = 1;
        clk = 0;
    end
    
    always #10 clk = ~clk;
    
    initial begin
        #10 reset = 0;
        #20 reset = 1;
        #10 reset = 0;
    end
endmodule
