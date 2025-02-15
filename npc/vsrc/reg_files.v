module Registerfile #(
    DATA_WIDTH = 32,
    ADDR_WIDTH = 5
) (
    input clk,
    input rst,
    //read
    input [ADDR_WIDTH-1 :0] raddr1,
    output [DATA_WIDTH-1 :0] rdata1,
    input [ADDR_WIDTH-1 :0] raddr2,
    output [DATA_WIDTH-1 :0] rdata2,

    //write
    input [ADDR_WIDTH-1 :0] waddr,
    input wr_en,
    input [DATA_WIDTH-1 :0] wdata
);
    // gpr stands for global po
    reg [DATA_WIDTH-1 :0] gpr [2**ADDR_WIDTH-1: 0];
    //Hardwired x0 to zero
    assign gpr[0] = 32'h0;

    assign rdata1 = gpr[raddr1];
    assign rdata2 = gpr[raddr2];
    //assign gpr[waddr] = (wr_en & (waddr!=0)):wdata;
    //use clk and rst to update gprs
    always @(posedge clk or posedge rst) begin
        if(rst)begin
            integer i;
            for (i = 1; i < 2**ADDR_WIDTH; i = i + 1) begin
                gpr[i] <= 32'h0; // 清除非x0寄存器
            end
        end
        else if(wr_en && (waddr != 5'b0))begin
        //elseif(wr_en)begin
            gpr[waddr] <= wdata;
        end
    end

    
endmodule