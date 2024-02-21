`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/03/29 08:30:43
// Design Name: 
// Module Name: Ctr
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


module Ctr(
    input [5:0] opCode,
    input nop,
    output regDst,
    output aluSrc,
    output memToReg,
    output regWrite,
    output memRead,
    output memWrite,
    output branch,
    output [2:0] aluOp,
    output jump,
    output extSign,
    output jalSign
    );
    
    reg RegDst;
    reg ALUSrc;
    reg MemToReg;
    reg RegWrite;
    reg MemRead;
    reg MemWrite;
    reg Branch;
    reg [2:0] ALUOp;
    reg Jump;
    reg ExtSign;
    reg JalSign;

    always @(opCode)
    if (nop) begin
        ALUOp = 3'b111;
            RegDst = 0;
            ALUSrc = 0;
            MemToReg = 0;
            RegWrite = 0;
            MemRead = 0;
            MemWrite = 0;
            Branch = 0;
            Jump = 0;
            ExtSign = 0;
            JalSign = 0;
    end 
    else begin
        case(opCode)
        6'b000000: //R type
        begin
            ALUOp = 3'b101;
            RegDst = 1;
            ALUSrc = 0;
            MemToReg = 0;
            RegWrite = 1;
            MemRead = 0;
            MemWrite = 0;
            Branch = 0;
            Jump = 0;
            ExtSign = 0;
            JalSign = 0;
        end
        
        //lw command
        6'b100011:
        begin
            ALUOp = 3'b000;
            RegDst = 0;
            ALUSrc = 1;
            MemToReg = 1;
            RegWrite = 1;
            MemRead = 1;
            MemWrite = 0;
            Branch = 0;
            Jump = 0;
            ExtSign = 1;
            JalSign = 0;
        end

        //sw command
        6'b101011:
        begin
            ALUOp = 3'b000;
            RegDst = 0;
            ALUSrc = 1;
            MemToReg = 0;
            RegWrite = 0;
            MemRead = 0;
            MemWrite = 1;
            Branch = 0;
            Jump = 0;
            ExtSign = 1;
            JalSign = 0;
        end

        //addi command
        6'b001000:
        begin
            ALUOp = 3'b001;
            RegDst = 0;
            ALUSrc = 1;
            MemToReg = 0;
            RegWrite = 1;
            MemRead = 0;
            MemWrite = 0;
            Branch = 0;
            Jump = 0;
            ExtSign = 1;
            JalSign = 0;
        end

        //beq command
        6'b000100:
        begin
            ALUOp = 3'b110;
            RegDst = 0;
            ALUSrc = 0;
            MemToReg = 0;
            RegWrite = 0;
            MemRead = 0;
            MemWrite = 0;
            Branch = 1;
            Jump = 0;
            ExtSign = 1;
            JalSign = 0;
        end

        //ori command
        6'b001101:
        begin
            ALUOp = 3'b010;
            RegDst = 0;
            ALUSrc = 1;
            MemToReg = 0;
            RegWrite = 1;
            MemRead = 0;
            MemWrite = 0;
            Branch = 0;
            Jump = 0;
            ExtSign = 1;
            JalSign = 0;
        end

        //andi command
        6'b001100:
        begin
            ALUOp = 3'b011;
            RegDst = 0;
            ALUSrc = 1;
            MemToReg = 0;
            RegWrite = 1;
            MemRead = 0;
            MemWrite = 0;
            Branch = 0;
            Jump = 0;
            ExtSign = 0;
            JalSign = 0;
        end

        //jump command
        6'b000010:
        begin
            ALUOp = 3'b100;
            RegDst = 0;
            ALUSrc = 0;
            MemToReg = 0;
            RegWrite = 0;
            MemRead = 0;
            MemWrite = 0;
            Branch = 0;
            Jump = 1;
            ExtSign = 0;
            JalSign = 0;
        end

        //jal command
        6'b000011:
        begin
            ALUOp = 3'b100;
            RegDst = 0;
            ALUSrc = 0;
            MemToReg = 0;
            RegWrite = 1;
            MemRead = 0;
            MemWrite = 0;
            Branch = 0;
            Jump = 1;
            ExtSign = 0;
            JalSign = 1;
        end

        default:
        begin
            RegDst = 0;
            ALUSrc = 0;
            MemToReg = 0;
            RegWrite = 0;
            MemRead = 0;
            MemWrite = 0;
            Branch = 0;
            ALUOp = 3'b111;
            Jump = 0;
        end
        endcase
    end
     
    assign regDst = RegDst;
    assign aluSrc = ALUSrc;
    assign memToReg = MemToReg;
    assign regWrite = RegWrite;
    assign memRead = MemRead;
    assign memWrite = MemWrite;
    assign branch = Branch;
    assign aluOp = ALUOp;
    assign jump = Jump;
    assign extSign = ExtSign;
    assign jalSign = JalSign;

endmodule
