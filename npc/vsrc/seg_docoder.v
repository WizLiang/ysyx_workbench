// module seven_seg_decoder(
//     input [3:0] digit,
//     output reg [6:0] segments
// );

// // // 定义段位常量
// // parameter SEG_A = segments[6];
// // parameter SEG_B = segments[5];
// // parameter SEG_C = segments[4];
// // parameter SEG_D = segments[3];
// // parameter SEG_E = segments[2];
// // parameter SEG_F = segments[1];
// // parameter SEG_G = segments[0];

// always @(*) begin
//     case(digit)
//         4'd0: segments = 7'b0000001; // 显示数字 0
//         4'd1: segments = 7'b1001111; // 显示数字 1
//         4'd2: segments = 7'b0010010; // 显示数字 2
//         4'd3: segments = 7'b0000110; // 显示数字 3
//         4'd4: segments = 7'b1001100; // 显示数字 4
//         4'd5: segments = 7'b0100100; // 显示数字 5
//         4'd6: segments = 7'b0100000; // 显示数字 6
//         4'd7: segments = 7'b0001111; // 显示数字 7
//         4'd8: segments = 7'b0000000; // 显示数字 8
//         4'd9: segments = 7'b0000100; // 显示数字 9
//         4'd10: segments = 7'b0001000; // 显示字母 A
//         4'd11: segments = 7'b1100000; // 显示字母 b
//         4'd12: segments = 7'b0110001; // 显示字母 C
//         4'd13: segments = 7'b1000010; // 显示字母 d
//         4'd14: segments = 7'b0110000; // 显示字母 E
//         4'd15: segments = 7'b0111000; // 显示字母 F
//         default: segments = 7'b1111111; // 默认全部熄灭
//     endcase
// end

// endmodule



module seven_seg_decoder(
    input [3:0] digit,
    input enable,
    output reg [6:0] segments
);

always @(*) begin
    if (enable) begin
        case(digit)
            4'd0: segments = 7'b0000001; // 显示数字 0
            4'd1: segments = 7'b1001111; // 显示数字 1
            4'd2: segments = 7'b0010010; // 显示数字 2
            4'd3: segments = 7'b0000110; // 显示数字 3
            4'd4: segments = 7'b1001100; // 显示数字 4
            4'd5: segments = 7'b0100100; // 显示数字 5
            4'd6: segments = 7'b0100000; // 显示数字 6
            4'd7: segments = 7'b0001111; // 显示数字 7
            4'd8: segments = 7'b0000000; // 显示数字 8
            4'd9: segments = 7'b0000100; // 显示数字 9
            4'd10: segments = 7'b0001000; // 显示字母 A
            4'd11: segments = 7'b1100000; // 显示字母 b
            4'd12: segments = 7'b0110001; // 显示字母 C
            4'd13: segments = 7'b1000010; // 显示字母 d
            4'd14: segments = 7'b0110000; // 显示字母 E
            4'd15: segments = 7'b0111000; // 显示字母 F
            default: segments = 7'b1111111; // 默认全部熏灭
        endcase
    end else begin
        segments = 7'b1111111; // 当 enable 为 0 时全部熏灭
    end
end

endmodule
