// module mux21e(a,b,s,y);
//   input   a,b,s;
//   output  y;
//   MuxKey #(2, 1, 1) i0 (y, s, {
//     1'b0, a,
//     1'b1, b
//   });
// endmodule

// module mux41b(a,s,y);
//   input  [3:0] a;
//   input  [1:0] s;
//   output y;
//   MuxKeyWithDefault #(4, 2, 1) i0 (y, s, 1'b0, {
//     2'b00, a[0],
//     2'b01, a[1],
//     2'b10, a[2],
//     2'b11, a[3]
//   });
// endmodule

module mux41_2bit (
    input clk,
    input rst_n,
    input [1:0] X0,X1,X2,X3,
    input [1:0] Y,
    output [7:0] seg0,
    output [1:0] F
);
    wire [15:0] lut = { // 4*(2+2) = 16 bits
        2'd3, X3,  // Key: 3, Data: X3
        2'd2, X2,  // Key: 2, Data: X2
        2'd1, X1,  // Key: 1, Data: X1
        2'd0, X0   // Key: 0, Data: X0
    };
    MuxKey #(4, 2, 2) i0 (F, Y, lut);
    assign seg0 = {8{1'b1}};
endmodule
