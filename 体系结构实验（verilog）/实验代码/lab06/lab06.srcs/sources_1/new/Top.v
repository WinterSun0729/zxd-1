`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/04/16 18:06:43
// Design Name: 
// Module Name: Top
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

//////////////////////////////////////////////////////////////////////////////////
    // Instruction Fetch Segement
    reg [31:0] IF_PCIN;
    wire [31:0] IF_INST;

    // instruction memory
    InstMem instmem_module (
        .readAddr(IF_PCIN),
        .clk(clk),
        .reset(reset),
        .instr(IF_INST)
    );

 /////////////////////////////////////////////////////////   
    // IF/ID Register
    reg [31:0] IFID_PC;
    reg [31:0] IFID_INST;

//////////////////////////////////////////////////////////////////////////////////
    // Instruction Decode Segement
    wire ID_REGDST; 
    wire ID_ALUSRC;    
    wire ID_MEMTOREG;
    wire ID_MEMREAD;  
    wire ID_REGWRITE;   
    wire ID_MEMWRITE;    
    wire ID_BRANCH; 
    wire ID_EXTSIGN;       
    wire ID_JALSIGN;
    wire ID_JUMP;
    wire [2:0] ID_ALUOP;

    // Control Unit
    Ctr ctr_module (
        .opCode(IFID_INST[31 : 26]),
        .nop(IFID_INST == 0),
        .regDst(ID_REGDST),
        .aluSrc(ID_ALUSRC),
        .memToReg(ID_MEMTOREG),
        .regWrite(ID_REGWRITE),
        .memRead(ID_MEMREAD),
        .memWrite(ID_MEMWRITE),
        .branch(ID_BRANCH),
        .aluOp(ID_ALUOP),
        .jump(ID_JUMP),
        .extSign(ID_EXTSIGN),
        .jalSign(ID_JALSIGN)
    );
    
    wire [31:0] ID_EXTRES;

    // EXTSIGN
    signext signext_module (
        .extSign(ID_EXTSIGN),
        .inst(IFID_INST[15 : 0]),
        .data(ID_EXTRES)
    );

    wire [4:0] WB_WRITEREG;
    wire [31:0] ID_REGOUT1;
    wire [31:0] ID_REGOUT2;
    wire [31:0] WB_REG_WRITE_DATA; 
    wire WB_REGWRITE;

    // register
    Register register_module (
        .readReg1(IFID_INST[25 : 21]),
        .readReg2(IFID_INST[20 : 16]),
        .writeReg(WB_WRITEREG),
        .writeData(WB_REG_WRITE_DATA),
        .regWrite(WB_REGWRITE),
        .clk(clk),
        .reset(reset),
        .readData1(ID_REGOUT1),
        .readData2(ID_REGOUT2)
    );
        
    wire [4 : 0] ID_WRITE_REG_TEMP;
    // rd or rt
    MUX_5 rt_rd_selector (
        .Select(ID_REGDST),
        .data0(IFID_INST[15 : 11]),
        .data1(IFID_INST[20 : 16]),
        .data(ID_WRITE_REG_TEMP)
    );

/////////////////////////////////////////////////////////
    // ID/EX register
    reg [2:0] IDEX_ALUOP;
    reg IDEX_ALUSRC;
    reg IDEX_MEMTOREG;
    reg IDEX_MEMREAD; 
    reg IDEX_REGWRITE;
    reg IDEX_MEMWRITE;
    reg IDEX_BRANCH;
    reg [31:0] IDEX_EXTRES;
    reg [4:0] IDEX_RS;
    reg [4:0] IDEX_RT;
    reg [31:0] IDEX_REGOUT1;
    reg [31:0] IDEX_REGOUT2;
    reg [5:0] IDEX_FUNCT;
    reg [4:0] IDEX_SHAMT;
    reg [4:0] IDEX_REGDEST;
    reg [31:0] IDEX_PC;

//////////////////////////////////////////////////////////////////////////////////
    wire [31:0] EX_ALU1_FORWARDING;
    wire [31:0] EX_ALU2_FORWARDING;
    
    // Execution Segment
    wire [3:0] EX_ALUCTR;
    wire EX_SHAMTSIGN; 

    // ALU Controller
    ALUCtr aluctr_module (
        .aluOp(IDEX_ALUOP),
        .funct(IDEX_FUNCT),
        .aluCtrOut(EX_ALUCTR),
        .shamtSign(EX_SHAMTSIGN),
        .jrSign(EX_JRSIGN)
    );
    
    wire [31:0] EX_ALUIN1;
    wire [31:0] EX_ALUIN2;
    wire EX_ALUZERO;
    wire [31:0] EX_ALURES;

    // INST[10:6] or rs
    MUX rs_shamt_selector (
        .Select(EX_SHAMTSIGN),
        .data0({27'b00000000000000000000000000, IDEX_SHAMT}),
        .data1(EX_ALU1_FORWARDING),
        .data(EX_ALUIN1)
    );

    // EXTRES or rt
    MUX rt_ext_selector (
        .Select(IDEX_ALUSRC),
        .data0(IDEX_EXTRES),
        .data1(EX_ALU2_FORWARDING),
        .data(EX_ALUIN2)
    );

    // ALU
    ALU alu_module (
        .input1(EX_ALUIN1),
        .input2(EX_ALUIN2),
        .aluCtr(EX_ALUCTR),
        .zero(EX_ALUZERO),
        .aluRes(EX_ALURES)
    );

    wire [31 : 0] BRANCH_DEST = IDEX_PC + 4 + (IDEX_EXTRES << 2);

/////////////////////////////////////////////////////////
    // EX/MA register
    reg EXMA_MEMTOREG;
    reg EXMA_MEMREAD; 
    reg EXMA_REGWRITE;
    reg EXMA_MEMWRITE;
    reg [31:0] EXMA_ALURES;
    reg [31:0] EXMA_REGOUT2;
    reg [4:0] EXMA_REGDEST;

//////////////////////////////////////////////////////////////////////////////////
    // Memery Segment
    wire [31:0] MA_MEM_READ_DATA;
    // data memory
    dataMemory datamemory_module (
        .clk(clk),
        .address(EXMA_ALURES),
        .writeData(EXMA_REGOUT2),
        .memWrite(EXMA_MEMWRITE),
        .memRead(EXMA_MEMREAD),
        .readData(MA_MEM_READ_DATA)
    );

    wire [31:0] MA_REG_WRITE_DATA_T;
    
    // MEM READ DATA or ALURES
    MUX mem_alu_selector (
        .Select(EXMA_MEMTOREG),
        .data0(MA_MEM_READ_DATA),
        .data1(EXMA_ALURES),
        .data(MA_REG_WRITE_DATA_T)
    );
/////////////////////////////////////////////////////////
    // ME/WB register
    reg MAWB_REGWRITE;
    reg [31:0] MAWB_FINALDATA;
    reg [4:0] MAWB_REGDEST;

//////////////////////////////////////////////////////////////////////////////////
    // Write Back Segment
    MUX jal_selector (
        .Select(ID_JALSIGN),
        .data0(IFID_PC + 4),
        .data1(MAWB_FINALDATA),
        .data(WB_REG_WRITE_DATA)
    );
    
    assign WB_WRITEREG = MAWB_REGDEST;
    assign WB_REGWRITE = MAWB_REGWRITE;

//////////////////////////////////////////////////////////////////////////////////
    // PC update
    wire [31:0] PC_JUMP_END;
    MUX jump_selector(
        .Select(ID_JUMP), 
        .data0(((IFID_PC + 4) & 32'hf0000000) + (IFID_INST [25 : 0] << 2)), 
        .data1(IF_PCIN + 4),
        .data(PC_JUMP_END));
    
    wire BEQ_BRANCH = IDEX_BRANCH & EX_ALUZERO;
    wire [31 : 0] PC_BEQ_END;
    MUX beq_selector(
        .Select(BEQ_BRANCH),
        .data0(BRANCH_DEST),
        .data1(PC_JUMP_END),
        .data(PC_BEQ_END));

//////////////////////////////////////////////////////////////////////////////////
    // Forwarding
    wire [31 : 0] EX_ALU1_FORTEMP;
    wire [31 : 0] EX_ALU2_FORTEMP;
    MUX forward1_1(
        .Select(MAWB_REGWRITE & (MAWB_REGDEST == IDEX_RS)),
        .data0(MAWB_FINALDATA),
        .data1(IDEX_REGOUT1),
        .data(EX_ALU1_FORTEMP));
    MUX forward1_2(
        .Select(EXMA_REGWRITE & (EXMA_REGDEST == IDEX_RS)),
        .data0(EXMA_ALURES),
        .data1(EX_ALU1_FORTEMP),
        .data(EX_ALU1_FORWARDING));
    
    MUX forward2_1(
        .Select(MAWB_REGWRITE & (MAWB_REGDEST == IDEX_RT)),
        .data0(MAWB_FINALDATA),
        .data1(IDEX_REGOUT2),
        .data(EX_ALU2_FORTEMP));
    MUX forward2_2(
        .Select(EXMA_REGWRITE & (EXMA_REGDEST == IDEX_RT)),
        .data0(EXMA_ALURES),
        .data1(EX_ALU2_FORTEMP),
        .data(EX_ALU2_FORWARDING));

    // Stall
    wire STALL = IDEX_MEMREAD & 
        ((IDEX_RT == IFID_INST [25 : 21]) | 
        (IDEX_RT == IFID_INST [20 : 16]));

always @(reset)
    begin
        if (reset) begin
            IF_PCIN = 0;
            IFID_INST = 0;
            IFID_PC = 0;
            IDEX_ALUOP = 0;
            IDEX_ALUSRC = 0;
            IDEX_MEMTOREG = 0;
            IDEX_MEMREAD = 0; 
            IDEX_REGWRITE = 0;
            IDEX_MEMWRITE = 0;
            IDEX_BRANCH = 0;
            IDEX_EXTRES = 0;
            IDEX_RS = 0;
            IDEX_RT = 0;
            IDEX_REGOUT1 = 0;
            IDEX_REGOUT2 = 0;
            IDEX_FUNCT = 0;
            IDEX_SHAMT = 0;
            IDEX_REGDEST = 0;
            IDEX_PC = 0;
            EXMA_MEMTOREG = 0;
            EXMA_MEMREAD = 0;
            EXMA_REGWRITE = 0;
            EXMA_MEMWRITE = 0;
            EXMA_ALURES = 0;
            EXMA_REGOUT2 = 0;
            EXMA_REGDEST = 0;
            MAWB_REGWRITE = 0;
            MAWB_FINALDATA = 0;
            MAWB_REGDEST = 0;
        end
    end
    
    always @(posedge clk) 
    begin
        // IF/ID -> ID/EX
        if (STALL || (IDEX_BRANCH & EX_ALUZERO)) 
        begin
            IDEX_ALUOP <= 4'b1111;
            IDEX_ALUSRC <= 0;
            IDEX_MEMTOREG <= 0;
            IDEX_MEMREAD <= 0;
            IDEX_REGWRITE <= 0;
            IDEX_MEMWRITE <= 0;
            IDEX_BRANCH <= 0;
            IDEX_EXTRES <= 0;
            IDEX_RS <= 0;
            IDEX_RT <= 0;
            IDEX_REGOUT1 <= 0;
            IDEX_REGOUT2 <= 0;
            IDEX_FUNCT <= 0;
            IDEX_SHAMT <= 0;
            IDEX_REGDEST <= 0;
            IDEX_PC <= IFID_PC;
        end
        else begin
            IDEX_ALUOP <= ID_ALUOP;
            IDEX_ALUSRC <= ID_ALUSRC;
            IDEX_MEMTOREG <= ID_MEMTOREG;
            IDEX_MEMREAD <= ID_MEMREAD;
            IDEX_REGWRITE <= ID_REGWRITE;
            IDEX_MEMWRITE <= ID_MEMWRITE;
            IDEX_BRANCH <= ID_BRANCH;
            IDEX_EXTRES <= ID_EXTRES;
            IDEX_RS <= IFID_INST [25 : 21];
            IDEX_RT <= IFID_INST [20 : 16];
            IDEX_REGOUT1 <= ID_REGOUT1;
            IDEX_REGOUT2 <= ID_REGOUT2;
            IDEX_FUNCT <= IFID_INST [5 : 0];
            IDEX_SHAMT <= IFID_INST [10 : 6];
            IDEX_REGDEST <= ID_WRITE_REG_TEMP;
            IDEX_PC <= IFID_PC;
        end
        
        // ID/EX -> EX/MA
        EXMA_MEMTOREG <= IDEX_MEMTOREG;
        EXMA_MEMREAD <= IDEX_MEMREAD;
        EXMA_REGWRITE <= IDEX_REGWRITE;
        EXMA_MEMWRITE <= IDEX_MEMWRITE;
        EXMA_ALURES <= EX_ALURES;
        EXMA_REGOUT2 <= IDEX_REGOUT2;
        EXMA_REGDEST <= IDEX_REGDEST;

        // EX/MA -> MA/WB
        MAWB_REGWRITE <= EXMA_REGWRITE;
        MAWB_REGDEST <= EXMA_REGDEST;
        MAWB_FINALDATA <= MA_REG_WRITE_DATA_T;

        // PCupdate -> IF/ID
        if (! STALL)
        begin
            IF_PCIN <= PC_BEQ_END;
            IFID_INST <= IF_INST;
            IFID_PC <= IF_PCIN;
        end
    end
endmodule