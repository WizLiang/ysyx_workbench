module IDU #(
    ADDR_WIDTH = 5,
    DATA_WIDTH = 32
) (
    input [DATA_WIDTH-1 :0] inst,
    //data
    output [DATA_WIDTH-1 :0] imm,
    //addr
    output [ADDR_WIDTH-1 :0] rs1,
    output [ADDR_WIDTH-1 :0] rs2,
    output [ADDR_WIDTH-1 :0] rd,
    // output[WIDTH-1 :0] src1,
    // output[WIDTH-1 :0] src2,
    //control signals
    output is_I_type,
    output is_R_type,
    output [2:0] func3,
    output [6:0] func7,
    output [6:0] opcode
);
    //instruction type
    //op_imm 
    assign is_I_type = (inst[6:0]== 7'b0010011);

    //imm 
    //assign imm = {DATA_WIDTH{is_I_type}} & {{20{inst[31]}},inst[31:20]};
    assign imm = is_I_type ? {{20{inst[31]}}, inst[31:20]} : 32'b0; 

    //hardwired excepted imm
    assign func3 = inst[14:12];
    assign func7 = inst[31:25];
    assign  rd   = inst[11:7];
    assign rs1 = inst[19:15];
    assign rs2 = inst[24:20];
    assign opcode = inst[6:0];
    
endmodule