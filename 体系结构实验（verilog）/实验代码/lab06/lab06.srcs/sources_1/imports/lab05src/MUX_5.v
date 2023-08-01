`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/04/13 18:38:07
// Design Name: 
// Module Name: MUX_5
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


module MUX_5(
    input Select,
    input [4 : 0] data0,
    input [4 : 0] data1,
    output [4 : 0] data
    );
    
    assign data = Select ? data0 : data1;

endmodule
