module linear_feedback_shift_register (
    input clk,
    input rst_n,
    output [7:0] data_out
);
    wire [7:0] data_in;

    //assign data_in[0] = data_out[0] ^ data_out[2] ^ data_out[3] ^ data_out[4];
    assign data_in[0] = (data_out == 8'b0) ? 1'b1 : data_out[0] ^ 
             data_out[2] ^ data_out[3] ^ data_out[4];
    shift_reg u_shift_reg(
        .clk(clk),
        .rst_n(rst_n),
        .ctrl(3'b101),
        .data_in(data_in),
        .Q(data_out)
    );
    
endmodule