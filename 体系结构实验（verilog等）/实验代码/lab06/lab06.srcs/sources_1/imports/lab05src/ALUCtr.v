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
    input [2:0] aluOp,
    input [5:0] funct,
    output [3:0] aluCtrOut,
    output shamtSign,
    output jrSign
    );

    reg [3:0] ALUCtrOut;
    reg ShamtSign;
    reg JrSign;

    always@(aluOp or funct)
    begin

        ShamtSign = 0;
        
        if ({aluOp, funct} == 9'b101001000) JrSign = 1;
        else JrSign = 0;

        casex({aluOp, funct})
            9'b000xxxxxx:  // lw, sw: add
            begin
                ALUCtrOut = 4'b0010;
            end

            9'b001xxxxxx:  // addi: add
            begin
                ALUCtrOut = 4'b0010;
            end
            
            9'b110xxxxxx:  // beq: sub
            begin
                ALUCtrOut = 4'b0110;
            end
            
            9'b011xxxxxx:  // andi: and
            begin
                ALUCtrOut = 4'b0000;
            end
            
            9'b010xxxxxx:  // ori: or
            begin
                ALUCtrOut = 4'b0001;
            end
            
            9'b101000000:  // sll
            begin
                ALUCtrOut = 4'b0011;
                ShamtSign = 1;
            end
            
            9'b101000010:  // srl
            begin
                ALUCtrOut = 4'b0100;
                ShamtSign = 1;
            end
            
            9'b101001000:  // jr: keep
            begin
                ALUCtrOut = 4'b0101;
            end
            
            9'b101100000:  // add
            begin
                ALUCtrOut = 4'b0010;
            end
            
            9'b101100010:  // sub
            begin
                ALUCtrOut = 4'b0110;
            end
            
            9'b101100100:  // and
            begin
                ALUCtrOut = 4'b0000;
            end
            
            9'b101100101:  // or
            begin
                ALUCtrOut = 4'b0001;
            end
            
            9'b101101010:  // slt
            begin
                ALUCtrOut = 4'b0111;
            end
            
            9'b100xxxxxx:  // jump: keep
            begin
                ALUCtrOut = 4'b0101;
            end

            9'b100xxxxxx:  // jal: keep
            begin
                ALUCtrOut = 4'b0101;
            end
            
        endcase

    end

    assign aluCtrOut = ALUCtrOut;
    assign shamtSign = ShamtSign;
    assign jrSign = JrSign;

endmodule
