`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/04/13 13:26:53
// Design Name: 
// Module Name: PC
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


module PC(
    input [31 : 0] PCin,
    input reset,
    input clk,
    output [31 : 0] pcout
    );

    reg [31 : 0] PCout;
    
    always @ (posedge clk or reset)
    begin
        if (reset)
            PCout = 0;
        else
            PCout = PCin;
    end

    assign pcout = PCout;
    
endmodule
