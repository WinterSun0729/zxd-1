`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/04/13 13:13:32
// Design Name: 
// Name: Top
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

 module Top(
        input clk,
        input reset
    );

    wire [31:0] PCIN;
    wire [31:0] PCOUT; 
    // PC
    PC pc_module (
        .PCin(PCIN),
        .clk(clk),
        .reset(reset),
        .pcout(PCOUT)
    );
    
    wire [31:0] INST;
    wire REGDST; 
    wire ALUSRC;    
    wire MEMTOREG;
    wire REGWRITE;   
    wire MEMREAD;  
    wire MEMWRITE;    
    wire BRANCH; 
    wire EXTSIGN;       
    wire JALSIGN;
    wire [2:0] ALUOP;
    wire JUMP;
    // Control Unit
    Ctr ctr_module (
        .opCode(INST[31 : 26]),
        .regDst(REGDST),
        .aluSrc(ALUSRC),
        .memToReg(MEMTOREG),
        .regWrite(REGWRITE),
        .memRead(MEMREAD),
        .memWrite(MEMWRITE),
        .branch(BRANCH),
        .aluOp(ALUOP),
        .jump(JUMP),
        .extSign(EXTSIGN),
        .jalSign(JALSIGN)
    );

    wire [31:0] ALUIN1;
    wire [31:0] ALUIN2;
    wire [3:0] ALUCTR;
    wire ALUZERO;
    wire [31:0] ALURES;
    
    // ALU
    ALU alu_module (
        .input1(ALUIN1),
        .input2(ALUIN2),
        .aluCtr(ALUCTR),
        .zero(ALUZERO),
        .aluRes(ALURES)
    );

    wire SHAMTSIGN; 
    wire JRSIGN;
    // ALU Controller
    ALUCtr aluctr_module (
        .aluOp(ALUOP),
        .funct(INST[5 : 0]),
        .aluCtrOut(ALUCTR),
        .shamtSign(SHAMTSIGN),
        .jrSign(JRSIGN)
    );
    
    wire [31:0] EXTRES;
    // EXTSIGN
    signext signext_module (
        .extSign(EXTSIGN),
        .inst(INST[15 : 0]),
        .data(EXTRES)
    );

    wire [4:0] WRITEREG;
    wire [31:0] REGOUT1;
    wire [31:0] REGOUT2;
    wire [31:0] REG_WRITE_DATA; 
    // register
    Register register_module (
        .readReg1(INST[25 : 21]),
        .readReg2(INST[20 : 16]),
        .writeReg(WRITEREG),
        .writeData(REG_WRITE_DATA),
        .regWrite(REGWRITE & (~JRSIGN)),
        .clk(clk),
        .reset(reset),
        .readData1(REGOUT1),
        .readData2(REGOUT2)
    );
    
    // instruction memory
    InstMem instmem_module (
        .readAddr(PCOUT),
        .clk(clk),
        .reset(reset),
        .instr(INST)
    );
    
    wire [31:0] MEM_READ_DATA;
    // data memory
    dataMemory datamemory_module (
        .clk(clk),
        .address(ALURES),
        .writeData(REGOUT2),
        .memWrite(MEMWRITE),
        .memRead(MEMREAD),
        .readData(MEM_READ_DATA)
    );

    // PC update
    PCupdate pcupdate_module (
        .newPC(PCOUT+4),
        .target(INST[25 : 0]),
        .offset(EXTRES << 2),
        .regOut(REGOUT1),
        .Branch(BRANCH),
        .Aluzero(ALUZERO),
        .Jump(JUMP),
        .JrSign(JRSIGN),
        .nextPC(PCIN)
    );
    
////////////////////////////////////////////////////
    wire [31 : 0] REG_WRITE_DATA_T;
    wire [4 : 0] WRITE_REG_TEMP; 

    // INST[10:6] or rs
    MUX rs_shamt_selector (
        .Select(SHAMTSIGN),
        .data0({27'b00000000000000000000000000, INST[10 : 6]}),
        .data1(REGOUT1),
        .data(ALUIN1)
    );

    // EXTRES or rt
    MUX rt_ext_selector (
        .Select(ALUSRC),
        .data0(EXTRES),
        .data1(REGOUT2),
        .data(ALUIN2)
    );
    
    // MEM READ DATA or ALURES
    MUX mem_alu_selector (
        .Select(MEMTOREG),
        .data0(MEM_READ_DATA),
        .data1(ALURES),
        .data(REG_WRITE_DATA_T)
    );

    // PCOUT + 4 or REG WRITE DATA T
    MUX jal_selector (
        .Select(JALSIGN),
        .data0(PCOUT + 4),
        .data1(REG_WRITE_DATA_T),
        .data(REG_WRITE_DATA)
    );

    // rd or rt
    MUX_5 rt_rd_selector (
        .Select(REGDST),
        .data0(INST[15 : 11]),
        .data1(INST[20 : 16]),
        .data(WRITE_REG_TEMP)
    );
    
    // 11111 or rt/td
    MUX_5 rtrd_31_selector (
        .Select(JALSIGN),
        .data0(5'b11111),
        .data1(WRITE_REG_TEMP),
        .data(WRITEREG)
    );

endmodule
