`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/04/13 13:15:49
// Design Name: 
// Module Name: PCupdate
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


module PCupdate(
    input [31:0] newPC,
    input [25:0] target,
    input [31:0] offset,
    input [31:0] regOut,
    input Branch,
    input Aluzero,
    input Jump,
    input JrSign,
    output [31:0] nextPC
    );

    wire [27:0] shtarget;
    assign shtarget = target << 2;

    wire [31:0] jumptarget;
    assign jumptarget = {newPC [31:28], shtarget};

    wire [31:0] branchtarget;
    assign branchtarget = newPC + offset;

    wire [31:0] nonjumptarget;
    assign nonjumptarget = (Branch & Aluzero) ? (branchtarget) : (newPC);

    wire [31:0] nonretaddr;
    assign nonretaddr = (Jump) ? (jumptarget) : (nonjumptarget);

    assign nextPC = (JrSign) ? (regOut) : (nonretaddr);

endmodule