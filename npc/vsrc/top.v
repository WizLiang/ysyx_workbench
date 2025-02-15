module cpu_top #(
    ADDR_WIDTH = 5,
    DATA_WIDTH = 32
) (
    input clk,
    input rst,
    input [DATA_WIDTH-1: 0]inst,
    output [DATA_WIDTH-1: 0]pc
);

    ProgramCounter u_pc(
        .clk(clk),
        .rst(rst),
        .en(1'b0),
        .pc_in(32'h80000000),
        .pc_out(pc)
    );

    // Control and data signals
    wire [DATA_WIDTH-1 :0] imm;     // Immediate value
    wire [DATA_WIDTH-1 :0] rs1_data;   
    wire [DATA_WIDTH-1 :0] rs2_data;
    wire [DATA_WIDTH-1 :0] rd_data;


    wire [ADDR_WIDTH-1 :0] rs1_addr;   
    wire [ADDR_WIDTH-1 :0] rs2_addr;
    wire [ADDR_WIDTH-1 :0] rd_addr;
    wire [ADDR_WIDTH-1 :0] rd_tmp;  // let the write bus of the rf all from exu
    wire is_I_type;                 // I-type instruction
    wire is_R_type;                 // R-type instruction
    wire [2:0] func3;               // func3 field
    wire [6:0] func7;               // func7 field
    wire [6:0] opcode;              // Opcode field

    wire wr_en_reg;

    // IDU instance
    IDU u_IDU (
        .inst(inst),                 // Input instruction
        .imm(imm),                   // Output immediate value
        .rs1(rs1_addr),                   // Output rs1 address
        .rs2(rs2_addr),                   // Output rs2 address
        .rd(rd_tmp),                     // Output rd address
        .is_I_type(is_I_type),       // Output I-type signal
        .is_R_type(is_R_type),       // Output R-type signal
        .func3(func3),               // Output func3 field
        .func7(func7),               // Output func7 field
        .opcode(opcode)              // Output opcode field
    );

    // Registerfile instance
    Registerfile u_rf (
        .clk(clk),                    
        .rst(rst),                    
        .raddr1(rs1_addr),            // Read rs1 register
        .rdata1(rs1_data),         
        .raddr2(rs2_addr),            // Read rs2 register
        .rdata2(rs2_data),   
        .waddr(rd_addr),              // Write to destination register
        .wr_en(wr_en_reg),            // Write enable signal
        .wdata(rd_data)                  
    );

    // EXU instance
    EXU u_EXU (
        .func3(func3),                // func3 field
        .func7(func7),                // func7 field
        .opcode(opcode),              // Opcode field
        .is_I_type(is_I_type),        // I-type instruction flag
        .is_R_type(is_R_type),        // R-type instruction flag
        .rs1(rs1_data),                    // rs1 register data
        .rs2(rs2_data),                    // rs2 register data
        .imm(imm),                    
        .rd(rd_tmp),                      // Destination register address and cannot use rd_addr for the multiple combinational drivers
        .wr_en(wr_en_reg),            
        .waddr(rd_addr),              
        .wdata(rd_data)             
    );

endmodule