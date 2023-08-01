`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/03/27 21:08:30
// Design Name: 
// Module Name: Register
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


module Register(
    input [25:21] readReg1,
    input [20:16] readReg2,
    input [4:0] writeReg,
    input [31:0] writeData,
    input regWrite,
    input clk,
    output [31:0] readData1,
    output [31:0] readData2
    );
    
    reg [31:0] RegFile[31:0];
    reg [31:0] ReadData1;
    reg [31:0] ReadData2;
    reg [31:0] WriteData;
    integer i;

    //init the RegFile
    initial begin
    for(i=0;i<=31;i=i+1)
       RegFile[i]=0;
    end

    always @ (readReg1 or readReg2 or writeReg)
    begin
        ReadData1 = RegFile[readReg1];
        ReadData2 = RegFile[readReg2];
        WriteData = writeData;
    end

    always @ (negedge clk)
    begin
        if(regWrite)
            RegFile[writeReg] = WriteData; 
    end

    assign readData1 = RegFile[readReg1];
    assign readData2 = RegFile[readReg2];

endmodule
