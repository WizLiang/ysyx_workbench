module EXU #(
    ADDR_WIDTH =5,
    DATA_WIDTH = 32
) (
    //control signals
    input [2:0] func3,
    input [6:0] func7,
    input [6:0] opcode,
    input is_I_type,
    input is_R_type,

    //data
    input [DATA_WIDTH-1 :0] rs1,
    input [DATA_WIDTH-1 :0] rs2,
    input [DATA_WIDTH-1 :0] imm,
    input [ADDR_WIDTH-1 :0] rd,

    output wr_en,
    output [ADDR_WIDTH-1 :0] waddr,
    output [DATA_WIDTH-1 :0] wdata
);
    
    wire addi;
    wire op_imm;
    assign op_imm = (opcode == 7'b0010011)? 1'b1: 1'b0;

    assign addi = op_imm & (func3 == 3'b000);

    assign wdata = addi ? (imm + rs1) : 32'b0;
    assign waddr = rd;
    assign wr_en = addi ? 1'b1: 1'b0;
    
endmodule