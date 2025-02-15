module ProgramCounter #(
    PC_WIDTH = 32,
    PC_RESET = 32'h80000000
) (
    input clk,
    input rst,
    input en,
    input [PC_WIDTH-1 : 0] pc_in,
    output reg [PC_WIDTH-1 :0] pc_out
);
    always @(posedge clk or posedge rst) begin
        if(rst) pc_out <= PC_RESET;
        else if (en) pc_out <= pc_in;
        else pc_out <= pc_out + 32'h4;
    end

endmodule