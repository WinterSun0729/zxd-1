`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/03/29 11:39:12
// Design Name: 
// Module Name: signext_tb
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


module signext_tb(

    );
    reg [15 : 0] inst;
    wire [31 : 0] data;
    
    signext u0(
        .inst(inst),
        .data(data)
    );
    
    initial begin
        inst = 0;
        
        #100;
        inst = 16'h0001;
        
        #100;
        inst = 16'hffff;
        
        #100;
        inst = 16'h0002;

        #100;
        inst = 16'hfffe;
        
        #100;
        inst = 16'h8120;
        
        #100;
        inst = 16'h0251;
    end
endmodule
