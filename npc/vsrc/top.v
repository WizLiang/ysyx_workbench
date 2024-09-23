module top(
  input clk,
  input rst,
  input [7:0] data_in,
  output reg [7:0] seg0,
  output [15:0]led
);

// light u_light(
//     .clk(clk),
//     .rst(rst),
//     .led(led)
// );
wire [2:0] u_digit;
encoder_83 u_encoder_83(
  .in(data_in),
  .out(u_digit[2:0]),
  .valid(led[0])
);

seven_seg_decoder u_seven_seg_decoder(
  .digit({1'b0,u_digit}),
  .segments(seg0[7:1])
);

assign seg0[0] = 1'b0;

//assign seg0[7:0] = 8'b00000010;




endmodule
