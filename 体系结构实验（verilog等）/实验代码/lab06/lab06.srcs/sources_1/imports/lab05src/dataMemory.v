`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/03/29 10:38:31
// Design Name: 
// Module Name: dataMemory
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


module dataMemory(
    input clk,
    input [31:0] address,
    input [31:0] writeData,
    input memWrite,
    input memRead,
    output [31:0] readData
    );

    reg [31:0] memFile[0:255];
    reg [31:0] ReadData;
    integer i;

    always @ (address or memRead)
    begin
        if(address < 255 && memRead && !memWrite)
        begin
            ReadData = memFile[address];
        end
    end

    always @ (negedge clk)
    begin
        if(address < 255 && memWrite)
        begin
            memFile[address] = writeData;
        end
    end
    
    assign readData = ReadData;

endmodule
