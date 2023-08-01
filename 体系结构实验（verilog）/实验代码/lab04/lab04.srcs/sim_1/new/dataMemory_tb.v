`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/03/29 11:13:34
// Design Name: 
// Module Name: dataMemory_tb
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


module dataMemory_tb(

    );
    reg clk;
    reg [31 : 0] address;
    reg [31 : 0] writeData;
    reg memWrite;
    reg memRead;
    wire [31 : 0] readData;
    
    dataMemory u0(
        .clk(clk), 
        .address(address), 
        .writeData(writeData),
        .memWrite(memWrite), 
        .memRead(memRead), 
        .readData(readData)
        );
    
    always #100 clk = ~clk;
    
    initial begin
        // Initialize Inputs
        clk = 0;
        address = 0;
        writeData = 0;
        memWrite = 0;
        memRead = 0;
        // Current Time: 185 ns
        #185;
        memWrite = 1'b1;
        address = 32'b00000000000000000000000000000111;// write data1
        writeData = 32'b11100000000000000000000000000000;
        
        // Current Time: 285 ns
        #100;
        memWrite = 1'b1;
        writeData = 32'hffffffff;
        address = 32'b00000000000000000000000000000110;
        
        // Current Time: 470 ns
        #185;
        memRead = 1'b1;
        memWrite = 0'b0;
        address = 32'b00000000000000000000000000000111;// read data1
        
        // Current Time: 550 ns
        #80;
        memWrite = 1;
        address = 32'b00000000000000000000000000001000;// write data 2
        writeData = 32'haaaaaaaa;
        
        // Current Time: 630 ns
        #80;
        memWrite = 0;
        memRead = 1;
        address = 32'b00000000000000000000000000000110;// read data2
    end
endmodule
