`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/03/29 09:11:06
// Design Name: 
// Module Name: ALUCtr_tb
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


module ALUCtr_tb(

    );
    reg [1:0] ALUOp;
    reg [5:0] Funct;
    wire [3:0] ALUCtrOut;
    
    ALUCtr u0(
        .aluOp(ALUOp), 
        .funct(Funct), 
        .aluCtrOut(ALUCtrOut)
        );

    initial begin
        ALUOp = 0;
        Funct = 0;
        #100;
        
        //0010
        ALUOp = 2'b00;
        Funct = 6'b000000;
        #100;
        
        //0110
        ALUOp = 2'b01;
        Funct = 6'b000000;
        #100;
        
        //0010
        ALUOp = 2'b10;
        Funct = 6'b000000;
        #100;
        
        //0110
        ALUOp = 2'b10;
        Funct = 6'b000010;
        #100;
        
        //0000
        ALUOp = 2'b10;
        Funct = 6'b000100;
        #100;
        
        //0001
        ALUOp = 2'b10;
        Funct = 6'b000101;
        #100;
        
        //0111
        ALUOp = 2'b10;
        Funct = 6'b001010;
        #100;
    end
    
endmodule
