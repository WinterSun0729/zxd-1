`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/03/29 08:44:21
// Design Name: 
// Module Name: ALUCtr
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


module ALUCtr(
    input [1:0] aluOp,
    input [5:0] funct,
    output [3:0] aluCtrOut
    );
    reg [3:0] ALUCtrOut;

    always@(aluOp or funct)
    begin
        casex({aluOp, funct})
            8'b00xxxxxx://lw, sw
            begin
            ALUCtrOut = 4'b0010;
            end

            8'bx1xxxxxx://beq
            begin
            ALUCtrOut = 4'b0110;
            end

            8'b1xxx0000://add
            begin
            ALUCtrOut = 4'b0010;
            end

            8'b1xxx0010://sub
            begin
            ALUCtrOut = 4'b0110;
            end

            8'b1xxx0100://and
            begin
            ALUCtrOut = 4'b0000;
            end

            8'b1xxx0101://or
            begin
            ALUCtrOut = 4'b0001;
            end

            8'b1xxx1010://stl
            begin
            ALUCtrOut = 4'b0111;
            end
        endcase
    end

    assign aluCtrOut = ALUCtrOut;
endmodule
