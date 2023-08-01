`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/04/13 13:15:12
// Design Name: 
// Module Name: InstMem
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


module InstMem(
    input [31 : 0] readAddr,
    input clk,
    input reset,
    output [31 : 0] instr
    );

    reg [31:0] instMEM [0:255];//set size as 256
    reg [31:0] n;

    assign instr = instMEM[readAddr >> 2];

endmodule
