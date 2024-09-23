module top(
  input clk,
  input rst,

  input a,
  input b,

  input sw,
  output reg f,
  output led1
);
  always@(posedge clk)begin
  if(rst) begin 
    f <= 1'b0;
  end
  else begin 
    f<= a^b;
  end
  end 
  assign led1 = sw;
  //assign f = a ^ b;
endmodule
