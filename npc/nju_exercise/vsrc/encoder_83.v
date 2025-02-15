module encoder_83 (
    input [7:0] in,
    output reg [2:0] out,
    output reg valid  //valid input
);
    always @(*) begin
        // 默认值
        out = 3'b000; // 输出的编码
        valid = 1'b0; // 输入指示位
        
        // 从最高位到最低位检查输入
        if (in[7]) begin
            out = 3'd7; // 输入为7
            valid = 1'b1;
        end else if (in[6]) begin
            out = 3'd6; // 输入为6
            valid = 1'b1;
        end else if (in[5]) begin
            out = 3'd5; // 输入为5
            valid = 1'b1;
        end else if (in[4]) begin
            out = 3'd4; // 输入为4
            valid = 1'b1;
        end else if (in[3]) begin
            out = 3'd3; // 输入为3
            valid = 1'b1;
        end else if (in[2]) begin
            out = 3'd2; // 输入为2
            valid = 1'b1;
        end else if (in[1]) begin
            out = 3'd1; // 输入为1
            valid = 1'b1;
        end else if (in[0]) begin
            out = 3'd0; // 输入为0
            valid = 1'b1;
        end
        // 如果所有输入都为0，out 保持为 3'b000，valid 仍为 0
    end
endmodule
