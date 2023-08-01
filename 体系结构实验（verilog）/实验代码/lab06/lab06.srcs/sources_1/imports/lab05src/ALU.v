`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/03/29 09:48:50
// Design Name: 
// Module Name: ALU
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


module ALU(
    input [31:0] input1,
    input [31:0] input2,
    input [3:0] aluCtr,
    output zero,
    output [31:0] aluRes
    );
    reg Zero;
    reg [31:0] ALURes;
    
    always @ (input1 or input2 or aluCtr)
    begin
        //add
        if(aluCtr == 4'b0010)
            ALURes = input1 + input2;

        //sub
        else if (aluCtr == 4'b0110)
            ALURes = input1 - input2;
        
        //or
        else if (aluCtr == 4'b0001)
            ALURes = input1 | input2;

        //and
        else if (aluCtr == 4'b0000)
            ALURes = input1 & input2;

        //nor
        else if (aluCtr == 4'b1100)
            ALURes = ~(input1 | input2);

        //slt
        else if (aluCtr == 4'b0111)
            ALURes = ($signed(input1) < $signed(input2));
        
        //sll
        else if (aluCtr ==4'b0011)    
            ALURes = input2 << input1;

        //srl
        else if (aluCtr ==4'b0100)    
            ALURes = input2 >> input1;

        //keep
        else if (aluCtr ==4'b0101)    
            ALURes = input1;

        if(ALURes==0)
            Zero = 1;
        else
            Zero = 0;
    end

   assign aluRes=ALURes;
   assign zero=Zero;

endmodule