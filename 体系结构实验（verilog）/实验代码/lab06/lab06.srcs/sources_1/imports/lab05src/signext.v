`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/03/29 11:24:27
// Design Name: 
// Module Name: signext
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


module signext(
    input extSign,
    input [15:0] inst,
    output [31:0] data
    );
    reg [31:0] Data;
    reg [15:0] Inst;
    
    assign data = (extSign ? {{16{inst[15]}}, inst[15:0]} : {16'h0000, inst[15:0]});
    
endmodule
